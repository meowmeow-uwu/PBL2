#ifndef USER_H
#define USER_H
#include<iostream>
#include<string.h>
using namespace std;
class User{
    private:
        string user;
        string pass;
        string khoLamViec;
    public:
        User() : user(""), pass(""), khoLamViec(""){};
        User(string username, string password, string kho) : user(username), pass(password), khoLamViec(kho){};


        //getter

        string getUser(){ return user;}
        string getPass(){ return pass;}
        string getKhoLamViec(){ return khoLamViec;}

        //setter

        void setUser(string username){ user = username;}
        void setPass(string password){ pass = password;}
        void setKhoLamViec(string kho){ khoLamViec = kho;}
        int islogin(string us, string pw);
};

#endif