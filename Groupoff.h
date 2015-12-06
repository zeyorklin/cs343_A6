#ifndef GROUPOFF_H
#define GROUPOFF_H

#include "Printer.h"
#include "WATCard.h"
#include <queue>

_Task Groupoff {

	struct Work {
		WATCard::FWATCard result;
	};

	
	Printer &prt;
	unsigned int numStudents;
	unsigned int sodaCost;
	unsigned int groupoffDelay;
	unsigned int cardsAssigned;
	std::queue<Work *> requests;

    void main();
  public:
    Groupoff( Printer &prt, unsigned int numStudents, unsigned int sodaCost, unsigned int groupoffDelay );
    WATCard::FWATCard giftCard();
};


#endif