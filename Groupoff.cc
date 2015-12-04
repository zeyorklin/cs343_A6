#include "Groupoff.h"

Groupoff::Groupoff( Printer &prt, unsigned int numStudents, unsigned int sodaCost, unsigned int groupoffDelay )
					:prt(prt), numStudents(numStudents), sodaCost(sodaCost), groupoffDelay(groupoffDelay), cardsAssigned(0) {

}

WATCard::FWATCard Groupoff:giftCard() {
	lock.wait();
	return card;
}


void Groupoff::main() {
	prt.print(Printer::Groupoff, 'S');

	for ( ;; ) {
		_Accept(~Groupoff) {
			break;
		} _Accept(giftCard) {
			if (cardsAssigned > numStudents) break;
			yield(groupoffDelay);
			card = new WATCard::FWTCard();
			card.deposit(sodaCost);
			cardsAssigned++;
			lock.signalBlock();
		}_Else {
		}
	}

	prt.print(Printer::Groupoff, 'F');
}


