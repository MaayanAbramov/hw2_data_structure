//
// Created by maaya on 04/06/2023.
//

#ifndef RECORDSCOMPANY_COSTUMER_H
#define RECORDSCOMPANY_COSTUMER_H

//#include "recordsCompany.h"
#include <iostream>
using namespace std;

class Customer {
    int m_c_id;
    int m_phone_num;
    bool m_is_member;
    int m_expenses;

public:
    Customer(int id, int phone, bool member) : m_c_id(id), m_phone_num(phone), m_is_member(member), m_expenses(0) {}
    ~Customer() = default;
    Customer(const Customer& other) = default;
    Customer& operator=(const Customer& Customer);

    // getters and setters
    int get_id() const;
    int get_phone() const;
    bool get_is_member() const;
    int get_expenses() const;

    void set_id(int id);
    void set_phone(int phone);
    void set_is_member(bool is_member);
    void set_expenses(int expenses);

    // operator overloading

    friend bool operator==(const Customer& Customer1, const Customer& Customer2);
    friend bool operator<(const Customer& Customer1, const Customer& Customer2);
    friend bool operator>(const Customer& Customer1, const Customer& Customer2);
    friend std::ostream& operator<<(std::ostream& os, const Customer& u);
};


#endif //RECORDSCOMPANY_COSTUMER_H
