#include "debug.h"
#include "Printer.h"
#include "NameServer.h"
#include "BottlingPlant.h"
#include "VendingMachine.h"

#include "MPRNG.h"

MPRNG rng;

void uMain::main() {
	unsigned int students = 0;
	unsigned int machines = 1;
	unsigned int maxShipped = 3;
	unsigned int maxStock = 5;
	unsigned int timeBetweenShipment = 3;
	unsigned int sodaCost = 2;

	Printer printer(students, machines, 0);

	NameServer nameServer(printer, machines, students);


	VendingMachine *vendingMachines[machines];
	for (unsigned int i = 0; i < machines; i++) {
		vendingMachines[i] = new VendingMachine(printer, nameServer, i, sodaCost, maxStock);
	}

	
	BottlingPlant *plant = new BottlingPlant(printer, nameServer, machines, maxShipped, maxStock, timeBetweenShipment);

	yield(100);
	// done....
	for (unsigned int i = 0; i < machines; i++) {
		delete vendingMachines[i];
	}
	delete plant;
} 
