#include "BottlingPlant.h"
#include "Printer.h"
#include "MPRNG.h"
#include "Truck.h"
#include "VendingMachine.h"
#include "debug.h"

BottlingPlant::BottlingPlant( Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
             unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
             unsigned int timeBetweenShipments ) 
				: prt(prt), nameServer(nameServer), numVendingMachines(numVendingMachines), 
				maxShippedPerFlavour(maxShippedPerFlavour), maxStockPerFlavour(maxStockPerFlavour),
				timeBetweenShipments(timeBetweenShipments), shutdown(false)
{
	stock = new unsigned int[VendingMachine::NUM_FLAVOUR];
	for (unsigned int i = 0; i < VendingMachine::NUM_FLAVOUR; i++) {
		stock[i] = 0;
	}
}


void BottlingPlant::getShipment( unsigned int cargo[] ) {
	if (shutdown) {
		uRendezvousAcceptor();
		_Throw Shutdown();
	}

	for (unsigned int i = 0; i < VendingMachine::NUM_FLAVOUR; i++) {
		cargo[i] = stock[i];
		stock[i] = 0;
	}

	prt.print(Printer::BottlingPlant, 'P');
}

BottlingPlant::~BottlingPlant() {
	delete[] stock;
}

void BottlingPlant::main() {
	prt.print(Printer::BottlingPlant, 'S');
	Truck truck(prt, nameServer, *this, numVendingMachines, maxStockPerFlavour);

	for ( ;; ) {

		// production run
		unsigned int bottlesProduced = 0;
		for (unsigned int i = 0; i < (unsigned int)VendingMachine::NUM_FLAVOUR; i++) {
			stock[i] = rng(maxShippedPerFlavour);
			bottlesProduced += stock[i];
		}
		prt.print(Printer::BottlingPlant, 'G', bottlesProduced);

		// wait for production
		yield(timeBetweenShipments);

		// wait for truck
		_Accept(getShipment) {

		} or _Accept(~BottlingPlant) {
			shutdown = true;
			break;
		}
	}

	prt.print(Printer::BottlingPlant, 'F');
	
	_Accept(getShipment);

}

