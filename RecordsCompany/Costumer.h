//
// Created by maaya on 04/06/2023.
//

#ifndef RECORDSCOMPANY_COSTUMER_H
#define RECORDSCOMPANY_COSTUMER_H
//#include "recordsCompany.h"
#include <iostream>
using namespace std;

class Costumer {
    int m_c_id;
    int m_phone_num;
    bool is_member;
    int m_expenses;


public:
    Costumer(int id, int phone, bool member) : m_c_id(id), m_phone_num(phone), is_member(member), m_expenses(0) {}
    ~Costumer() = default;
    Costumer(const Costumer& other) = default;
    Costumer& operator=(const Costumer& Costumer);

    int get_id() const;
    void set_id(int id);
    void set_phone(int phone);
    void set_is_member(bool IsMember);

    int get_phone() const;
    bool get_is_member() const;

    friend bool operator==(const Costumer& Costumer1, const Costumer& Costumer2);
    friend bool operator<(const Costumer& Costumer1, const Costumer& Costumer2);
    friend bool operator>(const Costumer& Costumer1, const Costumer& Costumer2);
    friend std::ostream& operator<<(std::ostream& os, const Costumer& u);


};


#endif //RECORDSCOMPANY_COSTUMER_H
