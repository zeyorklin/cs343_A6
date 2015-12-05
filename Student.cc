#include "Student.h"
#include "VendingMachine.h"
#include "WATCard.h"
#include "MPRNG.h"
#include "Groupoff.h"
#include "WATCardOffice.h"


Student::Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, Groupoff &groupoff, unsigned int id, unsigned int maxPurchases ) 
				: prt(prt), nameServer(nameServer), cardOffice(cardOffice), groupoff(groupoff), id(id), maxPurchases(maxPurchases) {
	
}



void Student::main() {
	purchase = rng(1, maxPurchases);
	flavour = (VendingMachine::Flavours)rng((unsigned int)VendingMachine::Flavours.NUM_FLAVOUR -1);

	prt.print(Printer::Student, 'S', flavour, purchase);

	// create card
	WATCard::FWATCard card = cardOffice.create(id, 5);
	WATCard::FWATCard gift = groupoff.giftCard();

	// get machine location
	VendingMachine *machine = nameServer.getMachine(id);
	prt.print(Printer::Student, 'V', machine->getId());



	for (unsigned int purchased = 0; i < purchase; ) {
		yield(rng(1, 10));
		try {
			machine->buy(flavour, gift.balance() > 0 : gift : card);
			purchased++;
			prt.print(Printer::Student, );
		} catch (WATCardOffice::Lost &e) {

		} catch (VendingMachine::Funds &e) {

		} catch (VendingMachine::Stock &e) {

		}
	}

	prt.print(Printer::Student, 'F');
}

