#include "BottlingPlant.h"


BottlingPlant::BottlingPlant( Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
             unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
             unsigned int timeBetweenShipments ) 
				: prt(prt), nameServer(nameServer), numVendingMachines(numVendingMachines), 
				maxShippedPerFlavour(maxShippedPerFlavour), maxStockPerFlavour(maxStockPerFlavour),
				timeBetweenShipments(timeBetweenShipments)
			{

}


void BottlingPlant::getShipment( unsigned int cargo[] ) {

}

void BottlingPlant::main() {

}