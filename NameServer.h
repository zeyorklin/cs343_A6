#ifndef NAMESERVER_H
#define NAMESERVER_H


#include "Printer.h"
_Monitor Printer;
_Task VendingMachine;

_Task NameServer {
private:
	Printer &prt;
    unsigned int numStudents, numVendingMachines, numRegisteredMachines;
    unsigned int *assignedMachines;
    VendingMachine **vendingMachines;
    void main();
 public:
    NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents );
    ~NameServer();
    void VMregister( VendingMachine *vendingmachine );
    VendingMachine *getMachine( unsigned int id );
    VendingMachine **getMachineList();
};

#endif
