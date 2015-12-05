#include "Printer.h"

#include <iostream>
using namespace std;
	
Printer::Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers )
					: numStudents(numStudents), numVendingMachines(numVendingMachines), numCouriers(numCouriers),
					bufferSize(6 + numStudents + numVendingMachines + numCouriers) {

	buffer = new Data*[bufferSize];
	for (unsigned int i = 0; i < bufferSize; i++) buffer[i] = NULL;
	
	cout << "Parent\t" << "Gropoff\t" << "WATOff\t" << "Names\t" << "Truck\t" << "Plant\t";
	for (unsigned int i = 0; i < numStudents; i++) cout << "Stud" << i << "\t";
	for (unsigned int i = 0; i < numVendingMachines; i++) cout << "Mach" << i << "\t";
	for (unsigned int i = 0; i < numCouriers; i++) cout << "Cour" << i << "\t";
	cout << endl;
	
	for (unsigned int i = 0; i < bufferSize; i++) cout << "*******" << '\t';
	cout << endl;
}

void Printer::finished() {
	for (unsigned int i = 0; i < bufferSize; i++) {
		if (buffer[i] == NULL || buffer[i]->state != 'F') {
			cout << "...";
		} else {
			cout << "F";
			delete buffer[i];
			buffer[i] = NULL;
		}
		cout << "\t";
	}
	cout << endl;
}

void Printer::_print(unsigned int id, char state, int numVal, int value1, int value2) {
	if (buffer[id] != NULL) flush();
	Data *data = new Data();
	data->state = state;
	data->numValue = numVal;

	if (numVal == 2) {
		data->value1 = value1;
		data->value2 = value2;
	} else if (numVal == 1) {
		data->value1 = value1;
	}

	buffer[id] = data;

	if (state == 'F') finished();

}

unsigned int Printer::bufferId(Kind kind) {
	unsigned int id = (unsigned int)kind;
	if (kind == Student) {
		id = 6;
	} else if (kind == Vending) {
		id = 6 + numStudents;
	} else if (kind == Courier) {
		id = 6 + numStudents + numVendingMachines;
	} 

	return id;
}

void Printer::print( Kind kind, char state ) {
	_print(bufferId(kind), state, 0, -1, -1);
}

void Printer::print( Kind kind, char state, int value1 ) {
	_print(bufferId(kind), state, 1, value1, -1);
}

void Printer::print( Kind kind, char state, int value1, int value2 ) {
	_print(bufferId(kind), state, 2, value1, value2);
}

void Printer::print( Kind kind, unsigned int lid, char state ) {
	_print(bufferId(kind)+lid, state, 0, -1, -1);
}

void Printer::print( Kind kind, unsigned int lid, char state, int value1 ) {
	_print(bufferId(kind)+lid, state, 1, value1, -1);
}

void Printer::print( Kind kind, unsigned int lid, char state, int value1, int value2 ) {
	_print(bufferId(kind)+lid, state, 2, value1, value2);
}

void Printer::flush() {
	for (unsigned int i = 0; i < bufferSize; i++) {
		if (buffer[i] == NULL) {
			cout << "\t";
			continue;
		}
		cout << buffer[i]->state;
		if (buffer[i]->numValue == 2) {
			cout << buffer[i]->value1 << "," << buffer[i]->value2;
		} else if (buffer[i]->numValue == 1) {
			cout << buffer[i]->value1;
		}
		delete buffer[i];
		buffer[i] = NULL;
		cout << "\t";
	}
	cout << endl;
}


Printer::~Printer() {
	cout << "***********************" << endl;
	for (unsigned int i = 0; i < bufferSize; i++)
		delete buffer[i];
	delete [] buffer;
}