/*
 * FakeBGP.cpp
 *
 *  Created on: Mar 5, 2014
 *      Author: egboeny
 */

#include "FakeBGPLS.h"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <fstream>
#include <iostream>
#include <signal.h>
#include <errno.h>
#include <unistd.h>

#include "Messages/KeepAlive.h"
#include "Messages/OpenMessage.h"

#include "Messages/Attributes/Origin.h"
#include "Messages/Attributes/ASPath.h"
#include "Messages/Attributes/MPReach.h"
// Ericsson fix start
#include "Messages/Attributes/LocalPref.h"
// Ericsson fix end
#include "Messages/Attributes/LS_TLV/AdministrativeGroup.h"
#include "Messages/Attributes/LS_TLV/LSNLRI.h"
#include "Messages/Attributes/LS_TLV/IPv4RouterID.h"
#include "Messages/Attributes/LS_TLV/LinkLocalRemoteIdentifierSubTLV.h"
#include "Messages/Attributes/LS_TLV/Metric.h"
#include "Messages/Attributes/LS_TLV/TeMetric.h"
#include "Messages/Attributes/BGPLSAttribute.h"
#include "Messages/Attributes/LS_TLV/MaxReservableBandwidth.h"
#include "Messages/Attributes/LS_TLV/MaximumLinkBandwidth.h"
#include "Messages/Attributes/LS_TLV/UnreservedBandwidth.h"
#include "Messages/Attributes/LS_TLV/IPReachability.h"
#include "Messages/Attributes/LS_TLV/PrefixMetric.h"
#include "Messages/Attributes/LS_TLV/PrefixSID.h"
#include "Messages/Attributes/LS_TLV/AdjacencySID.h"
#include "Messages/Attributes/LS_TLV/UnidirectionalLinkDelay.h"
#include "Messages/Attributes/LS_TLV/InterfaceAddress.h"
#include "Messages/Attributes/LS_TLV/NeighborAddress.h"

template <typename Graph>
typename Graph::Arc revert(const Graph& graph, const typename Graph::Arc& arc) {
    for (typename Graph::OutArcIt it(graph, graph.target(arc)); it != lemon::INVALID; ++it) {
        if (graph.target(it) == graph.source(arc))
            return it;
    }

    throw std::string("Cannot revert arc!");
}

FakeBGPLS::FakeBGPLS(const std::string& home, const std::string& bgp_identifier, std::string binding_address, unsigned int port_value, unsigned int proto_profile) :
  binding_address(binding_address),
  port(port_value),
  bgp_id(bgp_identifier),
  label(network),
	as(network),
	bgpLsId(network),
	routerId(network),
	area(network),
	loopbackAddress(network),
	nodeSids(network),
	adjSids(network),
	cost(network),
	bw(network),
	delay(network),
	srcAddress(network),
	nodeId(prefixes),
	prefVal(prefixes),
	prefSids(prefixes),
	prefCosts(prefixes),
	nhop(prefixes),
	proto_profile(proto_profile)
{
	//Zed's old code
/*	ifstream nodeFile(home + "/bgp-nodes.txt");
	string addr, sid;
	while (nodeFile >> addr >> sid) {
		if ((ipConv(addr) & 0x000fffff) != stoi(sid)) {
			cout << "Error: router id " << addr << " and sid " << sid << " are not in sync." << endl;
			throw;
		}

		nodes.push_back(ipConv(addr));
	}

	ifstream adjFile(home + "/bgp-adjs.txt");
	string source, target, bw, cost;
	while (adjFile >> source >> target >> bw >> cost) {
		adjs.push_back({ipConv(source), ipConv(target), stoi(bw), stoi(cost)});
	}*/

	lemon::DigraphReader<lemon::ListDigraph>(network, home)
			.nodes("nodes")
			.nodeMap("label", label)
			.nodeMap("as", as)
			.nodeMap("bgpLsId", bgpLsId)
			.nodeMap("routerId", routerId)
			.nodeMap("area", area)
			.nodeMap("loopbackAddress", loopbackAddress)
			.nodeMap("sid", nodeSids)
			.arcs("links")
			.arcMap("cost", cost)
			.arcMap("bw", bw)
			.arcMap("delay", delay)
			.arcMap("sid", adjSids)
			.arcMap("saddress", srcAddress)
			.run();

	lemon::DigraphReader<lemon::ListDigraph>(prefixes, home)
	        .nodes("prefixes")
	        .nodeMap("nodeId", nodeId)
	        .nodeMap("prefix", prefVal)
	        .nodeMap("sid", prefSids)
	        .nodeMap("cost", prefCosts)
	        .nodeMap("nhop", nhop)
	        .arcs("empty")
	        .run();

	for (lemon::ListDigraph::NodeIt it(network); it != lemon::INVALID; ++it)
	    label2Node[label[it]] = it;
}

FakeBGPLS::~FakeBGPLS() {}

//UpdateMessage FakeBGPLS::createSimpleNodeUpdate(IsoNodeId& isoAddress, boost::asio::ip::address_v4& ipAddress, uint32_t as, uint32_t bgpLsId) {
UpdateMessage FakeBGPLS::createSimpleNodeUpdate(const LocalNodeDescriptor& lnd, boost::asio::ip::address_v4& ipAddress) {
	NodeNLRI nnlri(1, 0);		//Proto=1 (IS-IS L1), routing universe = 0 (packet topology)
	nnlri.appendData(lnd.startPointer(), lnd.getFullSize());	//That goes into a Node NLRI

	LSMPReach lsReach(ipAddress);
	lsReach.appendTLV(nnlri);			//Node NLRI is transported in the "opaque" attribute named MP_Reach_NLRI
	UpdateMessage update;
	update.appendAttribute(Origin(Origin::Incomplete));
	update.appendAttribute(ASPath());
  // Ericsson fix start
  update.appendAttribute(LocalPref(1));
  // Ericsson fix end
	update.appendAttribute(lsReach);	//Finally we put this whole shit into an update message...

	return update;
}

UpdateMessage FakeBGPLS::createSimpleArcUpdate(
                                const LocalNodeDescriptor& lnd,
                                const RemoteNodeDescriptor& rnd,
                                boost::asio::ip::address_v4& sIpAddress,
                                uint32_t sid, uint32_t tid,
                                boost::asio::ip::address_v4& interfaceAddress, boost::asio::ip::address_v4& neighborAddress) {
    InterfaceAddress iatlv(interfaceAddress);
    NeighborAddress natlv(neighborAddress);

	LinkNLRI lnlri(1, 0);	//Link NLRI
	lnlri.appendData(lnd.startPointer(), lnd.getFullSize());	//LocalNodeDescriptor
	lnlri.appendData(rnd.startPointer(), rnd.getFullSize());	//RemoteNodeDescriptor

    if (sid != 0 && tid != 0) {
        LinkLocalRemoteIdentifierSubTLV llrstlv(sid, tid);	//This is the id of the link among multiple paralell links
        lnlri.appendData(llrstlv.startPointer(), llrstlv.getFullSize());	//Local/Remote identifier (link descriptor)
    }

	lnlri.appendData(iatlv.startPointer(), iatlv.getFullSize());
	lnlri.appendData(natlv.startPointer(), natlv.getFullSize());

	LSMPReach lsReach(sIpAddress);
	lsReach.appendTLV(lnlri);			//Link NLRI is transported in the "opaque" attribute named MP_Reach_NLRI
	UpdateMessage update;
	update.appendAttribute(Origin(Origin::Incomplete));
	update.appendAttribute(ASPath());
  // Ericsson fix start
  update.appendAttribute(LocalPref(1));
  // Ericsson fix end
	update.appendAttribute(lsReach);	//Finally we put this whole shit into an update message...

	return update;
}

UpdateMessage FakeBGPLS::createSimplePrefixUpdate(LocalNodeDescriptor lnd, const FakeBGPLS::Prefix_v4& prefix, boost::asio::ip::address_v4& ipAddress) {
    IPReachability ipReach(prefix.address, prefix.len);

    Prefixv4NLRI pnlri(1,0);
    pnlri.appendData(lnd.startPointer(), lnd.getFullSize());
    pnlri.appendData(ipReach.startPointer(), ipReach.getFullSize());

    LSMPReach lsReach(ipAddress);
    lsReach.appendTLV(pnlri);
    UpdateMessage update;
    update.appendAttribute(Origin(Origin::Incomplete));
    update.appendAttribute(ASPath());
    // Ericsson fix start
     update.appendAttribute(LocalPref(1));
    // Ericsson fix end
    update.appendAttribute(lsReach);    //Finally we put this whole shit into an update message...

    return update;
}

int FakeBGPLS::run() {
	uint8_t recBuff[65536];
	int sockfd, conSockfd;
	struct sockaddr_in serv_addr, cli_addr;

	//Do not crash when sigpipe fails
	signal(SIGPIPE, SIG_IGN);

	//Open the socket. - v4 TCP
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	//for quick kill and restart (before TIME_WAIT expires)
	int enable = 1;
	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0) {
		std::cout << "setsockopt(SO_REUSEADDR) failed" << std::endl;
		return -1;
	}

	//We'll need an address, but not everything - some parts will be left 0
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);
	serv_addr.sin_addr.s_addr = inet_addr(binding_address.c_str());
	if (bind(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr)))
	{
		std::cout << "Cannot bind. Exiting." << std::endl;
		return -1;
	}

	while(1) {
		std::cout << "Socket is open, waiting for connection from ODL." << std::endl;

		//Now, listen until someone connects
		listen(sockfd, 5);
		socklen_t clilen = sizeof(cli_addr);
		conSockfd = accept(sockfd, (struct sockaddr*) &cli_addr, &clilen);

		//Set the timeout to 10s
		struct timeval to;
		to.tv_sec = 10;
		to.tv_usec = 0;
		setsockopt(conSockfd, SOL_SOCKET, SO_RCVTIMEO, &to, sizeof(struct timeval));

		//Wait a second... just for fun.
		sleep(1);

		std::cout << "TCP connection is OK. Sending Open." << std::endl;


		OpenMessage open(bgp_id);
		write(conSockfd, open.getMessage(), open.getSize());

		if (read(conSockfd, recBuff, sizeof(recBuff))<=0) {
			std::cout << "Open from the other side was not received in time. Halting." << std::endl;
			return -1;
		}

		std::cout << "Something was received - hopefully the Open message. Send a KeepAlive to move other side OPENCONFIRM->ESTABLISH" << std::endl;

		KeepAlive keepAlive;
		write(conSockfd, keepAlive.getMessage(), keepAlive.getSize());
		time_t lastKeepAliveSent;
		time(&lastKeepAliveSent);

		//Read the messages - there might be some KeepAlive from the other side.
		read(conSockfd, recBuff, sizeof(recBuff));

		std::cout << std::hex;

		//Nodes
		for (lemon::ListDigraph::NodeIt it(network); it != lemon::INVALID; ++it) {

			std::cout << "Creating node: " << loopbackAddress[it] << std::endl;
			UpdateMessage nodeMsg = createSimpleNodeUpdate(createNodeDescriptor<LocalNodeDescriptor>(routerId[it], as[it], bgpLsId[it], area[it]), loopbackAddress[it]);

			//Add some IPv4 loopback to the node (BGP-LS calls that Ipv4RouterID
			IPv4RouterID ipv4RouterID(loopbackAddress[it]);
			BGPLSAttribute lsAttrib(proto_profile == 1 ? 99 : 29);
			lsAttrib.appendTLV(ipv4RouterID);
			nodeMsg.appendAttribute(lsAttrib);

			write(conSockfd, nodeMsg.getMessage(), nodeMsg.getSize());
		}

		//Links
		for (lemon::ListDigraph::ArcIt it(network); it != lemon::INVALID; ++it) {
			std::cout << "Creating arc: " <<  loopbackAddress[network.source(it)] << " -> " << loopbackAddress[network.target(it)] << std::endl;
			UpdateMessage arcMsg = createSimpleArcUpdate(
			        createNodeDescriptor<LocalNodeDescriptor>(routerId[network.source(it)], as[network.source(it)], bgpLsId[network.source(it)], area[network.source(it)]),
			        createNodeDescriptor<RemoteNodeDescriptor>(routerId[network.target(it)], as[network.target(it)], bgpLsId[network.target(it)], area[network.target(it)]),
			        loopbackAddress[network.source(it)],
			        0, 0,
			        srcAddress[it], srcAddress[revert(network, it)]);

			//Pimp up this message a little bit
			AdministrativeGroup administrativeGroupTlv(0);
			MaxReservableBandwidth resMaxBwTlv(bw[it]);
			MaximumLinkBandwidth maxBwTlv(bw[it]);
			float* f = new float[8];
			for (int i = 0; i < 8; i++) f[i] = bw[it];
			UnreservedBandwidth unresBdwTlv(f);
			Metric metricTlv(cost[it]);
			TeMetric teMetricTlv(cost[it]); // Ericsson: added te default metric

			BGPLSAttribute lsAttrib(proto_profile == 1 ? 99 : 29);
			lsAttrib.appendTLV(administrativeGroupTlv);
			lsAttrib.appendTLV(maxBwTlv);
			lsAttrib.appendTLV(resMaxBwTlv);
			lsAttrib.appendTLV(unresBdwTlv); // Ericsson: added unreserved bandwidth
			lsAttrib.appendTLV(metricTlv);
			lsAttrib.appendTLV(teMetricTlv);
			if (proto_profile == 1) {
                UnidirectionalLinkDelay linkDelay(0, delay[it]);
                lsAttrib.appendTLV(linkDelay);
			} else {
                UnidirectionalLinkDelay linkDelay(0, delay[it], 1104);
                lsAttrib.appendTLV(linkDelay);
            }

      if (proto_profile == 2) {
        /* IPOS defaults to V=1, L=1 (0x30) and SID as value (i.e. label) */
        AdjacencySID adjacencySid(0x30, true, adjSids[it]);
        lsAttrib.appendTLV(adjacencySid);
      }

			arcMsg.appendAttribute(lsAttrib);

			write(conSockfd, arcMsg.getMessage(), arcMsg.getSize());
		}

        std::cout << std::dec;
		//Prefixes - first the loopback with the
		for (lemon::ListDigraph::NodeIt it(network); it != lemon::INVALID; ++it) {
	        std::cout << "Sending loopback prefix " << loopbackAddress[it] << "/32" " with node SID " << nodeSids[it] << std::endl;

	        UpdateMessage prefMsg = createSimplePrefixUpdate(createNodeDescriptor<LocalNodeDescriptor>(routerId[it], as[it], bgpLsId[it], area[it]),
	                                                            Prefix_v4(loopbackAddress[it], 32), loopbackAddress[it]);


          if (proto_profile == 1) {
            PrefixMetric prefixMetric(0);
            PrefixSID prefixSid(0xc0, nodeSids[it]);
            BGPLSAttribute lsAttrib(99);
            lsAttrib.appendTLV(prefixMetric);
            lsAttrib.appendTLV(prefixSid);
            prefMsg.appendAttribute(lsAttrib);
          } else if (proto_profile == 2) {
            PrefixMetric prefixMetric(0);
            PrefixSID prefixSid(0x60, nodeSids[it], true);
            BGPLSAttribute lsAttrib(29);
            lsAttrib.appendTLV(prefixMetric);
            lsAttrib.appendTLV(prefixSid);
            prefMsg.appendAttribute(lsAttrib);
          }

	        write(conSockfd, prefMsg.getMessage(), prefMsg.getSize());
		}

		//Now the remaining prefixes
		for (lemon::ListDigraph::NodeIt it(prefixes); it != lemon::INVALID; ++it) {
		    //Find the node
		    auto node = label2Node[nodeId[it]];
		    boost::asio::ip::address_v4 nh = nhop[it];
		    if (nh.to_ulong() == 0)
		        nh = loopbackAddress[node];

		    std::cout << "Sending prefix " << prefVal[it].address << "/" << prefVal[it].len << " for " << loopbackAddress[node] << " with SID " << prefSids[it] << " nh ip: " << nh.to_string() << "." << std::endl;

            UpdateMessage prefMsg = createSimplePrefixUpdate(createNodeDescriptor<LocalNodeDescriptor>(routerId[node], as[node], bgpLsId[node], area[node]),
                                                                Prefix_v4(prefVal[it]), nh);

            if (proto_profile == 1) {
	      PrefixMetric prefixMetric(prefCosts[it]);
	      PrefixSID prefixSid(0x80, prefSids[it]);
	      BGPLSAttribute lsAttrib(99);
	      lsAttrib.appendTLV(prefixMetric);
	      lsAttrib.appendTLV(prefixSid);
	      prefMsg.appendAttribute(lsAttrib);
	    } else if (proto_profile == 2) {
	      PrefixMetric prefixMetric(prefCosts[it]);
	      PrefixSID prefixSid(0x20, prefSids[it], true);
	      BGPLSAttribute lsAttrib(29);
	      lsAttrib.appendTLV(prefixMetric);
	      lsAttrib.appendTLV(prefixSid);
	      prefMsg.appendAttribute(lsAttrib);
	    }

            write(conSockfd, prefMsg.getMessage(), prefMsg.getSize());
		}

		//TODO: advertise the adjacency segments

		std::cout << std::dec;

		std::cout << "Update was sent. Starting to send KeepAlive regularly." << std::endl;

		//Infinite loop to keep up connection - I hope that messages won't be removed too soon without updates...

		time_t currentTime;
		while(1) {
			//Do we need to send a KeepAlive?
			time(&currentTime);
			if (difftime(currentTime, lastKeepAliveSent) >= 30) {
				if (write(conSockfd, keepAlive.getMessage(), keepAlive.getSize()) < 0) {
					std::cout << "Something bad has happened, write failed. Restarting. errno=" << errno << std::endl;
					break;
				}
				time(&lastKeepAliveSent);
			}

			//Read the KeepAlive of the other side. Timeout is not a problem!
			int ret = read(conSockfd, recBuff, sizeof(recBuff));
			if (ret == 0) {
				std::cout << "Connection closed. Restarting." << std::endl;
				break;
			}
			if (ret < 0 && errno != EAGAIN) {
				std::cout << "Something bad has happened, read failed. Restarting. errno=" << errno << std::endl;
				break;
			}
		}

		close(conSockfd);
	}
	return 0; //Never reach
}


uint32_t FakeBGPLS::ipConv(const std::string& str) {
		struct in_addr addr;
		if (inet_pton(AF_INET, str.c_str(), &addr) != 1)
			throw;

		return ntohl(addr.s_addr);
}


std::istream& operator>>(std::istream& is, FakeBGPLS::IsoNodeId& isoId) {

    std::string rest;
    is >> rest;

    std::vector<std::string> splitres;
    boost::split(splitres, rest, boost::is_any_of(":"));
    if (splitres.size() != 3)
        throw std::string("CLNP node address must be 3x2 bytes.");

    unsigned cnt = 0;
    for (auto num : splitres) {
        std::stringstream strstr(num);
        uint16_t val;
        strstr >> std::hex >> val;

        ((uint16_t*) isoId.value)[cnt++] = htons(val);
    }

    return is;
}

std::istream& operator>>(std::istream& is, boost::asio::ip::address_v4& ipv4) {

    std::string rest;
    is >> rest;
    ipv4 = boost::asio::ip::address_v4::from_string(rest);

    return is;
}

std::istream& operator>>(std::istream& is, FakeBGPLS::Prefix_v4& pref) {

    std::string rest;
    is >> rest;
    pref = FakeBGPLS::Prefix_v4(rest);

    return is;
}
