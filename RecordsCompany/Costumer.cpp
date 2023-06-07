//
// Created by maaya on 04/06/2023.
//



#include "Costumer.h"

int Costumer::get_id() const{
    return m_c_id;
}
void Costumer::set_id(int id){
    m_c_id = id;
}

void Costumer::set_phone(int phone) {
    m_phone_num = phone;
}
void Costumer::set_is_member(bool IsMember) {
    is_member= IsMember;
}
int Costumer::get_phone() const{
    return m_phone_num;
}
bool Costumer::get_is_member() const{
    return is_member;
}

bool operator==(const Costumer& Costumer1, const Costumer& Costumer2) {
    return Costumer1.m_c_id == Costumer2.m_c_id;
}

bool operator<(const Costumer& Costumer1, const Costumer& Costumer2) {
    return Costumer1.m_c_id < Costumer2.m_c_id;
}

bool operator>(const Costumer& Costumer1, const Costumer& Costumer2) {
    return Costumer1.m_c_id > Costumer2.m_c_id;
}

Costumer& Costumer::operator=(const Costumer& Costumer){
    if (this == &Costumer) {
        return *this;
    }

    m_c_id = Costumer.get_id();
    m_phone_num = Costumer.get_phone();
    is_member = Costumer.get_is_member();

    return *this;
}

std::ostream& operator<<(std::ostream& os, const Costumer& u) {
    os << u.m_c_id;
    return os;
}
