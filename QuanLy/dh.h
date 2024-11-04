#include <iostream>
using namespace std;

#ifndef dh_h
#define dh_h
 
class DonHang{
    private:
        string maDH;
        // double canNang;

    public:
        DonHang(string ma = ""): maDH(ma){};

        string getMaDH(){ return maDH;}
        void setMaDH(string ma){ maDH = ma;}
};


#endif