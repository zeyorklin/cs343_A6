#ifndef GROUPOFF_H
#define GROUPOFF_H

#include "Printer.h"
#include "NameServer.h"

_Task VendingMachine {

    enum STATE {FUND, STOCK, BUY};

    Printer &prt;
    NameServer &nameServer;
    unsigned int id;
    unsigned int sodaCost;
    unsigned int maxStockPerFlavour;

    unsigned int* stock;
    State state;
    Flavours buyFlavour;
    WATCard &buyCard;
    uBaseTask *studentTask;
    bool stocking;
    uCondition done;

    void main();
  public:
    enum Flavours { BLACK_CHEERY = 0, CREAM_SODA, ROOT_BEER, LIME, NUM_FLAVOUR};                 // flavours of soda (YOU DEFINE)
    _Event Funds {};                       // insufficient funds
    _Event Stock {};                       // out of stock for particular flavour
    VendingMachine( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost,
                    unsigned int maxStockPerFlavour );
    void buy( Flavours flavour, WATCard &card );
    unsigned int *inventory();
    void restocked();
    _Nomutex unsigned int cost();
    _Nomutex unsigned int getId();
    ~VendingMachine();
};

#endif