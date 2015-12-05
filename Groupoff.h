#ifndef GROUPOFF_H
#define GROUPOFF_H

#include "Printer.h"
#include "WATCard.h"
#include <queue>

_Task Groupoff {


	std::queue<WATCard::FWATCard> requests;

	Printer &prt;
	unsigned int numStudents;
	unsigned int sodaCost;
	unsigned int groupoffDelay;

	unsigned int cardsAssigned;

    void main();
  public:
    Groupoff( Printer &prt, unsigned int numStudents, unsigned int sodaCost, unsigned int groupoffDelay );
    WATCard::FWATCard giftCard();
};


#endif