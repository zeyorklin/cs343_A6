#include "Groupoff.h"

Groupoff::Groupoff( Printer &prt, unsigned int numStudents, unsigned int sodaCost, unsigned int groupoffDelay )
					:prt(prt), numStudents(numStudents), sodaCost(sodaCost), groupoffDelay(groupoffDelay), cardsAssigned(0) {

}

WATCard::FWATCard Groupoff::giftCard() {
	WATCard::FWATCard fcard;
	requests.push(fcard);
	return fcard;
}


void Groupoff::main() {
	prt.print(Printer::Groupoff, 'S');

	for ( ;; ) {
		_Accept(~Groupoff) {
			break;
		} _Accept(giftCard) {
			if (cardsAssigned > numStudents) break;
			WATCard *card = new WATCard();
			card->deposit(sodaCost);
			yield(groupoffDelay);
			
			WATCard::FWATCard fcard = requests.front();
			requests.pop();
			fcard.delivery(card);
			
		}_Else {
		}
	}

	prt.print(Printer::Groupoff, 'F');
}


