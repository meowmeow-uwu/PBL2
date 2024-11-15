#include "xe.h"

#ifndef kho_h
#define kho_h

class Kho 
{
private:
    string maKho;
    unsigned int sodh;
    unsigned int soxe;
    HashTable<DonHang> donhang{sodh};
    HashTable<Truck> xe{soxe};

public:
    Kho(string maKho = "none", unsigned int sodh = 0, unsigned int soxe = 0)
        : maKho(maKho), sodh(sodh), donhang{sodh}, soxe(soxe), xe{soxe} {};
    string getMa() { return maKho; }

    bool docKho(ifstream &file)
    {

        if (!file)
        {
            cout << "Khong the doc file " << endl;
            return false;
        }
        file >> maKho;
        file >> sodh;
        donhang = HashTable<DonHang>(sodh);

        for (unsigned int i = 0; i < sodh; ++i)
        {
            string maDH;
            file >> maDH;
            DonHang newDH(maDH);
            donhang.insert(newDH);
        }

        file >> soxe;
        xe = HashTable<Truck>(soxe);
        for (unsigned int i = 0; i < soxe; ++i)
        {
            string maXe;
            file >> maXe;
            Truck newXe(maXe);
            xe.insert(newXe);
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
        cout << maKho << endl;
        for (int i = 0; i < sodh; i++)
            cout << donhang.getTableEntry(i)->data.getMa() << endl;
        for (int i = 0; i < soxe; i++)
            cout << xe.getTableEntry(i)->data.getMa() << endl;
    }


};

#endif