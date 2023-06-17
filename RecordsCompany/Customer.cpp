//
// Created by maaya on 04/06/2023.
//

#include "Customer.h"

// getters and setters

int Customer::get_id() const{
    return m_c_id;
}
int Customer::get_phone() const{
    return m_phone_num;
}
bool Customer::get_is_member() const{
    return m_is_member;
}
int Customer::get_expenses() const {
    return m_expenses;
}

void Customer::set_id(int id){
    m_c_id = id;
}
void Customer::set_phone(int phone) {
    m_phone_num = phone;
}
void Customer::set_is_member(bool is_member) {
    m_is_member= is_member;
}
void Customer::set_expenses(int expenses) {
    m_expenses = expenses;
}


// operator overloading

bool operator==(const Customer& Customer1, const Customer& Customer2) {
    return Customer1.m_c_id == Customer2.m_c_id;
}

bool operator<(const Customer& Customer1, const Customer& Customer2) {
    return Customer1.m_c_id < Customer2.m_c_id;
}

bool operator>(const Customer& Customer1, const Customer& Customer2) {
    return Customer1.m_c_id > Customer2.m_c_id;
}

Customer& Customer::operator=(const Customer& Customer){
    if (this == &Customer) {
        return *this;
    }

    m_c_id = Customer.get_id();
    m_phone_num = Customer.get_phone();
    m_is_member = Customer.get_is_member();
    m_expenses = Customer.get_expenses();

    return *this;
}

std::ostream& operator<<(std::ostream& os, const Customer& u) {
    os << u.m_c_id;
    return os;
}