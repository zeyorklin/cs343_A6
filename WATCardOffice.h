#ifndef WATCARDOFFICE_H
#define WATCARDOFFICE_H
#include <queue>
#include "WATCard.h"

_Monitor Printer;
_Monitor Bank;

_Task WATCardOffice {
    struct Job { 
        WATCard *card;     
        unsigned int amount;
        unsigned int sid;                     // marshalled arguments and return future
        WATCard::FWATCard result;          // return future
        Job( unsigned int amount, unsigned int sid, WATCard *card ) 
            : amount(amount), sid(sid), amount(amount) {}
    };
    _Task Courier {
    private:
        void main();
        Printer &printer;
        WATCardOffice &office;
        Bank &bank;
        unsigned int id;

        enum States {
            Start = 'S', StartFundsTransfer = 't', CompleteFundsTransfer = 'T', Finish = 'F'
        };
    public:
        Courier(Printer &printer, WATCardOffice &office, Bank &bank, unsigned int id)
            : printer(printer), office(office), bank(bank), id(id) {}
    };   

    enum States { 
        Start = 'S', RequestWork = 'W', Create   = 'C', Transfer = 'T', Finish   = 'F'
    };              

    std::vector<Courier*> couriers;
    std::queue<Job*> jobs;
    Printer &printer;
    Bank &bank;
    unsigned int numCouriers;
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
