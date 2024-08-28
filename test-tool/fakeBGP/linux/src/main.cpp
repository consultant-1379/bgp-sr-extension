/*
 * main.cpp
 *
 *  Created on: Feb 5, 2014
 *      Author: egboeny
 */

#include "FakeBGPLS.h"
#include <iostream>
#include <cstdlib>

static void usage() {
  std::cout << "fakebgp <lgt-file> [<bgp-id>] [<binding-address-port>] [<proto-profile>]" << std::endl;
  std::cout << "- lgf-file: name of the lgf file." << std::endl;
  std::cout << "- bgp-id: bgp identifier (default 172.16.77.09)." << std::endl;
  std::cout << "- binding-address-port: binding address and port (default INADDR_ANY:179)." << std::endl;
  std::cout << "- proto-profile: 1/2 (default 2)." << std::endl;
}

int main(int argc, char* argv[]) {
  std::string bgp_id;
  std::string lgf_file;
  unsigned int binding_port;
  std::string binding_address;
  unsigned int proto_profile;
  if ( argc > 1 ) {
    std::size_t help = strncmp(argv[1],"-h", strlen("-h"));
    if ( help == 0 ) {
      usage();
      return 0;
    }
    help = strncmp(argv[1],"--help", strlen("--help"));
    if ( help == 0 ) {
      usage();
      return 0;
    }
    lgf_file = argv[1];
    if ( argc > 2 ) {
      bgp_id = argv[2];
    }
    else {
      bgp_id = "172.16.77.09";
    }
    if (argc > 3) {
      // supported syntaxes are a) 179, b) :179, c) 127.0.0.1:179
      std::string arg3 = argv[3];
      std::string delimiter = ":";
      if (arg3.find(delimiter) == std::string::npos) {
        // no ':' found just a number, legacy syntax
        binding_port = (unsigned int)std::stoi(argv[3]);
      } else {
        binding_address = arg3.substr(0, arg3.find(delimiter));
        arg3.erase(0, arg3.find(delimiter) + delimiter.length());
        binding_port = (unsigned int)std::stoi(arg3.c_str());
      }
    } else {
      binding_port = 179;
    }

    binding_address = "0.0.0.0";

    if (argc > 4) {
      proto_profile = (unsigned int)std::stoi(argv[4]);
    } else {
      proto_profile = 2;
    }

    try {
      std::cout << "Launch" << std::endl;
      return FakeBGPLS(lgf_file, bgp_id, binding_address, binding_port, proto_profile).run();
    } catch (std::string& str) {
      std::cout << "Finished with exception. Reason: " << str << std::endl;
    }
  }
  else {
    std::cout << "Wrong number of parameters" << std::endl;
    usage();
    return -1;
  }

	return 0;
}
