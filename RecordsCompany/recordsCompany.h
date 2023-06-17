#ifndef RECORDS_COMPANY_H
#define RECORDS_COMPANY_H

#include "utilesWet2.h"

#include "Record.h"
#include "RankTree.h"
#include "Customer.h"
#include "hash_table.h"
#include "UnionFind.h"

#include <iostream>
class Customer;
class customer_getter : public Getter<Customer *>{
public:
    int operator()(Customer *t) override;


};


class RecordsCompany {
private:
    RankTree<Customer*> m_vip_costumers; // ranked tree for saving prizes
    hash_table<Customer> m_all_costumers;
    Union_Find m_records_stock;

public:
    RecordsCompany() : m_vip_costumers(new customer_getter()), m_all_costumers(), m_records_stock() {}

    ~RecordsCompany() = default;

    StatusType newMonth(int *records_stocks, int number_of_records);

    StatusType addCustomer(int c_id, int phone);

    Output_t<int> getPhone(int c_id);

    StatusType makeMember(int c_id);

    Output_t<bool> isMember(int c_id);

    StatusType buyRecord(int c_id, int r_id);

    StatusType addPrize(int c_id1, int c_id2, double  amount);

    Output_t<double> getExpenses(int c_id);

    StatusType putOnTop(int r_id1, int r_id2);

    StatusType getPlace(int r_id, int *column, int *hight);
};

#endif