#include <iostream>
#include "dh.h"
using namespace std;
#ifndef hash_h
#define hash_h
 
template <typename T,int TABLE_SIZE>
struct Node{
    T data;
    Node<T, TABLE_SIZE>* next;

    Node(T data): data(data), next(NULL){}
 };

template <typename T, int TABLE_SIZE>
class HashTable{
    private:
        Node<T, TABLE_SIZE>* table[TABLE_SIZE];
    public:
        HashTable(){
            for(int i = 0; i < TABLE_SIZE; i++)
                table[i] = NULL;
        }

        //hash function

int hashFunction(const string& key){
    int hash = 0;
    for(size_t i = 0; i < key.length(); ++i){
        hash = (hash * 31 + key[i]) % TABLE_SIZE;
    }
    return hash;
}
        //insert
        void insert(T& DH){
            int index;
            index = hashFunction(DH.getMaDH());
            Node<T>* newNode = new Node<T>(DH);
            if(!table[index]){
                table[index] = newNode;
            }else{
                Node<T>* current = table[index];
                while(current->next != NULL){
                    current = current->next;
                }
                current->next = newNode;
            }
        }
        //search

        T* find(const string maDH){
            int index = hashFunction(maDH);
            Node<T>* current = table[index];
            while(current){
                if(current->data.getMaDH() == maDH){
                    return &current->data;
                }
                current = current->next;
            }
            return NULL;
        }

        //remove

        bool erase(const string& maDH){
            int index = hashFunction(maDH);
            Node<T>* current = table[index];
            Node<T>* prev = NULL;

            while(current){
                if(current->data.getMaDH() == maDH){
                    if(prev){
                        prev->next = current->next;
                    }else{
                        table[index] = current->next;
                    }
                    delete current;
                    return true;
                }
                prev = current;
                current = current->next;
            }
            return false;
        }

        Node<T>* getTableEntry(int index){
            if(index >=0 && index < TABLE_SIZE){
                return table[index];
            }
            return NULL;
        }
};

#endif