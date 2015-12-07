//#define DEBUG

#include <iostream>
using namespace std;

#ifdef DEBUG 
#define D(x) x
#define LOG_LINE(x) cout << "[" << x << "]" << endl;
#define LOG(x) cout << "[" << x << "]";
#else 
#define D(x)
#endif