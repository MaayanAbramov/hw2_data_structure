//
// Created by maaya on 04/06/2023.
//

#ifndef RECORDSCOMPANY_RECORD_H
#define RECORDSCOMPANY_RECORD_H


class Record {
    int m_r_id;
    int m_num_of_copies;
    int m_num_of_sells;
public:
    Record(int r_id, int copies, int num_sells) : m_r_id(r_id), m_num_of_copies(copies), m_num_of_sells(num_sells){}
    ~Record() = default;
    Record(const Record& other) = default;
};


#endif //RECORDSCOMPANY_RECORD_H
