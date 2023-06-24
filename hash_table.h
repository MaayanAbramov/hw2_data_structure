//
// Created by maaya on 07/06/2023.
//

#ifndef RECORDSCOMPANY_HASH_TABLE_H
#define RECORDSCOMPANY_HASH_TABLE_H

using namespace std;
#include <iostream>
#include "AvlTree.h"
#include <cassert>

template <class T>
class hash_table{
public:
    class object {

        int m_key;
        T *m_object;

        friend class hash_table<T>;


    public:
        //----------------the big three---------------
        object(T* object, int key);  //we don't want the constructor to do implicit conversion between
        object() : m_key(-1), m_object(nullptr) {}
        // types
        ~object() = default;

        object(const object &other) = default;

        //----------------the big three---------------
        T *get_object() const;
        int get_key() const;


        //--------------------------operators------------
        object &operator=(const object &array_object2);
        bool operator==(const object& array_object2);
        bool operator<(const object& arr_obj2) const;
        bool operator>(const object& arr_obj2) const;

    };
    //remember this is the hash class

private:
    static const int default_Length = 16;


public:
    AvlTree<object>* m_array;
    /*-------------------- the big three ----------------*/
    explicit hash_table();
    ~hash_table();
    hash_table(const hash_table<T>& other) = delete;
    int m_size;
    int m_count_elements;


    /*--------------- process functions--------------------*/
    int hash(int key);

    T * find(int key);


    void assignObjectsToArray(typename AvlTree<object>::Node* node, object* arr, int* index);
    void changeSizeIfNeeded();


    bool insert_to_array(T* toAdd, int key);
    bool remove_from_array(const T& objectToRemove, int key);
};



template <class T>
hash_table<T>::object::object(T* object, int key) : m_key(key), m_object(object){}


template <class T>
T * hash_table<T>::object::get_object() const{
    return m_object;
}

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

    return *this;
}


template<class T>
bool hash_table<T>::object::operator==(const hash_table::object
                                       &array_object2) {
    bool OK1 = array_object2.m_key == this->m_key;
    return OK1;
}

template <class T>
bool hash_table<T>::object::operator<(const object& arr_obj2) const {
    int obj_key = arr_obj2.get_key();
    return this->m_key < obj_key;
}

template <class T>
bool hash_table<T>::object::operator>(const object& arr_obj2) const {
    int obj_key = arr_obj2.get_key();
    return this->m_key > obj_key;
}


/*-------------------------- hash table ---------------*/
template <class T>
hash_table<T>::hash_table(): m_size(default_Length), m_count_elements(0){
    this->m_array = new AvlTree<object>[m_size];
}


template <class T>
hash_table<T>::~hash_table() {
    delete[] m_array;
}

template <class T>
int hash_table<T>::hash(int key) {
    int hash_num = key % m_size;
    return hash_num;
}

template <class T>
T * hash_table<T>::find(int key)  {

    object toFind(nullptr, key);
    int index_in_array = hash(key);
    AvlTree<object>* current_tree = &m_array[index_in_array];

    bool is_exist = current_tree->is_key_exists(current_tree->ptr_main_root, toFind);
    if (!is_exist) {
        return nullptr;
    }
    else {
        auto toReturn = current_tree->find_pointer_node(current_tree->ptr_main_root, toFind);

        return toReturn->m_data.m_object;
    }
}

template <class T>
void hash_table<T>::assignObjectsToArray(typename AvlTree<object>::Node* node, object* arr, int* index) {
    if (node == nullptr) {
        return;
    }
    assignObjectsToArray(node->m_ptr_left, arr, index);
    arr[*index] = node->m_data;
    (*index)++;
    assignObjectsToArray(node->m_ptr_right, arr, index);
}

template <class T>
void hash_table<T>::changeSizeIfNeeded() {
    if (m_count_elements <= default_Length/2) {
        return;
    }
    if (m_count_elements >= m_size) { //not copied correct
        int backupToSize = m_size;
        m_size = m_size*2;
        auto updatedArray = new AvlTree<object>[m_size];
        for (int i = 0 ; i < backupToSize ; i++) {
            AvlTree<object>* tree_ob = &m_array[i];
            if (tree_ob->ptr_main_root != nullptr)  {

                int elems_in_tree_ob = tree_ob->m_num_elements;
                auto arr = new object[elems_in_tree_ob];
                int index = 0;
                assignObjectsToArray(tree_ob->ptr_main_root, arr, &index);

                for (int j = 0 ; j < elems_in_tree_ob ; j++) {

                    object* current_obj = &arr[j];
                    int current_key = (current_obj->get_key());
                    AvlTree<object>* current_tree = &updatedArray[hash(current_key)];
                    current_tree->ptr_main_root = current_tree->insert(current_tree->ptr_main_root, *current_obj);
                }
                delete[] arr;
            }
        }

        delete[] m_array;
        m_array = updatedArray;
    }
}


template <class T>
bool hash_table<T>::insert_to_array(T* objectToAdd, int key) {
    object toAdd(objectToAdd, key);
    int hash_key = hash(key);
    AvlTree<object>* current_tree = &m_array[hash_key];
    if (find(key) != nullptr) { // means the key is already in the tree
        return false;
    }
    current_tree->ptr_main_root = current_tree->insert(current_tree->ptr_main_root, toAdd);
    m_count_elements++;
    changeSizeIfNeeded();
    return true;

}

template <class T>
bool hash_table<T>::remove_from_array(const T& objectToRemove, int key) {
    if (find(key) == nullptr) { //means the key already does not exist in the tree
        return false;
    }
    object toRemove(&objectToRemove, key);
    int hash_key = hash(key);
    AvlTree<object>* current_tree = &m_array[hash_key];
    current_tree->remove_node(current_tree->ptr_main_root, toRemove);
    m_count_elements--;
    changeSizeIfNeeded();
    return true;

}

#endif //RECORDSCOMPANY_HASH_TABLE_H
