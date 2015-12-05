#include "debug.h"
#include "Printer.h"
#include "BottlingPlant.h"

#include "MPRNG.h"


MPRNG rng;



void uMain::main() {

	Printer printer(2, 2, 1);

	BottlingPlant *plant = new BottlingPlant(printer, 2, 3, 3, 10);
	
	unsigned int cargo[4];
	cargo[0] = 3;
	cargo[1] = 3;
	cargo[2] = 3;
	cargo[3] = 3;

	yield(30);
	plant->getShipment(cargo);
	
	cargo[0] = 3;
	cargo[1] = 3;
	cargo[2] = 3;
	cargo[3] = 3;
	yield(40);
	plant->getShipment(cargo);

	cargo[0] = 3;
	cargo[1] = 3;
	cargo[2] = 3;
	cargo[3] = 3;
	yield(10);
	plant->getShipment(cargo);

	cargo[0] = 3;
	cargo[1] = 3;
	cargo[2] = 3;
	cargo[3] = 3;
	yield(30);
	plant->getShipment(cargo);

	delete plant;
} 
