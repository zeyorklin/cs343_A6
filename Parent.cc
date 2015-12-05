#include <uC++.h>
#include "Parent.h"
#include "MPRNG.h"

Parent::Parent( Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay ) 
	: prt(prt), bank(bank), numStudents(numStudents), parentalDelay(parentalDelay)
	{
		prt.print(Printer::Parent, 'S');
	}

void Parent::main() {
  while (true) {
    _Accept(~Parent) {
      break;
    } 
    _Else 
    {
      yield(parentalDelay);
      int studentId = rng(numStudents - 1);
      int amount = rng(1, 3);
      prt.print(Printer::Parent, 'D', studentId, amount);
      bank.deposit(studentId, amount);
    }
  }

  prt.print(Printer::Parent, 'S');
}