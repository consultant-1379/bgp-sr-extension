#!/bin/sh
cd opendaylight/bgpcep
mvn -s ../../build/settings.xml clean install -DskipTests
