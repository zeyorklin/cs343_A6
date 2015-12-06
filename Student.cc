#include "Student.h"
#include "VendingMachine.h"
#include "WATCard.h"
#include "MPRNG.h"
#include "WATCardOffice.h"


Student::Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, Groupoff &groupoff, unsigned int id, unsigned int maxPurchases ) 
				: prt(prt), nameServer(nameServer), cardOffice(cardOffice), groupoff(groupoff), id(id), maxPurchases(maxPurchases) {
	
}



void Student::main() {

	int startBalance = 5;

	purchase = rng(1, maxPurchases);
	flavour = (VendingMachine::Flavours)rng(VendingMachine::Flavours::NUM_FLAVOUR -1);

	prt.print(Printer::Student, id, 'S', flavour, purchase);

	// create card

	WATCard::FWATCard card = cardOffice.create(id, startBalance);

	
	//WATCard::FWATCard gift = groupoff.giftCard();
	//prt.print(Printer::Student, id, 'G');

	// get machine location
	VendingMachine *machine = nameServer.getMachine(id);
	prt.print(Printer::Student, id, 'V', machine->getId());	
	
	for (unsigned int purchased = 0; purchased < purchase; ) {
		
		try {
			_Enable {
				//_Select(gift || card);
				/*
				if (gift.available()) {
					machine->buy(flavour, *(gift()));
					prt.print(Printer::Student, id, 'G', gift()->getBalance());
					gift.reset();
					purchased++;
				} else if (gift.available()) {}*/
				machine->buy(flavour, *(card()));
				prt.print(Printer::Student, id, 'B', card()->getBalance());
				yield(rng(1, 10));
				purchased++;
			}
			
		} catch (WATCardOffice::Lost &e) {
			prt.print(Printer::Student, id, 'L');
			card = cardOffice.create(id, startBalance);
		} catch (VendingMachine::Funds &e) {
			card = cardOffice.transfer(id, machine->cost() + startBalance, card());
		} catch (VendingMachine::Stock &e) {
			// try another machine
			machine = nameServer.getMachine(id);
			prt.print(Printer::Student, id, 'V', machine->getId());
		}
	}

	prt.print(Printer::Student, id, 'F');
}

