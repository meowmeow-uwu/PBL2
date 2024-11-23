#ifndef FUNCTION_H
#define FUNCTION_H
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include "route.h"
#include "donhang.h"
#include "hashtable.h"
#include "block.h"
#include "blockhash.h"
#include "kho.h"
#include "truck.h"
#include "user.h"

using namespace std;

const int KHO_SIZE = 4;
const int TRUCK_SIZE = 5;
/************************************************************* */
//Route
void Route::addPoint(const string& kho, int pos) {
    Point* newP = new Point(kho);

    if (!head) {  //danh sach trong
        head = newP;
        newP->stt = 1;
    }
    else if (pos == 1) {  // chen vao dau
        newP->next = head;
        newP->stt = 1;
        head = newP;

        // cap nhap stt
        Point* tmp = head->next;
        int sttCounter = 2;
        while (tmp) {
            tmp->stt = sttCounter++;
            tmp = tmp->next;
        }
    }
    else {  //chen vao cuoi
        Point* tmp = head;
        int currentPos = 1;

        // duyet den vi tri truoc nut chen
        while (tmp->next && currentPos < pos - 1) {
            tmp = tmp->next;
            currentPos++;
        }

        // neu pos nam ngoai pham vi thi chen vao cuoi
        newP->next = tmp->next;
        tmp->next = newP;

        // cap nhap stt
        newP->stt = currentPos + 1;
        tmp = newP->next;
        int sttCounter = newP->stt + 1;
        while (tmp) {
            tmp->stt = sttCounter++;
            tmp = tmp->next;
        }
    }

    cout << "Da them diem." << endl;
}
void Route::erasePoint(int pos) {
    if (!head) {
        cout << "Danh sach trong." << endl;
        return;
    }
    Point* tmp = head;
    while (tmp) {
        if (tmp->stt == pos) {
            tmp->status = "remove";
            cout << "Bo diem thanh cong" << endl;
            return;
        }
        tmp = tmp->next;
    }
    cout << "Diem can bo khong hop le" << endl;
}
void Route::showRoute() {
    Point* tmp = head;
    if (!head) {
        cout << "Tuyen rong" << endl;
    }
    else {
        while (tmp) {
            cout << tmp->stt << ". " << tmp->diemDem << ": " << tmp->status << endl;
            tmp = tmp->next;
        }
    }
}
Point* Route::getPoint() {
    if (!head) {
        cout << "Tuyen rong" << endl;
        return nullptr;
    }
    Point* tmp = head;
    while (tmp) {
        if (tmp->status == "chua den noi") {
            return tmp;
        }
        tmp = tmp->next;
    }
    return nullptr;
}
void Route::finishPont() {
    Point* tmp = head;
    while (tmp) {
        if (tmp->status == "Da den noi") {
            tmp->status = "Hoan thanh";
        }
        tmp = tmp->next;
    }
}
void DonHang::showInfo() {
    cout << "Ma don hang: " << maDH << endl;
    cout << "Can Nang: " << canNang << endl;
    cout << "Kho hien tai: " << khoHT << endl;
    cout << "Kho nguon: " << khoNguon << endl;
    cout << "Kho dich: " << khoDich << endl;
}
string DonHang::getInfo() {
    return "Ma don hang: " + maDH +
        "\nCan nang: " + to_string(canNang) +
        "kg\nKho nguon: " + khoNguon +
        "\nKho dich: " + khoDich +
        "\nKho hien tai: " + khoHT;
}

/************************************************************* */
//Hashtable
Node::Node(DonHang data) : data(data), next(nullptr) {}

HashTable::HashTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        table[i] = nullptr;
    }
}

int HashTable::hashFunction(const std::string& key) {
    int hash = 0;
    for (char c : key) {
        hash = (hash * 31 + c) % TABLE_SIZE;
    }
    return hash;
}

void HashTable::insert(DonHang& DH) {
    int index = hashFunction(DH.getMaDH());
    Node* newNode = new Node(DH);
    if (!table[index]) {
        table[index] = newNode;
    }
    else {
        Node* current = table[index];
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
}

DonHang* HashTable::find(const std::string& maDH) {
    int index = hashFunction(maDH);
    Node* current = table[index];
    while (current) {
        if (current->data.getMaDH() == maDH) {
            return &current->data;
        }
        current = current->next;
    }
    return nullptr;
}

bool HashTable::erase(const std::string& maDH) {
    int index = hashFunction(maDH);
    Node* current = table[index];
    Node* prev = nullptr;

    while (current) {
        if (current->data.getMaDH() == maDH) {
            if (prev) {
                prev->next = current->next;
            }
            else {
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

Node* HashTable::getTableEntry(int index) {
    if (index >= 0 && index < TABLE_SIZE) {
        return table[index];
    }
    return nullptr;
}



/************************************************************* */
//Block
Block::Block(std::string kho) : khoDen(kho) {}
void Block::add(DonHang& ord) {
    ordList.insert(ord);
}
DonHang* Block::find(const std::string& maDH) {
    return ordList.find(maDH);
}
bool Block::erase(const std::string& maDH) {
    return ordList.erase(maDH);
}
std::string Block::getKhoDen() const {
    return khoDen;
}
void Block::danhSach() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* current = ordList.getTableEntry(i);
        while (current) {
            std::cout << current->data.getMaDH() << std::endl;  // Print order ID
            current = current->next;
        }
    }
}
/************************************************************* */
//Block Hash
BlockNode::BlockNode(Block value) : data(value), next(nullptr) {}
BlockHash::BlockHash() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        table[i] = nullptr;  // Initialize all table entries to nullptr
    }
}
int BlockHash::hashFunction(const std::string& key) {
    int hash = 0;
    for (char c : key) {
        hash = (hash * 31 + c) % TABLE_SIZE;
    }
    return hash;
}
void BlockHash::insert(Block& bl) {
    int index = hashFunction(bl.getKhoDen());
    BlockNode* newNode = new BlockNode(bl);
    if (!table[index]) {
        table[index] = newNode;  // If no collision, insert directly
    }
    else {
        BlockNode* current = table[index];
        while (current->next != nullptr) {  // Traverse to the end of the list
            current = current->next;
        }
        current->next = newNode;  // Insert new node at the end
    }
}
Block* BlockHash::find(const std::string& kho) {
    int index = hashFunction(kho);
    BlockNode* current = table[index];
    while (current) {
        if (current->data.getKhoDen() == kho) {
            return &current->data;  // Return the found Block
        }
        current = current->next;  // Move to the next node
    }
    return nullptr;  // Return nullptr if not found
}
bool BlockHash::erase(const std::string& kho) {
    int index = hashFunction(kho);
    BlockNode* current = table[index];
    BlockNode* prev = nullptr;

    while (current) {
        if (current->data.getKhoDen() == kho) {
            if (prev) {
                prev->next = current->next;  // Remove the node from the list
            }
            else {
                table[index] = current->next;  // Update the table entry
            }
            delete current;  // Delete the node
            return true;  // Return true if deleted
        }
        prev = current;
        current = current->next;  // Move to the next node
    }
    return false;  // Return false if not found
}
BlockNode* BlockHash::getTableEntry(int index) {
    if (index >= 0 && index < TABLE_SIZE) {
        return table[index];  // Return the node at the given index
    }
    return nullptr;  // Return nullptr if index is out of bounds
}
/************************************************************* */
//KHO

Kho::Kho(const std::string& name) : tenKho(name) {}
void Kho::add(DonHang& ord) {
    ordList.insert(ord);  // Insert order into the order hash table

    // Find the block by its destination
    std::string khoDich = ord.getKhoDich();
    Block* bl = blockList.find(khoDich);

    // If block doesn't exist, create it and insert
    if (bl == nullptr) {
        Block newBlock(khoDich);
        blockList.insert(newBlock);
        bl = blockList.find(khoDich);
    }

    // Add the order to the corresponding block
    bl->add(ord);

    // Set the current warehouse for the order
    ord.setKhoHT(this->tenKho);
}
void Kho::erase(std::string& maDH) {
    DonHang* dh = ordList.find(maDH);  // Find the order by its ID
    if (dh) {
        std::string khoDich = dh->getKhoDich();  // Get destination warehouse
        Block* bl = blockList.find(khoDich);    // Find the corresponding block
        if (bl) {
            bl->erase(maDH);  // Erase the order from the block
        }
        ordList.erase(maDH);  // Erase the order from the warehouse
    }
}
DonHang* Kho::find(const std::string& maDH) {
    return ordList.find(maDH);
}
std::string Kho::getName() {
    return tenKho;
}
void Kho::danhSach() {
    std::cout << "Danh sach don hang trong kho " << tenKho << std::endl;
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* current = ordList.getTableEntry(i);
        while (current) {
            std::cout << current->data.getMaDH() << std::endl;  // Print order ID
            current = current->next;
        }
    }
}
void Kho::showBlock(const std::string& kho) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        BlockNode* entry = blockList.getTableEntry(i);
        while (entry) {
            Block* block = &entry->data;
            if (block->getKhoDen() == kho) {  // Check if block's destination matches
                std::cout << "Block: " << block->getKhoDen() << std::endl;
                block->danhSach();  // Display the list of orders in the block
            }
            entry = entry->next;
        }
    }
}
/************************************************************* */
//Truck
Truck::Truck(std::string bks)
    : BKS(bks), capacity(1900), taiTrong(0), status(OFFLINE) {
}
void Truck::lenTuyen(Route& route) {
    pointList = route;
    route.setRouteStatus(ONL);  // Change route status to ONLINE
}
void Truck::lenTai(DonHang& ord, Block& block) {
    DonHang* foundOrd = block.find(ord.getMaDH());
    if (foundOrd != nullptr) {
        if (taiTrong + ord.getCanNang() <= capacity) {
            taiTrong += ord.getCanNang();
            ordList.insert(ord);
            block.erase(ord.getMaDH());
            std::cout << "Xuat thanh cong!!!" << std::endl;
        }
        else {
            std::cout << "Khong the xuat them hang vi vuot qua tai trong xe tai" << std::endl;
        }
    }
}
void Truck::xuongTai(DonHang& ord, Kho& kho) {
    DonHang* foundDH = ordList.find(ord.getMaDH());
    if (foundDH) {
        kho.add(ord);
        ord.setKhoHT(kho.getName());
        ordList.erase(ord.getMaDH());
        taiTrong -= ord.getCanNang();
        std::cout << "Da nhap don thanh cong" << std::endl;
    }
    else {
        std::cout << "Don hang khong co trong danh sach can nhap" << std::endl;
    }
}
void Truck::showInfo() {
    std::cout << "Bien Kiem Soat: " << BKS << std::endl;
    std::cout << "Kho hien tai: " << khoHT << std::endl;
    std::cout << "Kho dich: " << khoDen << std::endl;
    std::cout << "Tai trong hien tai: " << taiTrong << std::endl;
}
void Truck::danhSach() {
    std::cout << "Danh sach don hang tren xe: " << std::endl;
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* current = ordList.getTableEntry(i);
        while (current) {
            std::cout << current->data.getMaDH() << std::endl;  // Print order ID
            current = current->next;
        }
    }
}

std::string Truck::DS() {
    std::string result = "List Order:\n";
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* current = ordList.getTableEntry(i);
        while (current) {
            result += current->data.getMaDH() + "\n";
            current = current->next;
        }
    }
    return result;
}

std::string* Truck::dsMaDH(int numOrders) {
    std::string* danhSachDonHang = new std::string[numOrders]; // Cấp phát mảng động
    int index = 0;

    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* current = ordList.getTableEntry(i);
        while (current) {
            if (index >= numOrders) {
                throw std::overflow_error("Số lượng đơn hàng vượt quá giới hạn đã biết!");
            }
            danhSachDonHang[index++] = current->data.getMaDH(); // Lưu mã đơn hàng vào mảng
            current = current->next;
        }
    }
    return danhSachDonHang; // Trả về con trỏ tới mảng
}
 
int Truck::soDH() {
    int count=0;
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* current = ordList.getTableEntry(i);
        while (current) {
            ++count;
            current = current->next;
        }
    }
    return count;
}
void Truck::add(DonHang& dh) {
    ordList.insert(dh);
}
std::string Truck::getKhoHT() { return khoHT; }
std::string Truck::getKhoDen() { return khoDen; }
std::string Truck::getBKS() { return BKS; }
double Truck::getTaiTrong() { return taiTrong; }
double Truck::getCapacity() { return capacity; }
TruckStatus Truck::getStatus() { return status; }  // Return the status as an enum

// Setter for status (using enum)
void Truck::setKhoHT(std::string name) { khoHT = name; }
void Truck::setKhoDen(std::string name) { khoDen = name; }
void Truck::setStatus(TruckStatus newStatus) { status = newStatus; }  // Set status as enum
/************************************************************* */
//User


/************************************************************* */
void readFile(HashTable& listOrd, Kho* khoArr[], string filename) {
    ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return;
    }

    string line;
    int i = 0;
    while (getline(inputFile, line)) {
        stringstream ss(line);
        string ma, nguon, dich, hientai;
        double wei;

        if (!(ss >> ma >> wei >> nguon >> dich >> hientai)) {
            cerr << "Error: Invalid data format in line: " << line << endl;
            continue; // Skip to the next line
        }

        DonHang dh(ma, wei, nguon, dich, hientai);
        listOrd.insert(dh);
        for (int i = 0; i < KHO_SIZE; i++) {
            if (hientai == khoArr[i]->getName()) {
                khoArr[i]->add(dh);
                break;
            }
            else if (hientai == "None") {
                continue;
            }
        }
    }


    inputFile.close();
}
void init(HashTable*& hash, Kho* khoArr[], Route* route[], Truck* truckArr[], User& user) {
    // Initialize HashTable
    hash = new HashTable();

    // Initialize Kho array
    khoArr[0] = new Kho("HCM");
    khoArr[1] = new Kho("DN");
    khoArr[2] = new Kho("CT");
    khoArr[3] = new Kho("HN");

    // Initialize and read file
    string filename = "donhang.txt";
    readFile(*hash, khoArr, filename);

    // Initialize Route and add points
    route[0] = new Route();
    route[1] = new Route();
    route[0]->addPoint("DN", 1);
    route[0]->addPoint("HCM", 2);
    route[0]->addPoint("CT", 3);
    route[0]->addPoint("DN", 4);
    route[0]->addPoint("HN", 5);

    route[1]->addPoint("HN", 1);
    route[1]->addPoint("DN", 2);
    route[1]->addPoint("HN", 3);


    // Initialize Truck array and assign route to the first truck
    truckArr[0] = new Truck("12345");
    truckArr[1] = new Truck("67890");
    truckArr[2] = new Truck("10111");
    truckArr[3] = new Truck("12131");
    truckArr[4] = new Truck("14151");
    truckArr[0]->lenTuyen(*route[0]);
    truckArr[1]->lenTuyen(*route[1]);
    DonHang* dh1 = new DonHang("DH0105", 20, "HN", "DN", "None");
    DonHang* dh2 = new DonHang("DH0106", 22, "HCM", "DN", "None");
    DonHang* dh3 = new DonHang("DH0107", 25, "CT", "DN", "None");
    DonHang* dh4 = new DonHang("DH0108", 29, "HN", "DN", "None");
    truckArr[0]->add(*dh1);
    truckArr[0]->add(*dh2);
    truckArr[0]->add(*dh3);
    truckArr[0]->add(*dh4);
    //Point* p = truckArr[1]->pointList.getPoint();
    //p->status = "Da hoan thanh";
    // Initialize User
    user = User("admin", "123", "DN");
}

/************************************************************* */
void search(HashTable* ht) {
    string ma;
    cout << "Nhap ma don hang: ";
    cin >> ma;
    DonHang* DH = ht->find(ma);
    if (DH) {
        DH->showInfo();
    }
    else {
        cout << "Khong tim thay don hang" << endl;
    }
}

string timDH(HashTable* hash, string ma) {
    DonHang* DH = hash->find(ma);
    if (DH) {
        return DH->getInfo();
    }
    else {
        return "Khong tim thay don hang";
    }
}

void coming(Truck* truckArr[], User user);

void nhapHang(Truck* truckArr[], User user, Kho* khoArr[]) {
    int ch;
    int a = 1;
    while (a == 1) {
        cout << "1. Den noi" << endl
            << "2. Nhap hang" << endl
            << "3. Back" << endl
            << "Chon: ";
        cin >> ch;
        switch (ch) {
        case 1: {
            coming(truckArr, user);
            break;
        }
        case 2: {
            string bs;
            cout << "Nhap BKS: ";
            cin >> bs;

            Truck* truck = nullptr;
            for (int i = 0; i < TRUCK_SIZE; i++) {
                if (truckArr[i]->getBKS() == bs) {
                    truck = truckArr[i];
                    break;
                }
            }

            if (truck == nullptr) {
                cout << "khong ton tai xe " << bs << endl;
                return;
            }
            if (truck->getStatus() == 0) {
                cout << "Xe van chua den noi khong the nhap hang" << endl;
                return;
            }

            while (1) {
                truck->danhSach();
                string ma;
                cout << "Nhap ma don hang (nhap 00 de thoat): ";
                cin >> ma;
                if (ma == "00") break;
                DonHang* DH = truck->ordList.find(ma);
                if (DH == nullptr) {
                    cout << "khong tim thay don hang " << ma << " tren xe" << endl;
                    continue;
                }
                string khoName = user.getKhoLamViec();
                Kho* kho = nullptr;
                for (int i = 0; i < KHO_SIZE; i++) {
                    if (khoArr[i]->getName() == khoName) {
                        kho = khoArr[i];
                        break;
                    }
                }
                if (kho) {
                    truck->xuongTai(*DH, *kho);
                }
            }
            int b;
            cout << "Nhap 1 de chot hoan thanh diem va cho xe di: ";
            cin >> b;
            if (b == 1) {
                truck->pointList.finishPont();
                truck->setStatus(OFFLINE);

            }
            break;
        }
        case 3: {
            a = 0;
            break;
        }
        }
        if (a == 0) {
            break;
        }
    }
}

void xuatHang(Truck* truckArr[], int num, User user, Kho* khoArr[], int n) {
    int a = 1;
    while (a == 1) {
        int ch;
        cout << "1. Den noi." << endl
            << "2. Xuat hang." << endl
            << "3. Back." << endl
            << "Lua chon: ";
        cin >> ch;
        switch (ch) {
        case 1: {
            coming(truckArr, user);
        }
              break;
        case 2: {
            string bs;
            cout << "Nhap BKS: ";
            cin >> bs;
            int check = 0;
            Truck* truck = nullptr;
            for (int i = 0; i < num; i++) {
                if (truckArr[i]->getBKS() == bs) {
                    truck = truckArr[i];
                    check = 1;
                    break;
                }
            }
            if (check == 0) {
                cout << "khong ton tai xe " << bs << endl;
                return;
            }
            if (truck->getStatus() == 0) {
                cout << "Xe van chua den noi khong the xuat hang" << endl;
                return;
            }
            Point* p = truck->pointList.getPoint();
            Point* tmp = p;
            Kho* kho = nullptr;
            for (int j = 0; j < KHO_SIZE; j++) {
                if (khoArr[j]->getName() == user.getKhoLamViec()) {
                    kho = khoArr[j];
                    break;
                }
            }

            if (kho == nullptr) {
                cout << "Khong tim thay kho " << kho << endl;
                return;
            }

            while (tmp->diemDem != user.getKhoLamViec() && tmp->next != nullptr) {
                kho->showBlock(tmp->diemDem);
                tmp = tmp->next;
            }


            while (1) {

                string ma;
                cout << "Nhap ma don hang (nhap 00 de thoat): ";
                cin >> ma;
                if (ma == "00") break;
                DonHang* dh = kho->find(ma);
                if (dh == nullptr) {
                    cout << "Khong tim thay don hang " << ma << " trong kho" << endl;
                    continue;
                }
                string khoDich = dh->getKhoDich();
                Block* block = kho->blockList.find(khoDich);
                if (block == nullptr) {
                    cout << "Khong tim thay block cho kho dich " << khoDich << endl;
                    continue;
                }
                truck->lenTai(*dh, *block);
            }
            int b;
            cout << "Nhap 1 de chot diem hoan thanh va cho xe di: ";
            cin >> b;
            if (b == 1) {
                truck->pointList.finishPont();
                truck->setStatus(OFFLINE);
            }
        }
        case 3: {
            a = 0;
            break;
        }
        }
        if (a == 0) {
            break;
        }
    }
}


/************************************************************* */
void routeManage(Truck* truckArr[]) {
    string bks;
    int check = 0;
    cout << "Nhap BKS: ";
    cin >> bks;
    int i;
    for (i = 0; i < TRUCK_SIZE; i++) {
        if (bks == truckArr[i]->getBKS()) {
            truckArr[i]->pointList.showRoute();
            break;
        }
    }
    while (check == 0) {
        string diem;
        int pos, choice;
        cout << "1. Them diem.\n2. Bo diem.\n3. Back.\nLua chon:";
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            cout << "Them diem: "; cin >> diem;
            cout << "Vi tri: "; cin >> pos;
            truckArr[i]->pointList.addPoint(diem, pos);
            truckArr[i]->pointList.showRoute();
        }
        break;
        case 2:
        {
            cout << "chon vi tri diem can bo: ";cin >> pos;
            truckArr[i]->pointList.erasePoint(pos);
            truckArr[i]->pointList.showRoute();
        }
        case 3:
            check = 1;
            break;
        default:
            cout << "Lua chon khong hop le chon lai." << endl;
            break;
        }
    }
}

void coming(Truck* truckArr[], User user) {
    string bks;
    cout << "Nhap BKS: ";
    cin >> bks;
    int i;
    for (i = 0; i < TRUCK_SIZE; i++) {
        if (truckArr[i]->getBKS() == bks)
        break;
    }
    Point* pon = truckArr[i]->pointList.getPoint();
    if (user.getKhoLamViec() == pon->diemDem) {
        pon->status = "Da den noi";
        truckArr[i]->setStatus(ONLINE);
        Point* nextPon = truckArr[i]->pointList.getPoint();
        truckArr[i]->setKhoHT(user.getKhoLamViec());
        truckArr[i]->setKhoDen(nextPon->diemDem);
        cout << "Da den noi thanh cong" << endl;
    }
    else {
        cout << "Diem den khong dung" << endl;
    }
}

void checkin(Truck* truckArr[], User user, string bks) {
    
    int i;
    for (i = 0; i < TRUCK_SIZE; i++) {
        if (truckArr[i]->getBKS() == bks)
            break;
    }
    Point* pon = truckArr[i]->pointList.getPoint();
    if (user.getKhoLamViec() == pon->diemDem) {
        pon->status = "Da den noi";
        truckArr[i]->setStatus(ONLINE);
        Point* nextPon = truckArr[i]->pointList.getPoint();
        truckArr[i]->setKhoHT(user.getKhoLamViec());
        truckArr[i]->setKhoDen(nextPon->diemDem);
        cout << "Da den noi thanh cong" << endl;
    }
    else {
        cout << "Diem den khong dung" << endl;
    }
}

string checkout(Truck* truckArr[], string bks) {
    int i = 0;
    while (i < TRUCK_SIZE) {
        if (truckArr[i]->getBKS() == bks) {
            truckArr[i]->pointList.finishPont();
            truckArr[i]->setStatus(OFFLINE);
            return "Checked out";
        }
    }
    return "Khong ton tai xe";
}
/************************************************************* */
void writeFile(HashTable& listOrd, Kho* khoArr[], Truck* truckArr[], string filename) {
    ofstream outputFile(filename);

    if (!outputFile.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return;
    }

    // Write all orders in the HashTable to the file
    for (int i = 0; i < TABLE_SIZE; i++) {  // Assuming HashTable supports iteration or similar
        Node* current = listOrd.getTableEntry(i);
        while (current) {
            outputFile << current->data.getMaDH() << " "
                << current->data.getCanNang() << " "
                << current->data.getKhoNguon() << " "
                << current->data.getKhoDich() << " "
                << current->data.getKhoHT() << endl;
            current = current->next;
        }

    }
    outputFile.close();
    // Write each warehouse's orders to the file
    for (int i = 0; i < KHO_SIZE; i++) {
        Kho* kho = khoArr[i];
        string f = kho->getName() + "_ordList.txt";
        ofstream khoFile(f);
        if (!khoFile.is_open()) {
            cout << "Khong the mo file " << f << endl;
            continue;
        }
        // Assuming Kho has a method to iterate over its `danhSachDonHang`
        for (int i = 0; i < TABLE_SIZE; i++) {
            Node* current = kho->ordList.getTableEntry(i);
            while (current) {
                khoFile << current->data.getMaDH() << " "
                    << current->data.getCanNang() << " "
                    << current->data.getKhoNguon() << " "
                    << current->data.getKhoDich() << " "
                    << current->data.getKhoHT() << endl;
                current = current->next;
            }
        }
        khoFile.close();
    }

    for (int i = 0; i < TRUCK_SIZE; i++) {
        string fi = "truck" + truckArr[i]->getBKS() + "_ordList.txt";
        ofstream truckFile(fi);
        if (!truckFile.is_open()) {
            cout << "Khong the mo file" << fi << endl;
            continue;
        }
        for (int i = 0; i < TABLE_SIZE; i++) {
            Node* current = truckArr[i]->ordList.getTableEntry(i);
            while (current) {
                truckFile << current->data.getMaDH() << " "
                    << current->data.getCanNang() << " "
                    << current->data.getKhoNguon() << " "
                    << current->data.getKhoDich() << " "
                    << current->data.getKhoHT() << endl;
                current = current->next;
            }
        }
        truckFile.close();
    }
}

std::string taiTrong(Truck* truckArr[], string bks) {
    int i;
    for (i = 0; i < TRUCK_SIZE; i++) {
        if (truckArr[i]->getBKS() == bks) {
            Truck* truck = truckArr[i];
            std::string sodh = to_string(truck->soDH());
            std::string tt = to_string(truck->getTaiTrong());
            std::string tmp = " | " + sodh + "DH " + tt + "kg";
            return tmp;
        }
    }
    return "";
}
int isTruck(Truck* truckArr[], string bks) {
    for (int i = 0; i < TRUCK_SIZE; i++) {
        if (truckArr[i]->getBKS() == bks)
            cout << "tim thay" << endl;
            return 1;
        break;
    }
    return 0;
}

bool islogin(string us, string pw) {
    if (us == "admin" && pw == "123") {
        return true;
    }
    return false;
}


Truck truck(Truck* truckArr[], string bks) {
    for (int i = 0; i < 4; i++) {
        if (truckArr[i]->getBKS() == bks && truckArr[i] != nullptr) {
            cout << "da tim thay" << endl;
            Truck* tr = truckArr[i];
            return *tr;
        }
    }
    cout << "Khong tim thay" << endl;
}

#endif