//
// Created by maaya on 04/06/2023.
//

#include "recordsCompany.h"

RecordsCompany::RecordsCompany() {
    this->m_vip_costumers = AvlTree<Costumer>();
    m_all_costumers();
    m_records_stock = nullptr;

}

StatusType RecordsCompany::newMonth(int *records_stocks, int number_of_records) {
    //לרוץ על כל הhash ולרוץ על כל העץ ולעדכן להם את שדה ההוצאות לאפס
    for (int i = 0 ; i < number_of_records ; i++) {

    }

}