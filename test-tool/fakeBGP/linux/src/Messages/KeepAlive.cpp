/*
 * KeepAlive.cpp
 *
 *  Created on: Feb 5, 2014
 *      Author: egboeny
 */

#include "KeepAlive.h"
#include <string.h>

KeepAlive::KeepAlive() {
StaticMessage binary_message =  {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, //Init
			 	    	 	   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	 	 	  	 	 	 	   //len=19B | type=4=KeepAlive
	 	 	 	 	 	 	   0x00, 0x13, 04 };

memcpy(this->binary_message, binary_message, sizeof(StaticMessage));
}

KeepAlive::~KeepAlive() {
	// TODO Auto-generated destructor stub
}

