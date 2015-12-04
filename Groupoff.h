#ifndef GROUPOFF_H
#define GROUPOFF_H

#include "Printer.h"

_Task Groupoff {
	Printer &prt;
	unsigned int numStudents;
	unsigned int sodaCost;
	unsigned int groupoffDelay;

	unsigned int cardsAssigned;
	uCondition lock;
	WATCard::FWTCard *card;
    void main();
  public:
    Groupoff( Printer &prt, unsigned int numStudents, unsigned int sodaCost, unsigned int groupoffDelay );
    WATCard::FWATCard giftCard();
};


#endif