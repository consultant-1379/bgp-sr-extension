#!/bin/sh
rm -rf $2/system/org/opendaylight/bgpcep/bgp-topology-provider
rm -rf $2/system/org/opendaylight/bgpcep/bgp-linkstate
cp -rf $1/opendaylight/bgp-updated-artifacts/bgp-topology-provider $2/system/org/opendaylight/bgpcep/bgp-topology-provider
cp -rf $1/opendaylight/bgp-updated-artifacts/bgp-linkstate $2/system/org/opendaylight/bgpcep/bgp-linkstate