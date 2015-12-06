#include "WATCardOffice.h"
#include "MPRNG.h"
#include "WATCard.h"
#include "Bank.h"
#include "Printer.h"
#include <iostream>

using namespace std;

void WATCardOffice::Courier::main() {
	printer.print(Printer::Courier, id, 'S');
	while(true)
	{
		Job *job = office.requestWork();
		if(job == NULL) break;
		if(job->card == NULL) job->card = new WATCard();
		printer.print(Printer::Courier, id, 't', job->sid, job->amount);
		bank.withdraw(job->sid, job->amount);
		job->card->deposit(job->amount);
		printer.print(Printer::Courier, id, 'T', job->sid, job->amount);

		if ((rng() % 6) == 0) {
			delete job->card;
			job->result.exception(new Lost());
		}
		else{
			job->result.delivery(job->card);
		}
		delete job;
	}

	printer.print(Printer::Courier, id, 'F');

	_Accept(~Courier);  //not sure about this
}

WATCardOffice::WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers )
	: printer(prt), bank(bank), numCouriers(numCouriers), couriers(new Courier*[numCouriers])
	{
		for(unsigned int i = 0; i < numCouriers; i += 1)
		{
			couriers[i] = new Courier(printer, *this, bank, i);
		}
	}

WATCardOffice::~WATCardOffice()
{
	for(unsigned int i; i < numCouriers; i+=1)
	{
		delete couriers[i];
	}
	delete []couriers;
	printer.print(Printer::WATCardOffice, 'F');
}

WATCard::FWATCard WATCardOffice::create(unsigned int sid, unsigned int amount) {
    Job *job = new Job(sid, amount, NULL);
    jobs.push(job);

    printer.print(Printer::WATCardOffice, 'C', sid, amount);
    courierWork.signal();
    return job->result;
}

WATCard::FWATCard WATCardOffice::transfer(unsigned int sid, unsigned int amount, WATCard *card) {
    Job *job = new WATCardOffice::Job(sid, amount, card);

    jobs.push(job);
    printer.print(Printer::WATCardOffice, 'T', sid, amount);
    courierWork.signal();

    return job->result;
}

WATCardOffice::Job *WATCardOffice::requestWork() {
    if(jobs.empty())
    {
    	courierWork.wait();
    	if(jobs.empty())
    	{
    		return NULL;
    	}
    }

    Job *job = jobs.front();
    jobs.pop();
    printer.print(Printer::WATCardOffice, 'W');
    return job;
}

void WATCardOffice::main()
{
	printer.print(Printer::WATCardOffice, 'S');
	while(true)
	{
		_Accept(~WATCardOffice) {
			 while (!courierWork.empty()) {
                courierWork.signalBlock();
            }
            break;
		} or _Accept(create, transfer, requestWork);
	} 
}



















