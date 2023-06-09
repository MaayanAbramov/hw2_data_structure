//
// Created by maaya on 08/06/2023.
//

#ifndef RECORDSCOMPANY_HASH2_H
#define RECORDSCOMPANY_HASH2_H
#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <exception>
#include <ostream>
#include "Deque.h"

template <class T>
class Hash_Table {
    static const int default_size = 16;
    int size;
    int currentSize;
    Deque<T> *arr; //מערך של רשימות מקושרות
    Getter<T> *pred;

public:
    explicit Hash_Table(Getter<T>* pred):size(default_size), currentSize(0), arr(new Deque<T>[default_size]), pred(pred){
        for(int i = 0; i < default_size; i++)
            arr[i].setPred(pred);
    }
    void updatePred(Deque<T>* arr1, int size1, Getter<T>* pred1)
    {
        for(int i = 0; i < size1; i++)
            arr1[i].setPred(pred1);
    }

    int hash(const T& data)
    {
        return (*pred)(data) % size;
    }

    int hash(int key)
    {
        return key % size;
    }

    bool insert(const T& toAdd)
    {
        Deque<T> *list = &arr[hash(toAdd)];
        if(list->find((*pred)(toAdd)) != nullptr)
            return false;
        list->add(toAdd);
        currentSize++;
        changeSizeIfNeeded();
        return true;
    }

    bool remove(const T& toRemove)
    {
        Deque<T> *list = &arr[hash(toRemove)];
        if(list->find((*pred)(toRemove)) == nullptr)
            return false;
        list->remove((*pred)(toRemove));
        currentSize--;
        changeSizeIfNeeded();
        return true;
    }


    T* find(int key)
    {
        Deque<T>* oldList = &arr[hash(key)];
        auto node = oldList->find(key);
        if(node == nullptr)
            return nullptr;
        return &(node->data);
    }

    void changeSizeIfNeeded()
    {
        if(size <= 8)
            return;
        if(currentSize >= size)
        {
            auto temp = new Deque<T>[size*2];
            int tempSize = size;
            size = size*2;
            updatePred(temp, size, pred);
            for(int i = 0 ; i < tempSize; i++)
            {
                Deque<T>* oldList = &arr[i];
                typename Deque<T>::node* node = oldList->head;
                while(node != nullptr)
                {
                    Deque<T>* list = &temp[hash(node->data)];
                    list->add(node->data);
                    node = node->next;
                }
            }
            delete[] arr;
            arr = temp;
        }
        else if(currentSize <= 0.25*size)
        {
            auto temp = new Deque<T>[size/2];
            int tempSize = size;
            size = size/2;
            updatePred(temp, size, pred);
            for(int i = 0 ; i < tempSize; i++)
            {
                Deque<T>* oldList = &arr[i];
                typename Deque<T>::node* runner = oldList->head;
                while(runner != nullptr)
                {
                    Deque<T>* list = &temp[hash(runner->data)];
                    list->add(runner->data);
                    runner = runner->next;
                }
            }
            delete[] arr;
            arr = temp;
        }
        return;
    }

    friend std::ostream& operator<<(std::ostream &os, const Hash_Table<T>& hash)
    {
        os << "size:" << hash.size << "current size: "<< hash.currentSize << std::endl;
        for(int i = 0; i < hash.size; i++)
            os << "arr[" << i << "]: " << hash.arr[i];
        os << std::endl;
        return os;
    }

    ~Hash_Table(){
        delete[] arr;
        delete pred;
    }
};







#endif

#endif //RECORDSCOMPANY_HASH2_H
