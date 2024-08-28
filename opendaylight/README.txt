>>> Ericsson updates <<<<

The following updates have been implemented for bgpcep:

$ git status .
On branch stable/carbon
Your branch is up-to-date with 'origin/stable/carbon'.
Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git checkout -- <file>..." to discard changes in working directory)

        modified:   bgp/linkstate/src/main/java/org/opendaylight/protocol/bgp/linkstate/impl/attribute/LinkAttributesParser.java
        modified:   bgp/linkstate/src/main/yang/bgp-linkstate.yang
        modified:   bgp/topology-provider/src/main/java/org/opendaylight/bgpcep/bgp/topology/provider/LinkstateTopologyBuilder.java

Untracked files:
  (use "git add <file>..." to include in what will be committed)

        bgp/topology-provider/src/main/yang/sr-poc-topology.yang

no changes added to commit (use "git add" and/or "git commit -a")

The involved bgpcep (sub)projects are:

    * bgp-linkstate
    * bgp-topology-provider

The bgp-linkstate project provides capability of handling BGP PDU and the TLV (Type-Length-Attribute) attributes in order to 
parse their content to populate the Adj-Rib. That can be applied in both IS-IS and OSPF scenarios.

The bgp-topology-provider project parses the Local RIB content and populate a network topology. As a result, the SDN controller
exports northbound the datastore where such topology is stored into. Nodes, termination-points and links have attributes associated
to, reporting traffic-engineering and segment-routing info as well.

The bgp-linkstate.yang model defines the link-state path attributes for node, link, prefix and te-lsp. Within the the link state
attribute, the Ericsson updates add the average unidirectional link delay (https://tools.ietf.org/html/rfc7810#section-4.1).

The LinkAttributesParser.java has been updated to also parse the TLV associated with the unidirectional link delay and store it
into the Adj-RIB.

The sr-poc-topology.yang model has been added to the bgp-topology-provider project to augment some network topology prefix and
traffic engineering (TED) attributes with segment routing info. In the specific:

    * the IGP node attribute prefix is augmented with the prefix SID
    * the IS-IS TED link attributes are augmented with the unidirectional link delay and adjacency SID
    * the OSPF TED link attributes are augmented with the unidirectional link delay

The purpose is to target the IS-IS scenario specifically. Those augmented attributes are part of the network-topology build
up by the BGP plug-in.

The LinkstateTopologyBuilder.java has been enhanced in order to populate abovementioned augmentation with the related info
coming from the LOC-RIB. As a result, within the resulting network topology, link and node segment routing data can be found.
