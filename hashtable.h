#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "DonHang.h"  // Assuming DonHang is defined in DonHang.h

const int TABLE_SIZE = 1000;  // Define the table size (adjust as needed)

struct Node {
  DonHang data;
  Node *next;
  Node(DonHang data);
};

class HashTable {
protected:
  Node *table[TABLE_SIZE];

public:
  HashTable();
  int hashFunction(const std::string &key);
  void insert(DonHang &DH);
  DonHang *find(const std::string &maDH);
  bool erase(const std::string &maDH);
  Node *getTableEntry(int index);

};

#endif // HASHTABLE_H
