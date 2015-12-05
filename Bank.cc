#include "Bank.h"

Bank::Bank(unsigned int numStudents) :
    numStudents(numStudents){
    	balances = new unsigned int [numStudents];
    	balancesCond = new uCondition [numStudents];
    	for(unsigned int i =0; i<numStudents; i+=1)
    	{
    		balances[i] = 0;
    	}
    }

Bank::~Bank() {
    delete[] balances;
    delete[] balancesCond;
}

void Bank::deposit(unsigned int id, unsigned int amount) {
    balances[id] += amount;      
    balancesCond[id].signal();    
}

void Bank::withdraw(unsigned int id, unsigned int amount) {
    while (balances[id] < amount) balancesCond[id].wait();

    balances[id] -= amount;    
}
