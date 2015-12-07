
#include "MPRNG.h"
#include "config.h"

#include "Printer.h"
#include "Bank.h"
#include "Parent.h"
#include "WATCardOffice.h"
#include "NameServer.h"
#include "VendingMachine.h"
#include "BottlingPlant.h"
#include "Student.h"
#include "Groupoff.h"

#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
#include <cstdlib>	

#include "debug.h"

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
    cerr << "Usage: " << argv[0] << " [ config-file [ seed > 0]" << endl;
    exit( EXIT_FAILURE );				// TERMINATE
} // usage

void uMain::main() {

	int seed = getpid();
	string configFile = "soda.config";

	switch (argc) {
		case 3:
	        if ( ! convert( seed, argv[2] ) || seed <= 0 ) {	// invalid integer ?
		    	usage( argv );
			} // if
		case 2:
			configFile = argv[1];
		case 1:
			break;
		default:
			usage( argv );
			break;
	}

	ConfigParms params;
	processConfigFile(configFile.c_str(), params);

	D(cout << "Config:" << endl << "sodaCost:" << params.sodaCost  << endl
    		<< "numStudents: " << params.numStudents << endl
    		<< "maxPurchases: " << params.maxPurchases << endl
    		<< "numVendingMachines: " << params.numVendingMachines << endl
    		<< "maxStockPerFlavour: " << params.maxStockPerFlavour << endl
    		<< "maxShippedPerFlavour: " << params.maxShippedPerFlavour << endl
    		<< "timeBetweenShipments: " << params.timeBetweenShipments << endl
    		<< "groupoffDelay: " << params.groupoffDelay << endl
    		<< "parentalDelay: " << params.parentalDelay << endl
    		<< "numCouriers: " << params.numCouriers << endl;
		);

	rng.seed(seed);


	// start tasks
	Printer printer(params.numStudents, params.numVendingMachines, params.numCouriers);
	Bank bank(params.numStudents);

	Parent *parent = new Parent(printer, bank, params.numStudents, params.parentalDelay);

	Groupoff *groupoff = new Groupoff(printer, params.numStudents, params.sodaCost, params.groupoffDelay);

	WATCardOffice *cardOffice = new WATCardOffice(printer, bank, params.numCouriers);

	NameServer *nameServer = new NameServer(printer, params.numVendingMachines, params.numStudents);

	VendingMachine *vendingMachines[params.numVendingMachines];

	for (unsigned int i = 0; i < params.numVendingMachines; i++) {
		vendingMachines[i] = new VendingMachine(printer, *nameServer, i, 
												params.sodaCost, params.maxStockPerFlavour);
	}

	BottlingPlant *bottlingPlant = new BottlingPlant(printer, *nameServer, 
													params.numVendingMachines, params.maxShippedPerFlavour, 
													params.maxStockPerFlavour, params.timeBetweenShipments);

	
	Student *students[params.numStudents];
	for (unsigned int i = 0; i < params.numStudents; i++) {
		students[i] = new Student(printer, *nameServer, *cardOffice, *groupoff, i, params.maxPurchases);
	}



	// finish
	for (unsigned int i = 0; i < params.numStudents; i++) {
		delete students[i];
	}

	delete bottlingPlant;

	for (unsigned int i = 0; i < params.numVendingMachines; i++) {
		delete vendingMachines[i];
	}

	delete nameServer;
	delete cardOffice;
	delete groupoff;
	delete parent;
	


} 
