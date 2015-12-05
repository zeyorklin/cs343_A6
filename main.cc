
#include "MPRNG.h"
#include "config.h"

#include "Printer.h"

#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
#include <cstdlib>	

MPRNG rng;

bool convert( int &val, char *buffer ) {		// convert C string to integer
    std::stringstream ss( buffer );			// connect stream and buffer
    ss >> dec >> val;					// convert integer from buffer
    return ! ss.fail() &&				// conversion successful ?
	// characters after conversion all blank ?
	string( buffer ).find_first_not_of( " ", ss.tellg() ) == string::npos;
} // convert

enum { sizeDeflt = 20, codeDeflt = 5 };	

void usage( char *argv[] ) {
    cerr << "Usage: " << argv[0] << endl;
    exit( EXIT_FAILURE );				// TERMINATE
} // usage

void uMain::main() {

	int seed = getpid();
	string configFile = "soda.config";

	switch (argc) {
		case 3:
	        if ( ! convert( seed, argv[2] ) || seed < 0 ) {	// invalid integer ?
		    	usage( argv );
			} // if
		case 2:
			configFile = argv[1];
		case 1:
			break;
		default:
			// error
			break;
	}

	ConfigParms params;
	processConfigFile(configFile.c_str(), params);
	rng.seed(seed);

	// todo
	
} 
