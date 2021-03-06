#include "Truck.h"
#include "MPRNG.h"
#include "VendingMachine.h"
#include "debug.h"


Truck::Truck( Printer &prt, NameServer &nameServer, BottlingPlant &plant,
           unsigned int numVendingMachines, unsigned int maxStockPerFlavour )
           : prt(prt), nameServer(nameServer), plant(plant), 
           numVendingMachines(numVendingMachines), maxStockPerFlavour(maxStockPerFlavour), nextMachineToStock(0) {
}



void Truck::main() {
	prt.print(Printer::Truck, 'S');

	try {

		// get machines
		VendingMachine** machines = nameServer.getMachineList();

		for ( ;; ) {
			// get coffee
			yield(rng(1, 10));

			// get shipment
			unsigned int cargo[VendingMachine::NUM_FLAVOUR];
			unsigned int totalBottles = 0;
			plant.getShipment(cargo);
			for (unsigned int i = 0; i < VendingMachine::NUM_FLAVOUR; i++) {
				totalBottles += cargo[i];
			}
			prt.print(Printer::Truck, 'P', totalBottles);

			// deliver
			for (unsigned int i = 0; i < numVendingMachines; i++) {

				if (totalBottles <= 0) break;

				VendingMachine *machine = machines[nextMachineToStock];
				prt.print(Printer::Truck, 'd', machine->getId(), totalBottles);

				// fill machine
				unsigned int * inventory = machine->inventory();
				unsigned int unfilled = 0;
				for (unsigned int i = 0; i < VendingMachine::NUM_FLAVOUR; i++) {
					unsigned int spaceInMachine = maxStockPerFlavour - inventory[i];
					unsigned int addBottles = std::min(spaceInMachine, cargo[i]);

					inventory[i] += addBottles;
					cargo[i] -= addBottles;
					totalBottles -= addBottles;
					if (maxStockPerFlavour > inventory[i]) unfilled += maxStockPerFlavour - inventory[i];

				}

				if (unfilled > 0) {
					prt.print(Printer::Truck, 'U', machine->getId(), unfilled);
				}


				prt.print(Printer::Truck, 'D', machine->getId(), totalBottles);

				machine->restocked();
				nextMachineToStock = (nextMachineToStock + 1) % numVendingMachines;
			}


		}
	} catch (BottlingPlant::Shutdown& e) {
		// stop truck
	}
	prt.print(Printer::Truck, 'F');
}