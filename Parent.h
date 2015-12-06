#ifndef PARENT_H
#define PARENT_H

#include <uC++.h>
#include "Printer.h"
#include "Bank.h"

_Task Parent {
private:
    void main();
    Printer &prt;
    Bank &bank;
    unsigned int numStudents, parentalDelay;
    enum State {Start = 'S', Deposit = 'D', Finished = 'F'};
public:
    
    Parent( Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay );
};

#endif
