//
// Created by maaya on 07/06/2023.
//

#ifndef RECORDSCOMPANY_HASH_TABLE_H
#define RECORDSCOMPANY_HASH_TABLE_H
using namespace std;
#include <iostream>
#include "AvlTree.h"
/*template <class T>
class Getter{
public:
    int operator()(const T&) = 0;
};*/

template <class T>
class hash_table{
public:

    class object {

        int m_key;
        const T *m_object;

        friend class hash_table<T>;



    public:
        //----------------the big three---------------
        explicit object(const T* object, int key);  //we don't want the constructor to do implicit conversion between
        // types
        ~object() = default;

        object(const object &other) = default;

        //----------------the big three---------------


        T *get_object() const;

        //void  set_object(const T *object);

        //there is no reason to create a setter function for this boolean field
        //the reason is that the function that responible for the size multipication will indicate this for us.

        int get_key() const;
        //no reason to create a setter function for this field


        //--------------------------operators------------
        object &operator=(const object &array_object2);
        bool operator==(const object& array_object2);
        bool operator<(const object& arr_obj2) const;
        bool operator>(const object& arr_obj2) const;









    };
    //remember this is the hash class

private:
    static const int default_Length = 16;
    int m_size; // this is the size of the array
    int m_count_elements;
    //AvlTree<object> m_array[default_Length]; //every field in the array will be tree
    AvlTree<object>* m_array;

public:
    /*-------------------- the big three ----------------*/
    explicit hash_table();
    ~hash_table();
    hash_table(const hash_table<T>& other) = delete;

    /*--------------- process functions--------------------*/
    int hash(int key);

    const T* find(int key);

    void changeSizeIfNeeded();


    bool insert_to_array(const T& toAdd, int key);

    bool remove_from_array(const T& toRemove, int key);



    //friend std::ostream& operator<<(std::ostream &os, const hash_table<T>& hash);





};



template <class T>
hash_table<T>::object::object(const T* object, int key) : m_key(key), m_object(object){}


template <class T>
T* hash_table<T>::object::get_object() const{
    return m_object;
}
/*
template <class T>
void hash_table<T>::object::set_object(const T *object) {
    m_object = object;
}*/

/*template <class T>
bool hash_table<T>::object::get_is_insertion_available() const {
    return m_is_insertion_available;
}*/

template <class T>
int hash_table<T>::object::get_key() const {
    return m_key;
}

template <class T>
typename hash_table<T>::object& hash_table<T>::object::operator=(const hash_table::object& array_object2) {
    if (this == &array_object2) {
        return *this;
    }
    m_object = array_object2.m_object;
    m_key = array_object2.get_key();
    //m_is_insertion_available = array_object2.get_is_insertion_available();

    return *this;
}


template<class T>
bool hash_table<T>::object::operator==(const hash_table::object
                                             &array_object2) {
    return array_object2.m_key == this->m_key;
}

template <class T>
bool hash_table<T>::object::operator<(const object& arr_obj2) const {
    return this->m_key < arr_obj2.get_key();
}

template <class T>
bool hash_table<T>::object::operator>(const object& arr_obj2) const {
    return this->m_key < arr_obj2.get_key();
}

/*-------------------------- hash table ---------------*/
template <class T>
hash_table<T>::hash_table(): m_size(default_Length), m_count_elements(0){
    this->m_array = new AvlTree<object>[m_size];
    for (int i = 0; i < m_size; i++) {
        m_array[i] = AvlTree<object>(); // Initialize each tree in the array
    }

}



template <class T>
hash_table<T>::~hash_table() {
    delete[] m_array;
}

template <class T>
int hash_table<T>::hash(int key) {
    return key % m_size;
}

template <class T>
const T* hash_table<T>::find(int key) {
    int index_in_array = hash(key);
    object toFind(nullptr, key);
    AvlTree<object>* current_tree = &m_array[index_in_array];
    bool is_exist = current_tree->is_key_exists(m_array[index_in_array].ptr_main_root, toFind);
    if (!is_exist) {
        return nullptr;
    }
    else {
        object* toReturn = current_tree->find_pointer(m_array[index_in_array].ptr_main_root, toFind);

        return toReturn->m_object;
    }
}

template <class T>
void hash_table<T>::changeSizeIfNeeded() {
    if (m_count_elements <= default_Length/2) {
        return;
    }
    if (m_count_elements >= m_size) {
        int backupToSize = m_size;
        m_size = m_size*2;
        AvlTree<object> updatedArray[m_size];
        for (int i = 0 ; i < backupToSize ; i++) {
            auto ptr_to_tree = &m_array[i];
            updatedArray[i] = *ptr_to_tree;
        }
        delete[] m_array;
        m_array = updatedArray;
    }
    else if(m_count_elements <= 0.25*m_size) {
        int backUpToSize = m_size;
        m_size = m_size/2;
        AvlTree<object> updatedArray[m_size];
        for (int i = 0 ; i < backUpToSize ; i++) {
            auto ptr_to_tree = &m_array[i];
            updatedArray[hash(i)] = *ptr_to_tree;
        }
        delete[] m_array;
        m_array = updatedArray;
    }
    return;
}


template <class T>
bool hash_table<T>::insert_to_array(const T& objectToAdd, int key) {
    if (find(key)) {
        return false;
    }
    object toAdd(&objectToAdd, key);
    int hash_key = hash(key);
    m_array[hash_key].ptr_main_root = m_array[hash_key].insert(m_array[hash_key].ptr_main_root, toAdd);
    m_count_elements++;
    changeSizeIfNeeded();
    return true;

}

template <class T>
bool hash_table<T>::remove_from_array(const T& objectToAdd, int key) {
    if (!find(key)) {
        return false;
    }
    object toRemove(&objectToAdd, key);
    int hash_key = hash(key);
    m_array[hash_key].remove_node(m_array[hash_key].ptr_main_root, toRemove);
    m_count_elements--;
    changeSizeIfNeeded();
    return true;

}

/*
template <class T>
std::ostream& operator<<(std::ostream &os, const hash_table<T>& hash)
{
    os << "size:" << hash.m_size << "current size: "<< hash.currentSize << std::endl;
    for(int i = 0; i < hash.m_size; i++)
        os << "arr[" << i << "]: " << hash.m_array[i];
    os << std::endl;
    return os;
}*/








#endif //RECORDSCOMPANY_HASH_TABLE_H