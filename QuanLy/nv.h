#include <iostream>
using namespace std;

#ifndef nv_h
#define nv_h

//thong tin nhan vien
class NhanVien{
    private:
        string maNV;
        string user;
        string pass;
        string maKho;
    public:
        NhanVien(string username="", string password="", string kho="") : user(username), pass(password), maKho(kho){};
        void login();
};
//dang nhap
void NhanVien::login(){
    int check;
    do{
        cout<< "User Name: ";
        cin>>user;
        cout<< "Password: ";
        cin>>pass;
        if(user == "admin" && pass== "123"){
            check = 1;
            cout<<"Welcome "+user+" login success!!"<<endl;
        }else{
            check = 0;
            cout<<"Thong tin nhap vao sai vui long nhap lai!!!"<<endl;
        }
    }while(check == 0);
}

#endif