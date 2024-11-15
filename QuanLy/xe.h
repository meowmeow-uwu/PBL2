#include "dh.h"
#include "hash.h"
#include <fstream>
#ifndef xe_h
#define xe_h

class Truck
{

    string BKS;
    double taitrong;
    unsigned int sodh;
    HashTable<DonHang> donhang;

public:
    Truck(string bienso = "none", unsigned int n = 0, double tai = 0.0)
        : BKS(bienso), sodh(n), donhang(sodh), taitrong(tai) {};

    string getMa() { return BKS; };

    bool docXe(ifstream &file)
    {

        if (!file)
        {
            cout << "Khong the doc file " << endl;
            return false;
        }
        file >> BKS >> taitrong;
        file >> sodh;
        donhang = HashTable<DonHang>(sodh);

        for (unsigned int i = 0; i < sodh; ++i)
        {
            string maDH;
            file >> maDH;
            DonHang newDH(maDH);
            donhang.insert(newDH);
        }

        file.ignore();
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
        cout << BKS << "  " << taitrong << endl;
        for (int i = 0; i < sodh; i++)
            cout << donhang.getTableEntry(i)->data.getMa() << endl;
    }
};

#endif