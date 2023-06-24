//
// Created by maaya on 16/06/2023.
//

#include "UnionFind.h"

/*------------the implementation of union find class------------*/
Union_Find::~Union_Find() {
    delete[] m_elements;
    delete[] m_groups;

    m_size = 0;
    m_elements = nullptr;
    m_groups = nullptr;
}

Record* Union_Find::get_record_from_array(int r_id) const {
    return m_elements[r_id].get_record();
}
int Union_Find::get_size() const {
    return m_size;
}
int Union_Find::recursive_height_sum(Node* curr_node, Node* root) const {
    if (curr_node == root) {
        return root->global_height;
    }
    return curr_node->global_height + recursive_height_sum(curr_node->m_father, root);
}

int Union_Find::get_height(int r_id) const {

    Node* element = &m_elements[r_id];
    Node* root = Node::find_root(element);

    return recursive_height_sum(element, root);


}
void Union_Find::shrink_the_tree_path(Union_Find::Node* curr_node, Union_Find::Node* root,int* acumulated_sum_height,
                                      int* balance_factor) {
    if (curr_node== root) {
        return;
    }
    int old = curr_node->global_height;
    curr_node->global_height = *acumulated_sum_height - *balance_factor;
    *balance_factor += old;
    Node* next = curr_node->m_father;
    curr_node->m_father = root;
    shrink_the_tree_path(next, root, acumulated_sum_height, balance_factor);

}

Union_Find::GroupOfNodes* Union_Find::find_group(int r_id) {
    Node* ptr_to_record_node = &m_elements[r_id];
    Node* root = Node::find_root(ptr_to_record_node);
    int acumulated_sum = recursive_height_sum(ptr_to_record_node, root);
    acumulated_sum-= root->global_height;

    //like the boxes question from the turtorial
    int balance_factor = 0;
    if (ptr_to_record_node->m_father != nullptr) {
        shrink_the_tree_path(ptr_to_record_node, root, &acumulated_sum, &balance_factor);
    }

    GroupOfNodes* group_of_node = root->m_group;
    return group_of_node;
}


Union_Find::GroupOfNodes* Union_Find::Union(GroupOfNodes* group1, GroupOfNodes* group2) {
    //group_2 contains more elements
    if (group1->m_num_of_members < group2->m_num_of_members) {
        auto group1_m_ptr_root = group1->m_root;
        auto group2_m_ptr_root = group2->m_root;

        int temp1 = group2->m_height - group2_m_ptr_root->global_height;
        group1_m_ptr_root->global_height = group1_m_ptr_root->global_height + temp1;

        group2->m_height = group1->m_height + group2->m_height;
        group2->m_num_of_members = group1->m_num_of_members + group2->m_num_of_members;

        group1_m_ptr_root->m_father = group2_m_ptr_root;
        group1_m_ptr_root->m_group = nullptr;
        group1->m_root = nullptr;

        return group2;
    }

    //group_1 contains more elements
    else {
        auto group1_m_ptr_root = group1->m_root;
        auto group2_m_ptr_root = group2->m_root;

        group1_m_ptr_root->global_height = group1_m_ptr_root->global_height + group2->m_height;
        group2_m_ptr_root->global_height = group2_m_ptr_root->global_height - group1_m_ptr_root->global_height;

        group1->m_column = group2->m_column;
        group1->m_height = group1->m_height + group2->m_height;
        group1->m_num_of_members = group1->m_num_of_members + group2->m_num_of_members;

        group2_m_ptr_root->m_father = group1_m_ptr_root;
        group2_m_ptr_root->m_group = nullptr;
        group2->m_root = nullptr;

        return group1;
    }
}

void Union_Find::newMonth(int* records_stock, int num_of_records)  {
    if (num_of_records == 0) {
        this->~Union_Find();
        return;
    }
    Node* updated_node_array = nullptr;
    try {
        updated_node_array = new Node[num_of_records];
    } catch(std::bad_alloc& e) {
        delete[] updated_node_array;
        throw;
    }
    GroupOfNodes* updated_group_array = nullptr;
    try {
        updated_group_array = new GroupOfNodes[num_of_records];
    } catch (std::bad_alloc& e) {
        delete[] updated_group_array;
        throw;
    }

    //deleted all the old data
    this->~Union_Find();

    //now updating the data
    int actual_size=0;
    try {

        for (int i = 0; i < num_of_records ; i++) {
            updated_node_array[i].m_record = new Record(i, records_stock[i], 0);
            actual_size++;
        }
    } catch (std::bad_alloc& e) {
        for (int i = 0 ; i < actual_size ; i++) {
            delete updated_node_array[i].m_record;
        }
        delete[] updated_node_array;
        delete[] updated_group_array;
    }

    for (int i = 0 ; i < num_of_records ; i++) {
        updated_group_array[i].m_num_of_members = 1;
        //the height will be the amount of copies
        updated_group_array[i].m_height = updated_node_array[i].m_record->get_num_of_copies();
        //the bottom is the record himself
        updated_group_array[i].m_column = updated_node_array[i].m_record->get_r_id();
        updated_group_array[i].m_root = &updated_node_array[i];
        updated_node_array[i].m_group = &updated_group_array[i];

    }
    m_elements = updated_node_array;
    m_groups = updated_group_array;
    m_size = num_of_records;
}










/*----------------the implementation of the node class-----------------*/


Union_Find::Node::Node()  {
    resetNode();
    global_height = 0;
}

void Union_Find::Node::resetNode() {
    this->m_record = nullptr;
    this->m_father = nullptr;
    this->m_group = nullptr;
}
Union_Find::Node::~Node() {
    delete this->m_record;
    resetNode();
}

Record* Union_Find::Node::get_record() const {
    return m_record;
}
void Union_Find::Node::set_record(Record* r) {
    m_record = r;
}
Union_Find::GroupOfNodes* Union_Find::Node::get_group() const {
    return m_group;
}

void Union_Find::Node::set_group(GroupOfNodes* g) {
    m_group = g;
}

void Union_Find::Node::set_father(Node* father) {
    m_father = father;
}
Union_Find::Node* Union_Find::Node::get_father() const {
    return m_father;
}

Union_Find::Node* Union_Find::Node::find_root(Node *node) {
    if (node == nullptr) {
        return nullptr;
    }

    Node* temp = node;
    while (temp->m_father != nullptr)
    {
        temp = temp->m_father;
    }
    return temp;
}

int Union_Find::Node::get_global_height() const {
    return global_height;
}
void Union_Find::Node::set_global_height(int num) {
    global_height = num;
}

/*--------------------the implementation of the group of nodes class---------------*/


/*------------------the implementation of the groups of nodes class--------*/
Union_Find::GroupOfNodes::GroupOfNodes() : m_num_of_members(1), m_height(0), m_column(-1), m_root(nullptr){}
int Union_Find::GroupOfNodes::get_num_of_members() const {
    return m_num_of_members;
}

void Union_Find::GroupOfNodes::set_num_of_members(int num_elements) {
    m_num_of_members = num_elements;
}
int Union_Find::GroupOfNodes::get_height() const {
    return m_height;
}
void Union_Find::GroupOfNodes::set_height(int num) {
    m_height = num;
}


int Union_Find::GroupOfNodes::get_column() const {
    return m_column;
}
void Union_Find::GroupOfNodes::set_column(int column) {
    m_column = column;
}
Union_Find::Node* Union_Find::GroupOfNodes::get_root() const {
    return m_root;
}
void Union_Find::GroupOfNodes::set_root(Node* root) {
    m_root = root;
}
