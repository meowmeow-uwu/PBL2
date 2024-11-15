#include "kho.h"
#include "hash.h"

#ifndef vanchuyen_h
#define vanchuyen_h

class VanChuyen
{
    string maXe;
    unsigned int sokho;
    HashTable<Kho> dsKho;

public:
    VanChuyen(string ma = "", unsigned int n = 0)
        : sokho(n), dsKho(sokho), maXe(ma) {};
    string getMa() { return maXe; }
    HashTable<Kho> &getKho()
    {
        return dsKho;
    }

    bool remove(const string &maKho)
    {
        for (int i = 0; i < sokho; i++)
        {
            if (dsKho.find(maKho))
            {
                dsKho.erase(maKho);
                sokho--;
                return true;
            }
        }
        return false;
    }

    void add(Kho &khoMoi)
    {
        if (dsKho.find(khoMoi.getMa()) != NULL)
        {
            cout << "Kho " << khoMoi.getMa() << " đã tồn tại trong danh sách kho của xe " << maXe << "." << endl;
            return;
        }

        dsKho.insert(khoMoi);
        sokho++;
        cout << "Kho " << khoMoi.getMa() << " đã được thêm vào danh sách kho của xe " << maXe << "." << endl;
    }

    Kho* findKho(const string &maKho)
{
    return dsKho.find(maKho);  // Gọi hàm find của HashTable để tìm kho theo mã kho
}


    bool isEmpty() const
    {
        return sokho == 0;
    }

    bool docVC(ifstream &file)
    {

        if (!file)
        {
            cout << "Khong the doc file " << endl;
            return false;
        }
        file >> maXe;
        file >> sokho;
        dsKho = HashTable<Kho>(sokho);

        for (unsigned int i = 0; i < sokho; ++i)
        {
            string maKho;
            file >> maKho;
            Kho newKho(maKho);
            dsKho.insert(newKho);
        }
        file.ignore();
        return true;
    }

    bool ghiVC(ofstream &file)
    {
        if (!file)
        {
            cout << "Không thể mở file để ghi." << endl;
            return false;
        }

        // Ghi mã xe
        file << maXe << endl;

        // Ghi số lượng kho
        file << sokho << endl;

        // Ghi danh sách mã kho
        for (int i = 0; i < sokho; ++i)
        {
            Node<Kho> *entry = dsKho.getTableEntry(i);
            while (entry)
            {
                file << entry->data.getMa() << endl;
                entry = entry->next;
            }
        }

        // Ghi thêm một dòng trống giữa các xe để dễ đọc
        file << endl;
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
        cout << maXe << endl;
        for (int i = 0; i < sokho; i++)
            cout << dsKho.getTableEntry(i)->data.getMa() << endl;
    }
};

#endif