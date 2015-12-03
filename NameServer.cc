#include "NameServer.h"
#include "VendingMachine.h"


NameServer::NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents )
	: prt(prt), numVendingMachines(numVendingMachines), numStudents(numStudents), numRegisteredMachines(0)
	{
		assignedMachines = new int [numStudents];
		vendingMachines = new VendingMachine*[numStudents];
	}

NameServer::~NameServer()
{
	delete [] assignedMachines;
	delete [] vendingMachines;
}

void NameServer::main()
{
	prt.printer(Printer::NameServer, 'S');
}

VendingMachine **NameServer::getMachineList()
{
	return vendingMachines;
	while(true)
	{
		_Accept(~NameServer) break;
		or _When(numVendingMachines = numRegisteredMachines) _Accept(getMachine, getMachineList);
		or _When(numVendingMachines > numRegisteredMachines) _Accept(VMregister);
	}
	prt.printer(Printer::NameServer, 'F');
}

VendingMachine *NameServer::getMachine( unsigned int id )
{
	VendingMachine *machine = vendingMachines[assignedMachines[id]];
	prt.printer(Printer::NameServer, 'N', id, machine->getId());
	assignedMachines[id] = (assignedMachines[id] + 1) % numVendingMachines;
}

void NameServer::VMregister( VendingMachine *vendingmachine )
{
	prt.printer(Printer::NameServer, 'R', vendingmachine->getId());
	vendingMachines[numRegisteredMachines] = vendingmachine;
	numRegisteredMachines += 1;
}









