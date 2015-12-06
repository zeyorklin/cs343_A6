#include "VendingMachine.h"
#include "Printer.h"

VendingMachine::VendingMachine( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost,
                unsigned int maxStockPerFlavour ) :prt(prt), nameServer(nameServer), id(id), sodaCost(sodaCost),
                maxStockPerFlavour(maxStockPerFlavour) {
    stock = new unsigned int[Flavours::NUM_FLAVOUR];
    for (unsigned int i = 0; i < Flavours::NUM_FLAVOUR; i++) {
    	stock[i] = 0;
    }
    nameServer.VMregister(this);

}


void VendingMachine::buy( Flavours flavour, WATCard &card ) {
	if (stock[flavour] == 0) {
		state = STOCK;
	} else if (card.getBalance() < sodaCost) {	
		state = FUND;
	} else {
		state = BUY;
		buyFlavour = flavour;
		buyCard = &card; 
	}
	studentTask = &uThisTask();
	done.wait();
}


unsigned int *VendingMachine::inventory() {
	prt.print(Printer::Vending, id, 'r');
	stocking = true;
	return stock;
}

void VendingMachine::restocked() {
	prt.print(Printer::Vending, id, 'R');
	stocking = false;
}


_Nomutex unsigned int VendingMachine::cost() {
	return sodaCost;
}


_Nomutex unsigned int VendingMachine::getId() {
	return id;
}


void VendingMachine::main() {
	prt.print(Printer::Vending, id, 'S', sodaCost);

	for ( ;; ) {
		_Accept(~VendingMachine) {
			break;
		} or _Accept(inventory, restocked) {

		} or _When(!stocking) _Accept(buy) {
			switch (state) {
				case FUND:
					_Resume Funds() _At *studentTask;
					break;
				case STOCK:
					_Resume Stock() _At *studentTask;
					break;
				case BUY:
					buyCard->withdraw(sodaCost);
					stock[buyFlavour]--;
					prt.print(Printer::Vending, id, 'B', buyFlavour, stock[buyFlavour]);
					break;
			}
			done.signalBlock();
		}
	}

	prt.print(Printer::Vending, id, 'F');
}


VendingMachine::~VendingMachine() {

}