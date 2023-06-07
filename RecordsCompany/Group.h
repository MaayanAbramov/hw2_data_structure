//
// Created by maaya on 06/06/2023.
//

#ifndef RECORDSCOMPANY_GROUP_H
#define RECORDSCOMPANY_GROUP_H

#include "AvlTree.h"
#include "Record.h"
#include "Costumer.h"

class Group {
    int m_id;
    AvlTree<Costumer *> m_tree_group;

public :
    Group(int id) : m_id(id), m_tree_group(AvlTree<Costumer*>()) {}
    AvlTree<Costumer *>& get_group_tree() {
        return m_tree_group;
    }

};


#endif //RECORDSCOMPANY_GROUP_H
