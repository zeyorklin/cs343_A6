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
    WATCard::FWATCard create( unsigned int sid, unsigned int amount );
    WATCard::FWATCard transfer( unsigned int sid, unsigned int amount, WATCard *card );
    Job *requestWork();

private:
    struct Job { 
        WATCard *card;
        unsigned int sid;      
        unsigned int amount;
        WATCard::FWATCard result;          // return future
        Job( unsigned int sid, unsigned int amount, WATCard *card );
    };
    _Task Courier {
    public:
        Courier(Printer &printer, WATCardOffice &office, Bank &bank, unsigned int id);
    private:
        
        Printer &printer;
        WATCardOffice &office;
        Bank &bank;
        unsigned int id; //not sure if needed

        enum States {
            Start = 'S', StartFundsTransfer = 't', CompleteFundsTransfer = 'T', Finish = 'F'
        };

        void main();
    
    };   

    enum States { 
        Start = 'S', Work = 'W', Create   = 'C', Transfer = 'T', Finish   = 'F'
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
