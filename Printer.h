#ifndef PRINTER_H
#define PRINTER_H

_Monitor Printer {

    struct Data {
        char state;
        int value1;
        int value2;
        int numValue;
    };

	unsigned int numStudents;
	unsigned int numVendingMachines;
	unsigned int numCouriers;

    unsigned int bufferSize;

    Data** buffer;

  public:
    enum Kind { Parent, Groupoff, WATCardOffice, NameServer, Truck, BottlingPlant, Student, Vending, Courier };
    Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers );
    void print( Kind kind, char state );
    void print( Kind kind, char state, int value1 );
    void print( Kind kind, char state, int value1, int value2 );
    void print( Kind kind, unsigned int lid, char state );
    void print( Kind kind, unsigned int lid, char state, int value1 );
    void print( Kind kind, unsigned int lid, char state, int value1, int value2 );
    ~Printer();

  private:
    void flush();
    unsigned int bufferId(Kind kind);
    void finished();
    void _print(unsigned int id, char state, int numVal, int value1, int value2);

};

#endif