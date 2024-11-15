#include "vanchuyen.h"
#include "nv.h"

#ifndef congty_h
#define congty_h

class CongTy
{
    string name;
    unsigned int sokho;
    unsigned int soxe;
    unsigned int sodh;
    unsigned int sonv;
    HashTable<NhanVien> nv;
    HashTable<Kho> kho;
    HashTable<Truck> xe;
    HashTable<DonHang> donhang;
    HashTable<VanChuyen> vanchuyen;

public:
    CongTy(unsigned int sokho = 3, unsigned int soxe = 3, unsigned int sonv = 3, unsigned int sodh = 3)
        : sokho(sokho), soxe(soxe), sonv(sonv), sodh(sodh), nv(sonv), kho(sokho), xe(soxe), donhang(sodh), vanchuyen(soxe)
    {
    }

    // Getter cho các thuộc tính của CongTy
string getName() const
{
    return name;
}

unsigned int getSoKho() const
{
    return sokho;
}

unsigned int getSoXe() const
{
    return soxe;
}

unsigned int getSoDH() const
{
    return sodh;
}

unsigned int getSoNV() const
{
    return sonv;
}


    HashTable<Kho> &getKho()
    {
        return kho;
    }
    HashTable<NhanVien> &getNV()
    {
        return nv;
    }
    HashTable<DonHang> &getDH()
    {
        return donhang;
    }
    HashTable<Truck> &getXe()
    {
        return xe;
    }
    HashTable<VanChuyen> &getTuyen()
    {
        return vanchuyen;
    }

    bool search();
    bool nhap();
    bool xuat();

    bool docCongTy(const string &tenFile = "congty.txt")
    {
        ifstream file(tenFile);
        if (!file)
        {
            cout << "Không thể mở file " << tenFile << endl;
            return false;
        }
        file >> name;
        file >> sokho;
        kho = HashTable<Kho>(sokho);

        for (unsigned int i = 0; i < sokho; ++i)
        {
            string maKho;
            file >> maKho;
            Kho newKho(maKho);
            kho.insert(newKho);
        }

        file >> soxe;
        xe = HashTable<Truck>(soxe);
        vanchuyen = HashTable<VanChuyen>(soxe);
        for (unsigned int i = 0; i < soxe; ++i)
        {
            string maXe;
            file >> maXe;
            Truck newXe(maXe);
            xe.insert(newXe);
            VanChuyen newTuyen(maXe);
            vanchuyen.insert(newTuyen);
        }

        file >> sodh;
        donhang = HashTable<DonHang>(sodh);
        for (unsigned int i = 0; i < sodh; ++i)
        {
            string maDH;
            file >> maDH;
            DonHang newDH(maDH);
            donhang.insert(newDH);
        }
        file >> sonv;
        nv = HashTable<NhanVien>(sonv);
        for (unsigned int i = 0; i < sonv; ++i)
        {
            string maNV;
            file >> maNV;
            NhanVien newNV(maNV);
            nv.insert(newNV);
        }

        file.close();
        return true;
    }

    bool ghiCongTy(const string &tenFile = "congty.txt")
    {
        ofstream file(tenFile);
        if (!file)
        {
            cout << "Không thể mở file " << tenFile << endl;
            return false;
        }
        file << name;
        file << sokho;
        kho = HashTable<Kho>(sokho);

        for (unsigned int i = 0; i < sokho; ++i)
        {
            string maKho;
            file << maKho;
            Kho newKho(maKho);
            kho.insert(newKho);
        }

        file << soxe;
        xe = HashTable<Truck>(soxe);
        vanchuyen = HashTable<VanChuyen>(soxe);
        for (unsigned int i = 0; i < soxe; ++i)
        {
            string maXe;
            file << maXe;
            Truck newXe(maXe);
            xe.insert(newXe);
            VanChuyen newTuyen(maXe);
            vanchuyen.insert(newTuyen);
        }

        file << sodh;
        donhang = HashTable<DonHang>(sodh);
        for (unsigned int i = 0; i < sodh; ++i)
        {
            string maDH;
            file << maDH;
            DonHang newDH(maDH);
            donhang.insert(newDH);
        }
        file << sonv;
        nv = HashTable<NhanVien>(sonv);
        for (unsigned int i = 0; i < sonv; ++i)
        {
            string maNV;
            file << maNV;
            NhanVien newNV(maNV);
            nv.insert(newNV);
        }

        file.close();
        return true;
    }


    void show()
    {
        if (!docCongTy())
        {
            cout << "loi";
            return;
        }
        cout << name << endl;
        for (int i = 0; i < sokho; i++)
            cout << kho.getTableEntry(i)->data.getMa() << endl;
        for (int i = 0; i < soxe; i++)
            cout << xe.getTableEntry(i)->data.getMa() << endl;
        for (int i = 0; i < sonv; i++)
            cout << nv.getTableEntry(i)->data.getMa() << endl;
        for (int i = 0; i < sodh; i++)
            cout << donhang.getTableEntry(i)->data.getMa() << endl;
    }
};

#endif