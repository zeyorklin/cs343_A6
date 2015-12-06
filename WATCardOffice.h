#ifndef WATCARDOFFICE_H
#define WATCARDOFFICE_H
#include <queue>
#include "WATCard.h"
#include "Printer.h"
#include "Bank.h"

_Task WATCardOffice {
    struct Job { 
        WATCard *card;
        unsigned int sid;      
        unsigned int amount;
        WATCard::FWATCard result;          // return future
        Job( unsigned int sid, unsigned int amount, WATCard *card ) 
            : card(card),  sid(sid), amount(amount) {}
    };
    _Task Courier {
    private:
        void main();
        Printer &printer;
        WATCardOffice &office;
        Bank &bank;
        unsigned int id; //not sure if needed

        enum States {
            Start = 'S', StartFundsTransfer = 't', CompleteFundsTransfer = 'T', Finish = 'F'
        };
    public:
        Courier(Printer &printer, WATCardOffice &office, Bank &bank, unsigned int id)
            : printer(printer), office(office), bank(bank), id(id) {}
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

  public:
    _Event Lost {};                        // lost WATCard
    WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers );
    virtual ~WATCardOffice();
    WATCard::FWATCard create( unsigned int sid, unsigned int amount );
    WATCard::FWATCard transfer( unsigned int sid, unsigned int amount, WATCard *card );
    Job *requestWork();
};

#endif
