#include <iostream>
#include "kho.h"
#include "xe.h"
#include "dh.h"
#include "nv.h"
#include "hash.h"
using namespace std;

#ifndef congty_h
#define congty_h

class CongTy : public Kho, NhanVien, Truck
{
    string name;
    unsigned int sokho;
    unsigned int soxe;
    unsigned int sonv;
    HashTable<NhanVien, sonv> nv;
    HashTable<Kho, sokho> kho;
    HashTable<Truck, soxe> xe;

public:
    CongTy(unsigned int sokho = 3, unsigned int soxe = 3, unsigned int sonv = 3): sokho(sokho), soxe(soxe), sonv(sonv)
    {
    }

    bool search();
    bool nhap();
    bool xuat();
};

bool search()
{
    string ma;
    cout << "Nhap ma don hang: ";
    cin >> ma;

    for (int i = 0; i < number; i++)
    {
        DonHang *DH = kho[i]->searchDH(ma);
        if (DH)
        {
            cout << "found";
            return;
        }
    }
    cout << "Khong tim thay thong tin don hang" << endl;
}

#endif