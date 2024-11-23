#ifndef DONHANG_H
#define DONHANG_H

#include<string.h>
#include<iostream>
 using namespace std;

 class DonHang {
private:
  string maDH;
  double canNang;
  string khoNguon;
  string khoDich;
  string khoHT;

public:
  DonHang() : maDH(""), canNang(0), khoNguon(""), khoDich(""), khoHT("") {}
  DonHang(string ma, double wei, string nguon, string dich, string ht)
      : maDH(ma), canNang(wei), khoNguon(nguon), khoDich(dich),
        khoHT(ht) {}

  // getter
  string getMaDH() { return maDH; }
  double getCanNang() { return canNang; }
  string getKhoNguon() { return khoNguon; }
  string getKhoDich() { return khoDich; }
  string getKhoHT() { return khoHT; }

  // setter
  void setMaDH(string ma) { maDH = ma; }
  void setCanNang(double wei) { canNang = wei; }
  void setKhoNguon(string nguon) { khoNguon = nguon; }
  void setKhoDich(string dich) { khoDich = dich; }
  void setKhoHT(string khoht) { khoHT = khoht; }

  // method

  void showInfo();
  string getInfo();
};



#endif