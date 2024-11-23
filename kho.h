#ifndef KHO_H
#define KHO_H

#include <string>
#include "HashTable.h"  // Include header for HashTable
#include "BlockHash.h"  // Include header for BlockHash
#include "DonHang.h"    // Include header for DonHang

class Kho {
private:
  std::string tenKho;  // Warehouse name

public:
  BlockHash blockList;  // Block hash table for blocks in the warehouse
  HashTable ordList;    // Order hash table for orders in the warehouse

  // Constructor to initialize warehouse name
  Kho(const std::string &name);

  // Add an order to the warehouse and related block
  void add(DonHang &ord);

  // Remove an order by its ID
  void erase(std::string &maDH);

  // Find an order by its ID
  DonHang *find(const std::string &maDH);

  // Get the name of the warehouse
  std::string getName();

  // Display all orders in the warehouse
  void danhSach();

  // Show the blocks in the warehouse
  void showBlock(const std::string& kho);
};

#endif // KHO_H
