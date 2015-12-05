
#include "MPRNG.h"
#include "config.h"

#include "Printer.h"

#include <iostream>
using namespace std;

MPRNG rng;


void uMain::main() {

	int seed = pid();
	String configFile = "soda.config";

	switch (argc) {
		case 3:
			seed = atoi(argc[2]);
		case 2:
			configFile = argv[1];
		case 1:
			break;
		default:
	}

	ConfigParms params;
	processConfigFile(configFile, params);
	rng.seed(seed);

	// todo
} 
