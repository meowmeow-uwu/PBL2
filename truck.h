#ifndef TRUCK_H
#define TRUCK_H

#include <iostream>
#include "route.h"  // Assuming you have the Route class in a separate file.
#include "hashtable.h"  // Assuming you have a HashTable implementation.

enum TruckStatus { OFFLINE = 0, ONLINE = 1 };  // Enum for truck status

class Truck {
private:
  std::string BKS, khoHT, khoDen;
  double taiTrong, capacity;
  TruckStatus status;  // Use enum instead of int for status

public:
  Route pointList;
  HashTable ordList;

  // Constructor for Truck

  Truck(std::string bks);
  Truck();

  // Set the route for the truck
  void lenTuyen(Route& route);

  // Load an order onto the truck
  void lenTai(DonHang& ord, Block& block);

  // Unload an order from the truck into a warehouse
  void xuongTai(DonHang& ord, Kho& kho);

  // Display truck information
  void showInfo();

  // Display the list of orders on the truck
  void danhSach();
  string DS();

  // Add an order to the truck's order list
  void add(DonHang& dh);

  string* dsMaDH(int numOrders);

  // Getters and setters
  std::string getKhoHT();
  std::string getKhoDen();
  std::string getBKS();
  double getTaiTrong();
  double getCapacity();
  TruckStatus getStatus();  // Return the status as an enum
  int soDH();//so don hang tren xe

  // Setter for status (using enum)
  void setKhoHT(std::string name);
  void setKhoDen(std::string name);
  void setStatus(TruckStatus newStatus);  // Set status as enum
};

#endif // TRUCK_H
