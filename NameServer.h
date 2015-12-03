#ifndef NAMESERVER_H
#define NAMESERVER_H

#include <uC++.h>
#include "Printer.h"
_Task VendingMachine;

_Task NameServer {
private:
	Printer &prt;
    unsigned int numStudents, numVendingMachines, numRegisteredMachines;
    unsigned int *assignedMachines;
    VendingMachine **vendingMachines;
    void main();
 public:
 	enum State {Start = 'S', Register= 'R', New = 'N', Finished = 'F'};
    NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents );
    ~NameServer();
    void VMregister( VendingMachine *vendingmachine );
    VendingMachine *getMachine( unsigned int id );
    VendingMachine **getMachineList();
};

#endif
