#ifndef BLOCKHASH_H
#define BLOCKHASH_H

#include "Block.h"  // Include Block class header
#include <string>


struct BlockNode {
  Block data;
  BlockNode *next;

  BlockNode(Block value);  // Constructor for BlockNode
};

class BlockHash {
private:
  BlockNode *table[TABLE_SIZE];  // Hash table array

public:
  BlockHash();  // Constructor
  int hashFunction(const std::string &key);  // Hash function
  void insert(Block &bl);  // Insert a Block into the table
  Block* find(const std::string &kho);  // Find a Block by warehouse name
  bool erase(const std::string &kho);  // Remove a Block by warehouse name
  BlockNode* getTableEntry(int index);  // Get a table entry by index
};

#endif // BLOCKHASH_H
