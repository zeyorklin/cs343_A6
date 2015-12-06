#ifndef STUDENT_H
#define STUDENT_H

#include "Printer.h"
#include "NameServer.h"
#include "WATCardOffice.h"
#include "Groupoff.h"
#include "MPRNG.h"
#include "VendingMachine.h"



_Task Student {
	Printer &prt;
	NameServer &nameServer;
	WATCardOffice &cardOffice;
	Groupoff &groupoff;
	unsigned int id;
	unsigned int maxPurchases;

	unsigned int purchase;
	VendingMachine::Flavours flavour;

    void main();
  public:
    Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, Groupoff &groupoff,
             unsigned int id, unsigned int maxPurchases );
};

#endif