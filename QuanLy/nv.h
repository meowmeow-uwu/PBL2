#include <iostream>
#include <fstream>
using namespace std;

#ifndef nv_h
#define nv_h

// thong tin nhan vien
class NhanVien
{
private:
    string maNV;
    string user;
    string pass;
    string maKho;

public:
    NhanVien(string maNV = "", string username = "", string password = "", string kho = "") : maNV(maNV),user(username), pass(password), maKho(kho) {};
    string getKho() { return maKho; }
    string getMa() { return maNV; }
    bool login()
    {
        string u, p;
        if (u == user && p == pass)
            return true;
        return false;
    };

    bool docNV(ifstream &file)
    {

        if (!file)
        {
            cout << "Khong the doc file " << endl;
            return false;
        }
        file >> maNV >> user >> pass >> maKho;
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
        cout << maNV << " " << user << "  " << pass << " " << maKho << endl;
    }
};

#endif