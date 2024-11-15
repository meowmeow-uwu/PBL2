#include <iostream>
#include <fstream>
using namespace std;

#ifndef dh_h
#define dh_h

class DonHang
{
private:
    string maDH;
    double canNang;

public:
    DonHang(string ma = "", double size = 0.0) : maDH(ma), canNang(size) {};
    string getMa() { return maDH; }
    void setMa(string ma) { maDH = ma; }

    bool docDH(ifstream &file)
    {

        if (!file)
        {
            cout << "Khong the doc file " << endl;
            return false;
        }
        file >> maDH >> canNang;
        return true;
    }

    void show()
    {
        // ifstream file;
        // if (!docKho(file))
        // {
        //     cout << "loi";
        //     return;
        // }
        cout << maDH << "  " << canNang << endl;
    }
};

#endif