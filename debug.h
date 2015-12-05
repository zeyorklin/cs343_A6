#define DEBUG

#include <iostream>
using namespace std;

#ifdef DEBUG 
#define D(x) x
#else 
#define D(x)
#endif