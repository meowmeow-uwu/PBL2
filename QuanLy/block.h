#include <iostream>
#include "kho.h"
using namespace std;

#ifndef block_h
#define block_h

class Block: public DonHang{
    string maBlock;
    DonHang* DH;
    unsigned int number;
    

};

#endif