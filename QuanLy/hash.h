#include <iostream>
using namespace std;
#ifndef hash_h
#define hash_h

template <typename T>
struct Node
{
    T data;
    Node<T> *next;

    Node(T data) : data(data), next(NULL) {}
};

template <typename T>
class HashTable
{
private:
    Node<T> **table;
    unsigned int tableSize;
    unsigned int maxSize;

public:
    HashTable(unsigned int size = 10) : tableSize(size)
    {
        if (tableSize == 0)
        {
            table = NULL;
            return;
        }
        maxSize = 100;
        table = new Node<T> *[maxSize];
        for (unsigned int i = 0; i < maxSize; i++)
            table[i] = NULL;
    }

    ~HashTable()
    {
        for (unsigned int i = 0; i < tableSize; i++)
        {
            Node<T> *current = table[i];
            while (current)
            {
                Node<T> *temp = current;
                current = current->next;
                delete temp;
            }
        }
        delete[] table;
    }

    unsigned int getSize() const
    {
        return tableSize;
    }

    // Hash function
    int hashFunction(const string &key) const
    {
        int hash = 0;
        for (size_t i = 0; i < key.length(); ++i)
        {
            hash = (hash * 31 + key[i]) % tableSize;
        }
        return abs(hash);
    }

    // Insert
    void insert(T &ma)
    {
        if (tableSize == 0)
        {
            return;
        }

        int index = hashFunction(ma.getMa());
        Node<T> *newNode = new Node<T>(ma);

        if (table[index] == NULL)
        {
            table[index] = newNode;
        }
        else
        {
            Node<T> *current = table[index];
            while (current->next != NULL)
            {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    // Find
    T *find(const string &ma)
    {
        if (tableSize == 0)
            return NULL;

        int index = hashFunction(ma);
        Node<T> *current = table[index];
        while (current)
        {
            if (current->data.getMa() == ma)
            {
                return &current->data;
            }
            current = current->next;
        }
        return NULL;
    }

    // Erase
    bool erase(const string &ma)
    {
        if (tableSize == 0)
            return false;

        int index = hashFunction(ma);
        Node<T> *current = table[index];
        Node<T> *prev = NULL;

        while (current)
        {
            if (current->data.getMa() == ma)
            {
                if (prev)
                {
                    prev->next = current->next;
                }
                else
                {
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

    Node<T> *getTableEntry(int index)
    {
        if (tableSize == 0 || index < 0 || index >= tableSize)
        {
            return NULL;
        }
        return table[index];
    }

    HashTable<T> &operator=(const HashTable<T> &other)
    {
        if (this != &other)
        {
            // Xóa dữ liệu cũ
            for (unsigned int i = 0; i < tableSize; i++)
            {
                Node<T> *current = table[i];
                while (current)
                {
                    Node<T> *temp = current;
                    current = current->next;
                    delete temp;
                }
            }
            delete[] table;

            // Sao chép từ `other`
            tableSize = other.tableSize;
            table = new Node<T> *[tableSize];
            for (unsigned int i = 0; i < tableSize; i++)
            {
                table[i] = NULL;
                if (other.table[i])
                {
                    Node<T> *current = other.table[i];
                    while (current)
                    {
                        T data = current->data;
                        this->insert(data);
                        current = current->next;
                    }
                }
            }
        }
        return *this;
    }
};

#endif
