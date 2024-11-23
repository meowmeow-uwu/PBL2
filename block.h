#ifndef BLOCK_H
#define BLOCK_H

#include "DonHang.h"
#include "hashtable.h"
#include <string>
#include <iostream>

class Block {
private:
	std::string khoDen;  // Destination warehouse
	HashTable ordList;   // HashTable to store orders

public:
	Block(std::string kho);  // Constructor

	void add(DonHang& ord);  // Add an order
	DonHang* find(const std::string& maDH);  // Find an order by ID
	bool erase(const std::string& maDH);  // Remove an order by ID
	std::string getKhoDen() const;  // Get the destination warehouse name

	void danhSach();  // List all orders in the block
};

#endif // BLOCK_H
