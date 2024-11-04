#include <iostream>
#include "dh.h"
#include "block.h"
#include "hash.h"
using namespace std;

#ifndef kho_h
#define kho_h

class Kho: public Block{
    private:
        string maKho;
        unsigned int soblock;
        HashTable<Block, soblock> block;
       
    public:
        Kho(string name="none", unsigned int num =0, HashTable<Block, soblock> block): maKho(name), soblock(num){
        };

        void addDH(DonHang& newDH){
            DH.insert(newDH);
            string khoDich = newDH.getKhoDich();
            Block* block = (Block*)blocks.find(khoDich);
            if(block == NULL){
                block = new Block(khoDich);
                blocks.insert(*block);
            }
            block->addDH(newDH);
            newDH.setKhoHT(this->name);
        }

        bool removeDH(string& maDH){
            DonHang* dh = DH.find(maDH);
            if(dh){
                string khoDich = dh->getKhoDich();
                Block* block = (Block*)blocks.find(khoDich);
                if(block){
                    block->removeDH(maDH);
                }
                return DH.erase(maDH);
            }
            return false;

        }

        DonHang* searchDH(const string& maDH){
            return DH.find(maDH);
        }






        //

        void showBlock(const string& kho){
            for(int i = 0; i < TABLE_SIZE; i++){
                Node<Block>* entry = blocks.getTableEntry(i);
                while(entry){
                    Block* block = &entry->data;
                    if(block->getKhoDen() == kho){
                        cout<<"Block: "<<block->getKhoDen()<<endl;
                        block->danhSach();
                    }
                    entry = entry->next;
                }
            }
        }
        string getName(){return name;}
};

#endif