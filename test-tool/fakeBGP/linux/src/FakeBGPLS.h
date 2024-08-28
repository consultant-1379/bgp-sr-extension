/*
 * FakeBGP.h
 *
 *  Created on: Mar 5, 2014
 *      Author: egboeny
 */

#ifndef FAKEBGP_H_
#define FAKEBGP_H_

#include <vector>

#include "Messages/UpdateMessage.h"
#include <lemon/lgf_reader.h>
#include <lemon/list_graph.h>
#include <iostream>
#include <list>
#include <map>
#include <boost/asio/ip/address_v4.hpp>
#include <boost/algorithm/string.hpp>

#include "Messages/Attributes/LS_TLV/AS.h"
#include "Messages/Attributes/LS_TLV/BgpLsId.h"
#include "Messages/Attributes/LS_TLV/IGPRouterID.h"
#include "Messages/Attributes/LS_TLV/Area.h"
#include "Messages/Attributes/LS_TLV/NodeDescriptor.h"


class FakeBGPLS {
/*	struct Adj {
		uint32_t source;
		uint32_t target;
		uint32_t bw;
		uint32_t cost;
	};

	std::vector<uint32_t> nodes;
	std::vector<Adj> adjs;*/
public:
	struct IsoNodeId {
		uint8_t value[6];
	};

	struct Prefix_v4 {
	    boost::asio::ip::address_v4 address;
	    unsigned len;

	    Prefix_v4() :
            len(0)
        {}

	    Prefix_v4(const boost::asio::ip::address_v4 address, uint8_t len) :
	        address(address),
	        len(len)
	    { }

	    Prefix_v4(const std::string& str) : len(0) {
            std::vector<std::string> strs;
	        boost::split(strs, str, boost::is_any_of("/"));
	        if (strs.size() != 2)
	            throw std::string("Format error!");

	        address = boost::asio::ip::address_v4::from_string(strs[0]);
	        std::stringstream(strs[1]) >> len;
	    }
	};

protected:
	lemon::ListDigraph network;

	lemon::ListDigraph::NodeMap<uint32_t> label;
	lemon::ListDigraph::NodeMap<uint32_t> as;
	lemon::ListDigraph::NodeMap<uint32_t> bgpLsId;
	lemon::ListDigraph::NodeMap<IsoNodeId> routerId;
	lemon::ListDigraph::NodeMap<uint32_t> area;
	lemon::ListDigraph::NodeMap<boost::asio::ip::address_v4> loopbackAddress;
	lemon::ListDigraph::NodeMap<uint32_t> nodeSids;
	lemon::ListDigraph::ArcMap<uint32_t> cost;
	lemon::ListDigraph::ArcMap<uint32_t> bw;
	lemon::ListDigraph::ArcMap<uint32_t> delay;
	lemon::ListDigraph::ArcMap<uint32_t> adjSids;
	lemon::ListDigraph::ArcMap<boost::asio::ip::address_v4> srcAddress;

	std::map<uint32_t, lemon::ListDigraph::Node> label2Node;

	lemon::ListDigraph prefixes;
	lemon::ListDigraph::NodeMap<uint32_t> nodeId;
	lemon::ListDigraph::NodeMap<Prefix_v4> prefVal;
	lemon::ListDigraph::NodeMap<uint32_t> prefSids;
	lemon::ListDigraph::NodeMap<uint32_t> prefCosts;
	lemon::ListDigraph::NodeMap<boost::asio::ip::address_v4> nhop;

  // BGP data
  std::string bgp_id;

  // bindind address
  std::string binding_address;

  // SERVER port
  unsigned int port = 179;

  // protocol profile
  unsigned int proto_profile = 2;

	template <typename NodeDescriptorType>
	NodeDescriptorType createNodeDescriptor(IsoNodeId& isoAddress, uint32_t as, uint32_t bgpLsId, uint32_t area) {
	    AS astlv(as);
	    BgpLsId bgplsidtlv(bgpLsId);
	    Area areatlv(area);
	    IGPRouterID ndstlv(isoAddress.value, sizeof(isoAddress.value));

	    NodeDescriptorType nd;
	    nd.appendData(astlv.startPointer(), astlv.getFullSize());
	    nd.appendData(bgplsidtlv.startPointer(), bgplsidtlv.getFullSize());
	    nd.appendData(areatlv.startPointer(), areatlv.getFullSize());
	    nd.appendData(ndstlv.startPointer(), ndstlv.getFullSize());

	    return nd;
	}

	UpdateMessage createSimpleNodeUpdate(const LocalNodeDescriptor& lnd, boost::asio::ip::address_v4& ipAddress);
	UpdateMessage createSimpleArcUpdate(
	                    const LocalNodeDescriptor& lnd,
	                    const RemoteNodeDescriptor& rnd,
	                    boost::asio::ip::address_v4& sIpAddress,
	                    uint32_t sid, uint32_t tid,
	                    boost::asio::ip::address_v4& interfaceAddress, boost::asio::ip::address_v4& neighborAddress);
	UpdateMessage createSimplePrefixUpdate(LocalNodeDescriptor lnd, const Prefix_v4& prefix, boost::asio::ip::address_v4& ipAddress);

	uint32_t ipConv(const std::string& str);

public:

	FakeBGPLS(const std::string&, const std::string&, std::string, unsigned int port = 179, unsigned int proto_profile = 2);
	virtual ~FakeBGPLS();
	FakeBGPLS(lemon::ListDigraph& transport, lemon::DigraphReader<lemon::ListDigraph>& loader);

	int run();
};

//std::istream& operator>>(std::istream& is, const FakeBGPLS::IsoNodeId& isoId);

#endif /* FAKEBGP_H_ */
