#ifndef BOTTLING_PLANT_H
#define BOTTLING_PLANT_H

#include "Printer.h"
#include "NameServer.h"

_Task BottlingPlant {
    Printer &prt;
    NameServer &nameServer;
    unsigned int numVendingMachines;
    unsigned int maxShippedPerFlavour;
    unsigned int maxStockPerFlavour;
    unsigned int timeBetweenShipments;
    bool shutdown;
    void main();

    unsigned int *stock;
  public:
    _Event Shutdown {};                    // shutdown plant
    BottlingPlant( Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
                 unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
                 unsigned int timeBetweenShipments );
    void getShipment( unsigned int cargo[] );
    ~BottlingPlant();
};

#endif