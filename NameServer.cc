#include "NameServer.h"
#include "VendingMachine.h"
#include "Printer.h"


NameServer::NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents )
	: prt(prt), numStudents(numStudents), numVendingMachines(numVendingMachines), numRegisteredMachines(0)
	{
		assignedMachines = new unsigned int [numStudents];
		for (unsigned int i = 0; i < numStudents; i++) {
			assignedMachines[i] = i % numVendingMachines;
		}

		vendingMachines = new VendingMachine*[numStudents];
	}

NameServer::~NameServer()
{
	delete [] assignedMachines;
	delete [] vendingMachines;
}

void NameServer::main()
{
	prt.print(Printer::NameServer, 'S');

	/*while(true)
	{
		_Accept(~NameServer) break;
		or _When(numVendingMachines == numRegisteredMachines) _Accept(getMachine, getMachineList);
		or _When(numVendingMachines > numRegisteredMachines) _Accept(VMregister);
	}*/

	outer: while (true) {
        // block tasks from using vending machines until `numVendingMachines` machines have been registered
        while (numRegisteredMachines < numVendingMachines) {
            _Accept(~NameServer) {
                // allow the destructor to terminate the loop
                break outer;
            } or _Accept(VMregister) {
                // each time we register a vending machine, increment `numRegistered`
                numRegisteredMachines++;
            }
        }

        // now that machines have been registered, assign each student to a vending machine
        for (unsigned int i = 0; i < numStudents; i++) {
            unsigned int machineNum = i % numVendingMachines;
            assignedMachines[i] = machineNum;
        }

        while (true) {
            _Accept(~NameServer) {
                // allow the destructor to terminate the loop
                break outer;
            } or _Accept(getMachine, getMachineList);    // otherwise, finally allow normal calls to our public methods
        }
    }

	prt.print(Printer::NameServer, 'F');
}

VendingMachine **NameServer::getMachineList()
{
	return vendingMachines;

}

VendingMachine *NameServer::getMachine( unsigned int id )
{
	VendingMachine *machine = vendingMachines[assignedMachines[id]];
	prt.print(Printer::NameServer, 'N', id, machine->getId());
	//assignedMachines[id] = (assignedMachines[id] + 1) % numVendingMachines;
	assignedMachines[id] = (assignedMachines[id] < numVendingMachines - 1) ? assignedMachines[id] + 1 : 0;

	return machine;
}

void NameServer::VMregister( VendingMachine *vendingmachine )
{
	prt.print(Printer::NameServer, 'R', vendingmachine->getId());
	vendingMachines[numRegisteredMachines] = vendingmachine;
	//numRegisteredMachines += 1;
}









