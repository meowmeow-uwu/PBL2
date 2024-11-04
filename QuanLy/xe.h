#include <iostream>
#include "kho.h"
#include "dh.h"
using namespace std;

#ifndef xe_h
#define xe_h

class Truck: public DonHang{
    private:
        string BKS;
        unsigned int n;
        HashTable<DonHang, n> DH;
    public:
        Truck(string bienso="", int n = 0)
        : BKS(bienso), DH(new DonHang[n]){}





        void lenTai(DonHang& dh, Block& block){
            DonHang* foundDH = block.find(dh.getMaDH());
            if(foundDH){
                if(capacity-taiTrong<dh.getCanNang()){
                    cout<<"Xe qua tai! khong the xuat them."<<endl;
                    return;
                }
                DH.insert(*foundDH);
                block.removeDH(dh.getMaDH());
                taiTrong += dh.getCanNang();
                dh.setKhoHT("None");
                cout<<"Da quet xuat thang cong!"<<endl;
            }else{
                cout<<"Don hang khong co trong kho"<<endl;
            }
        }

        void xuongTai(DonHang& dh, Kho& kho){
            DonHang* ord = DH.find(dh.getMaDH());
            if(ord){
                kho.addDH(*ord);
                ord->setKhoHT(kho.getName());
                DH.erase(dh.getMaDH());
                taiTrong -= dh.getCanNang();
                cout<<"Da quet nhap thanh cong"<<endl;
            }else{
                cout<<"Don hang khong co trong danh sach can nhap tren xe!"<<endl;
            }
        }

        void danhSach(){
            cout<<"Danh sach don hang tren xe: "<<endl;
            for(int i =0; i <TABLE_SIZE;i++){
                Node<DonHang>* current = DH.getTableEntry(i);
                while(current){
                    cout<<current->data.getMaDH()<<endl;//xem lai
                    current = current->next;
                }
            }
        }

        void addOrd(DonHang& dh){
            DH.insert(dh);
        }

        //getter
        string getKhoHT(){return khoHT;}
        string getKhoDen(){return khoDen;}
        string getBKS(){return BKS;}
        double getTaiTrong(){return taiTrong;}
        double getCapacity(){return capacity;}
        int getStatus(){return status;}
        //setter
        void setKhoHT(string name){khoHT = name;}
        void setKhoDen(string name){khoDen = name;}
        void setStatus(int i){
            if(i==0){
            status = i;
            }else{
                status = 1;
            }
        }
};

#endif