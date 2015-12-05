#ifndef VENDING_MACHINE_H
#define VENDING_MACHINE_H

#include "Printer.h"
#include "NameServer.h"
#include "WATCard.h"

_Task VendingMachine {

    enum MACHINE_STATE {FUND, STOCK, BUY};

    Printer &prt;
    NameServer &nameServer;
    unsigned int id;
    unsigned int sodaCost;
    unsigned int maxStockPerFlavour;

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

  private:
    unsigned int* stock;
    MACHINE_STATE state;
    Flavours buyFlavour;
    WATCard *buyCard;
    uBaseTask *studentTask;
    bool stocking;
    uCondition done;
};

#endif