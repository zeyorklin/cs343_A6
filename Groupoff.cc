#include "Groupoff.h"

#include <iostream>
using namespace std;

Groupoff::Groupoff( Printer &prt, unsigned int numStudents, unsigned int sodaCost, unsigned int groupoffDelay )
					:prt(prt), numStudents(numStudents), sodaCost(sodaCost), groupoffDelay(groupoffDelay), cardsAssigned(0), requests() {

}

WATCard::FWATCard Groupoff::giftCard() {
	Work *w = new Work();
	requests.push(w);
	return w->result;
}


void Groupoff::main() {
	prt.print(Printer::Groupoff, 'S');

	
	for ( ;; ) {

		_Accept(~Groupoff) {
			break;
		} _Else {}

		if (cardsAssigned > numStudents) break;

		
		if (!requests.empty()) {
			
			WATCard *card = new WATCard();
			card->deposit(sodaCost);
			prt.print(Printer::Groupoff, 'D', sodaCost);

			yield(groupoffDelay);

			Work *w = requests.front();
			requests.pop();
			w->result.delivery(card);
			cardsAssigned++;
			
		}
	}
	

	prt.print(Printer::Groupoff, 'F');
}


