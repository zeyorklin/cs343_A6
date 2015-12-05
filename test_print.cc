#include "debug.h"
#include "Printer.h"




void uMain::main() {

	Printer printer(2, 2, 1);

	printer.print(Printer::Kind::Parent, 'S');
	printer.print(Printer::Kind::Groupoff, 'S');
	printer.print(Printer::Kind::WATCardOffice, 'S');
	printer.print(Printer::Kind::NameServer, 'S');
	printer.print(Printer::Kind::BottlingPlant, 'S');

	printer.print(Printer::Kind::Parent, 'S', 2);
	printer.print(Printer::Kind::Parent, 'S', 3, 3);
	printer.print(Printer::Kind::Student, 1, 'S');
	printer.print(Printer::Kind::Student, 2, 'S', 5);
	printer.print(Printer::Kind::Student, 3, 'S', 6, 6);
	printer.print(Printer::Kind::Student, 1, 'S', 7, 7);
	printer.print(Printer::Kind::Student, 1, 'F');
	printer.print(Printer::Kind::Student, 2, 'V', 8);
	printer.print(Printer::Kind::Student, 3, 'V', 9);
	printer.print(Printer::Kind::Student, 3, 'V', 9);


} 
