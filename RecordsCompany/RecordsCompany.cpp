//
// Created by maaya on 04/06/2023.
//

#include "RecordsCompany.h"

/*
RecordsCompany::RecordsCompany() {
    //m_vip_costumers = RankTree<Customer*>();
    //m_all_costumers = hash_table<Customer>();
    //m_records_stock = Union_Find();
}*/


StatusType RecordsCompany::newMonth(int *records_stocks, int number_of_records) {
    try {
        if (number_of_records < 0) {
            return StatusType::INVALID_INPUT;
        }

        m_records_stock.newMonth(records_stocks, number_of_records);
        if (m_vip_costumers.ptr_main_root != nullptr ) {
            // finds the leftmost node of the rank tree & updates the whole tree of members
            auto curr_node = m_vip_costumers.distant_son(m_vip_costumers.ptr_main_root);
            while (m_vip_costumers.find_next_inorder(m_vip_costumers.ptr_main_root, curr_node) != nullptr) {
                auto next_node = m_vip_costumers.find_next_inorder(m_vip_costumers.ptr_main_root, curr_node);
                curr_node->m_data->set_expenses(0);
                curr_node = next_node;
            }
            if (curr_node != nullptr) {
                curr_node->m_data->set_expenses(0);
            }
        }


    }
    catch (std::bad_alloc& ba) {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}


StatusType RecordsCompany::addCostumer(int c_id, int phone) {
    try {
        if (c_id < 0 || phone < 0) {
            return StatusType::INVALID_INPUT;
        }

        auto curr_customer = m_all_costumers.find(c_id);

        // checks if the customer already exists
        if (curr_customer != nullptr) {
            return StatusType::ALREADY_EXISTS;
        }

        // adds a new customer to a hash_table of all customers
        auto customerToAdd = new Customer(c_id, phone, false);
        m_all_costumers.insert_to_array(customerToAdd, c_id);
    }
    catch (std::bad_alloc& ba) {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}


Output_t<int> RecordsCompany::getPhone(int c_id) {
    if (c_id < 0) {
        return StatusType::INVALID_INPUT;
    }

    auto curr_customer = m_all_costumers.find(c_id);

    // checks if the customer doesn't exist
    if (curr_customer == nullptr) {
        return StatusType::DOESNT_EXISTS;
    }

    return curr_customer->get_phone();
}


StatusType RecordsCompany::makeMember(int c_id) {
    try {
        if (c_id < 0) {
            return StatusType::INVALID_INPUT;
        }

        auto curr_customer = m_all_costumers.find(c_id);


        // checks if the customer doesn't exist
        if (curr_customer == nullptr) {
            return StatusType::DOESNT_EXISTS;
        }

        // checks if the customer is already in the group
        if (curr_customer->get_is_member()) {
            return StatusType::ALREADY_EXISTS;
        }

        curr_customer->set_is_member(true);
        bool helper1 = false;
        bool helper2 = false;
        m_vip_costumers.insert(m_vip_costumers.ptr_main_root, curr_customer, &helper1, &helper2);
    }
    catch (std::bad_alloc& ba) {
        Customer* curr_customer = m_all_costumers.find(c_id);

        if (curr_customer != nullptr) {
            curr_customer->set_is_member(false);
        }

        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}


Output_t<bool> RecordsCompany::isMember(int c_id) {
    if (c_id < 0) {
        return StatusType::INVALID_INPUT;
    }

    Customer* curr_customer = m_all_costumers.find(c_id);

    // checks if the customer doesn't exist
    if (curr_customer == nullptr) {
        return StatusType::DOESNT_EXISTS;
    }

    return curr_customer->get_is_member();
}


StatusType RecordsCompany::buyRecord(int c_id, int r_id) {
    if (c_id < 0 || r_id < 0) {
        return StatusType::INVALID_INPUT;
    }

    Customer* curr_customer = m_all_costumers.find(c_id);

    // checks if the customer or the record doesn't exist
    if (curr_customer == nullptr || r_id >= m_records_stock.get_size()) {
        return StatusType::DOESNT_EXISTS;
    }

    // updates the expenses of the customer (if he is a member)
    if (curr_customer->get_is_member()) {
        int curr_expenses = curr_customer->get_expenses();
        int num_of_sales = m_records_stock.get_record_from_array(r_id)->get_num_of_sales();
        curr_customer->set_expenses(curr_expenses + (100 + num_of_sales));
    }

    // increments the num of sales of the record
    m_records_stock.get_record_from_array(r_id)->inc_num_of_sales();

    return StatusType::SUCCESS;
}


StatusType RecordsCompany::addPrize(int c_id1, int c_id2, double  amount) {
    if (c_id1 < 0 || c_id2 < 0 || amount <= 0) {
        return StatusType::INVALID_INPUT;
    }
    RankTree<Customer *>::Node * temp = nullptr;
    auto upper_bound = m_vip_costumers.find_closest_max(m_vip_costumers.ptr_main_root, c_id2,temp);
    temp = nullptr;
    auto lower_bound = m_vip_costumers.find_closest_max(m_vip_costumers.ptr_main_root, c_id1, temp);

    //auto lower_bound = m_vip_costumers.find_closest_min(m_vip_costumers.ptr_main_root, c_id1, 2147483647); // was
    // c_id1 - 1
    if (upper_bound == nullptr && lower_bound == nullptr) {
        return StatusType::SUCCESS;
    }
     //update here
    m_vip_costumers.add_amount(m_vip_costumers.ptr_main_root, false, upper_bound->m_data->get_id(), amount);
    m_vip_costumers.add_amount(m_vip_costumers.ptr_main_root, false, lower_bound->m_data->get_id(), -amount); // was
    // -amount

    return StatusType::SUCCESS;
}


Output_t<double> RecordsCompany::getExpenses(int c_id) {
    if (c_id < 0) {
        return StatusType::INVALID_INPUT;
    }

    Customer* curr_customer = m_all_costumers.find(c_id);

    // checks if the customer doesn't exist or if he is not a member
    if (curr_customer == nullptr) {
        return StatusType::DOESNT_EXISTS;
    }

    if (!curr_customer->get_is_member()) {
        return 0;
    }
    else {
        auto ptr_node_customer = m_vip_costumers.find_pointer_node(m_vip_costumers.ptr_main_root,curr_customer);
        double prize = m_vip_costumers.acumulated_sum(ptr_node_customer);
        double expenses = curr_customer->get_expenses();
        return expenses-prize;
    }



}


StatusType RecordsCompany::putOnTop(int r_id1, int r_id2) {
    if (r_id1 < 0 || r_id2 < 0) {
        return StatusType::INVALID_INPUT;
    }

    if (r_id1 >= m_records_stock.get_size() || r_id2 >= m_records_stock.get_size()) {
        return StatusType::DOESNT_EXISTS;
    }

    // check if one of them is already on top of the other
    auto group1 = m_records_stock.find_group(r_id1);
    auto group2 = m_records_stock.find_group(r_id2);

    if (group1 == group2) {
        //if the records already one on the other
        return StatusType::FAILURE;
    }
    else {
        m_records_stock.Union(group1, group2);

        return StatusType::SUCCESS;
    }

}


StatusType RecordsCompany::getPlace(int r_id, int *column, int *hight) {
    if (r_id < 0 || column == nullptr || hight == nullptr) {
        return StatusType::INVALID_INPUT;
    }

    if (r_id >= m_records_stock.get_size()) {
        return StatusType::DOESNT_EXISTS;
    }

    auto ptr_to_group = m_records_stock.find_group(r_id);
    *column = ptr_to_group->m_column;
    *hight = m_records_stock.get_height(r_id);

    return StatusType::SUCCESS;
}

int customer_getter::operator()(Customer *t) {
    if (t == nullptr) {
        return -1;
    }
    return t->get_id();
}