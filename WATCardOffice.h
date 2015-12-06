#ifndef WATCARDOFFICE_H
#define WATCARDOFFICE_H
#include <queue>
#include "WATCard.h"
#include "Printer.h"
#include "Bank.h"

_Monitor Printer;
_Monitor Bank;

_Task WATCardOffice {
struct Job;
public:
    _Event Lost {};                        // lost WATCard
    WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers );
    ~WATCardOffice();
    WATCard::FWATCard create( unsigned int sid, unsigned int amount );
    WATCard::FWATCard transfer( unsigned int sid, unsigned int amount, WATCard *card );
    Job *requestWork();

private:
    struct Job { 
        WATCard *card;
        unsigned int sid;      
        unsigned int amount;
        WATCard::FWATCard result;          // return future
        Job( unsigned int sid, unsigned int amount, WATCard *card )
            : sid(sid), amount(amount), card(card) {}

    };
    _Task Courier {
    public:
        Courier(Printer &printer, WATCardOffice &office, Bank &bank, unsigned int id)
            : printer(printer), office(office), bank(bank), id(id) {}
    private:
        
        Printer &printer;
        WATCardOffice &office;
        Bank &bank;
        unsigned int id; 

        void main();
    
    };   

    Printer &printer;
    Bank &bank;
    unsigned int numCouriers;
    Courier **couriers; 
    std::queue<Job*> jobs;
    uCondition courierWork;

    void main();

  
};

#endif
