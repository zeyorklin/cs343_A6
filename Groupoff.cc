#include "Groupoff.h"
#include "debug.h"

#include <iostream>
using namespace std;

Groupoff::Groupoff( Printer &prt, unsigned int numStudents, unsigned int sodaCost, unsigned int groupoffDelay )
					:prt(prt), numStudents(numStudents), sodaCost(sodaCost), groupoffDelay(groupoffDelay), requests() {

}

WATCard::FWATCard Groupoff::giftCard() {
	WorkCard *w = new WorkCard();
	requests.push(w);
	return w->result;
}

Groupoff::~Groupoff() {

}

void Groupoff::main() {
	prt.print(Printer::Groupoff, 'S');
	for (unsigned int gifted = 0; gifted < numStudents; ) {
		 _Accept(~Groupoff) {
			break;
		} or _Accept(giftCard) {
			yield(groupoffDelay);
			WATCard *card = new WATCard();
			card->deposit(sodaCost);
			prt.print(Printer::Groupoff, 'D', sodaCost);

			WorkCard *w = requests.front();
			requests.pop();
			w->result.delivery(card);
			gifted++;
		}_Else 
		{
		}
	}
	prt.print(Printer::Groupoff, 'F');
}


