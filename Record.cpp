//
// Created by maaya on 04/06/2023.
//

#include "Record.h"

// getters and setters
int Record::get_r_id() const {
    return m_r_id;
}
int Record::get_num_of_copies() const {
    return m_num_of_copies;
}
int Record::get_num_of_sales() const {
    return m_num_of_sales;
}

void Record::set_num_of_copies(int num_copies) {
    m_num_of_copies = num_copies;
}
void Record::set_num_of_sales(int num_sales) {
    m_num_of_sales = num_sales;
}


// aux func

void Record::inc_num_of_sales() {
    m_num_of_sales++;
}