//
// Created by maaya on 04/06/2023.
//

#ifndef RECORDSCOMPANY_RECORD_H
#define RECORDSCOMPANY_RECORD_H


class Record {
    int m_r_id;
    int m_num_of_copies;
    int m_num_of_sales;

public:
    Record(int r_id, int copies, int num_sales) : m_r_id(r_id), m_num_of_copies(copies), m_num_of_sales(num_sales){}
    ~Record() = default;
    Record(const Record& other) = default;

    // getters and setters
    int get_r_id() const;
    int get_num_of_copies() const;
    int get_num_of_sales() const;

    void set_num_of_copies(int num_copies);
    void set_num_of_sales(int num_sales);

    // aux func

    void inc_num_of_sales();
};


#endif //RECORDSCOMPANY_RECORD_H