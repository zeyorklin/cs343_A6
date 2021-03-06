#include "Student.h"
#include "VendingMachine.h"
#include "WATCard.h"
#include "MPRNG.h"
#include "WATCardOffice.h"
#include "debug.h"


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

	
	WATCard::FWATCard gift = groupoff.giftCard();

	// get machine location
	VendingMachine *machine = nameServer.getMachine(id);
	prt.print(Printer::Student, id, 'V', machine->getId());	
	
	unsigned int purchased = 0;
	bool lostCard = false;


	for ( ;; ) {
		try {
			if (lostCard == true) {
				card = cardOffice.create(id, startBalance);
				lostCard = false;
			}
			for (; purchased < purchase; ) {
				try {
					_Enable { 

						_Select(card || gift) {
							if (card.available()) {
								machine->buy(flavour, *(card()));
								prt.print(Printer::Student, id, 'B', card()->getBalance());
								yield(rng(1, 10));
								purchased++;
							} else if (gift.available()) {
								machine->buy(flavour, *(gift()));
								prt.print(Printer::Student, id, 'G', gift()->getBalance());
								gift.reset();
								yield(rng(1, 10));
					 			purchased++;
							}
						} _Else { }
					}
				} catch (VendingMachine::Funds &e) {
					card = cardOffice.transfer(id, machine->cost() + startBalance, card());
				} catch (VendingMachine::Stock &e) {
					// try another machine
					machine = nameServer.getMachine(id);
					prt.print(Printer::Student, id, 'V', machine->getId());
				}
			}
			break;
		} catch (WATCardOffice::Lost &e) {
			prt.print(Printer::Student, id, 'L');
			lostCard = true;
			card.reset();
		}
	} 

	//delete card();

	prt.print(Printer::Student, id, 'F');
}

