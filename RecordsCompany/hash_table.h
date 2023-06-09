//
// Created by maaya on 07/06/2023.
//

#ifndef RECORDSCOMPANY_HASH_TABLE_H
#define RECORDSCOMPANY_HASH_TABLE_H
using namespace std;
#include <iostream>
#include "AvlTree.h"


    template <class T>
    class hash_table{
    public:
        class array_object {
           //bool m_is_insertion_available;
            int m_key; //please notice that the keys are between 0 to the num_of_records
            T *m_object;
            //this is the root of tree This object founds

            friend class hash_table<T>;

        public:
             /*----------------the big three---------------*/
            explicit array_object(T *object, int key);  //we don't want the constructor to do implicit conversion between
            // types
            ~array_object() = default;

            array_object(const array_object &other) = delete;

            /*----------------the big three---------------*/


            T *get_object() const;

            void  set_object(T *object);

            //bool get_is_insertion_available() const;
        //there is no reason to create a setter function for this boolean field
        //the reason is that the function that responible for the size multipication will indicate this for us.

            int get_key() const;
        //no reason to create a setter function for this field


        /*--------------------------operators------------*/
            array_object &operator=(const array_object &array_object2);
            bool operator==(const array_object& array_object2);
            bool operator<(const array_object& arr_obj2) const;
            bool operator>(const array_object& arr_obj2) const;









        };
    //remember this is the hash class

    private:
        static const int default_Length = 16;
        int m_size; // this is the size of the array
        int m_count_elements;
        //AvlTree<array_object> m_array[default_Length]; //every field in the array will be tree
        array_object* m_array;

    public:
    /*-------------------- the big three ----------------*/
        explicit hash_table();
        ~hash_table();
        hash_table(const hash_table<T>& other) = delete;

    /*--------------- process functions--------------------*/
        int hash(int key);

        T* find(int key);

        void changeSizeIfNeeded();


        bool insert_to_array(const T& toAdd, int key);

        bool remove_from_array(const T& toRemove, int key);



        friend std::ostream& operator<<(std::ostream &os, const hash_table<T>& hash);





    };



template <class T>
hash_table<T>::array_object::array_object(T* object, int key) : m_key(key), m_object(object){}


template <class T>
T* hash_table<T>::array_object::get_object() const{
    return m_object;
}

template <class T>
void hash_table<T>::array_object::set_object(T *object) {
    m_object = object;
}

/*template <class T>
bool hash_table<T>::array_object::get_is_insertion_available() const {
    return m_is_insertion_available;
}*/

template <class T>
int hash_table<T>::array_object::get_key() const {
    return m_key;
}

template <class T>
typename hash_table<T>::array_object& hash_table<T>::array_object::operator=(const hash_table::array_object&
        array_object2) {
    if (this == &array_object2) {
        return *this;
    }
    m_object = array_object2.get_object();
    m_key = array_object2.get_key();
    //m_is_insertion_available = array_object2.get_is_insertion_available();

    return *this;
}


template<class T>
bool hash_table<T>::array_object::operator==(const hash_table::array_object
&array_object2) {
    return array_object2.m_key == this->m_key;
}

template <class T>
bool hash_table<T>::array_object::operator<(const array_object& arr_obj2) const {
    return this->m_key < arr_obj2.get_key();
}

template <class T>
bool hash_table<T>::array_object::operator>(const array_object& arr_obj2) const {
    return this->m_key < arr_obj2.get_key();
}

/*-------------------------- hash table ---------------*/
template <class T>
hash_table<T>::hash_table()   {
    m_size = default_Length;
    m_count_elements = 0;
    this->m_array = new AvlTree<array_object>[m_size];

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
T* hash_table<T>::find(int key) {
    int index_in_array = hash(key);
    array_object toFind(nullptr, key);
    bool is_exist = m_array[index_in_array].is_key_exists(m_array[index_in_array].ptr_main_root, toFind);
    if (!is_exist) {
        return nullptr;
    }
    else {
        auto toReturn = m_array[index_in_array].find_pointer(m_array[index_in_array].ptr_main_root, toFind);
        return toReturn;
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
        AvlTree<array_object> updatedArray[m_size];
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
        AvlTree<array_object> updatedArray[m_size];
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
    array_object toAdd(&objectToAdd, key);
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
    array_object toRemove(&objectToAdd, key);
    int hash_key = hash(key);
    m_array[hash_key].remove_node(m_array[hash_key].ptr_main_root, toRemove);
    m_count_elements--;
    changeSizeIfNeeded();
    return true;

}

template <class T>
std::ostream& operator<<(std::ostream &os, const hash_table<T>& hash)
{
    os << "size:" << hash.m_size << "current size: "<< hash.currentSize << std::endl;
    for(int i = 0; i < hash.m_size; i++)
        os << "arr[" << i << "]: " << hash.m_array[i];
    os << std::endl;
    return os;
}








#endif //RECORDSCOMPANY_HASH_TABLE_H
