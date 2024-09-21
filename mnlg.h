#include <string>
#ifndef mnlg_h
#define mnlg_h
#define name_size 15


class Product{
    char* name;         // tên sản phẩm
    int quantity;       //số lượng
    // dùng queue quản lý sản phẩm mới, cũ, hết hạn

    public:

    //constructor
    Product(char* ="", int = 0);

    //destructor
    ~Product();

    // setter
    void setName(const char*&);
    void setQuantity(int=0);

    //getter
    char* getName() const;
    int getQuantity() const;

};

class Warehouse{
    Product* inventory;     //các loại sản phẩm trong kho
    int size;       //số lượng hàng tồn kho
    int capacity;   //sức chứa của kho
    /* dùng hash table để xác định vị trí và đơn giản hóa
    tìm kiếm sản phẩm*/

    public:
    //constructor
    Warehouse(int cap = 100):size(0), capacity(cap){};
    //destructor
    ~Warehouse(){delete [] inventory;};
    //
    void resize();
    void addProduct(char* = "unknown", int = 0);
    void removeProduct(const char*&, int);
    void display() const;
};

#endif