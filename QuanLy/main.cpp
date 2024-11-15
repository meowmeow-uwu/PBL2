#include "congty.h"

int main()
{
    CongTy A;
    A.docCongTy();
    HashTable<Kho> &dsKho = A.getKho();
    HashTable<Truck> &dsXe = A.getXe();
    HashTable<DonHang> &dsDH = A.getDH();
    HashTable<NhanVien> &dsNV = A.getNV();
    HashTable<VanChuyen> &dsTuyen = A.getTuyen();
    string tenFile = "kho.txt";
    ifstream file(tenFile);
    if (!file)
    {
        cout << "Can't open file! "<< endl;
        return false;
    }
    
    for (int i = 0; i < dsKho.getSize(); i++)
    {
        Node<Kho> *entry = dsKho.getTableEntry(i);
        while (entry)
        {
            entry->data.docKho(file);
            entry = entry->next;
        }
    }

file.close();
tenFile = "xe.txt";
file.open(tenFile);

    if (!file)
    {
        cout << "Can't open file! "<< endl;
        return false;
    }
   
       for (int i = 0; i < dsXe.getSize(); i++)
    {
        Node<Truck> *entry = dsXe.getTableEntry(i);
        while (entry)
        {
            entry->data.docXe(file);
            entry = entry->next;
        }
    }

file.close();
tenFile = "dh.txt";
file.open(tenFile);

    if (!file)
    {
        cout << "Can't open file! "<< endl;
        return false;
    }
   
       for (int i = 0; i < dsXe.getSize(); i++)
    {
        Node<DonHang> *entry = dsDH.getTableEntry(i);
        while (entry)
        {
            entry->data.docDH(file);
            entry = entry->next;
        }
    }

file.close();

tenFile = "nhanvien.txt";
file.open(tenFile);

    if (!file)
    {
        cout << "Can't open file! "<< endl;
        return false;
    }
   
       for (int i = 0; i < dsNV.getSize(); i++)
    {
        Node<NhanVien> *entry = dsNV.getTableEntry(i);
        while (entry)
        {
            entry->data.docNV(file);
            entry = entry->next;
        }
    }

file.close();

tenFile = "vanchuyen.txt";
file.open(tenFile);

    if (!file)
    {
        cout << "Can't open file! "<< endl;
        return false;
    }
       for (int i = 0; i < dsXe.getSize(); i++)
    {
        Node<VanChuyen> *entry = dsTuyen.getTableEntry(i);
        while (entry)
        {
            entry->data.docVC(file);
            entry = entry->next;
        }
    }

file.close();


       for (int i = 0; i < dsXe.getSize(); i++)
    {
        Node<Truck> *entry = dsXe.getTableEntry(i);
        while (entry)
        {
            entry->data.show();
            cout<<endl;
            entry = entry->next;
        }
    }









    

    return 0;
}
