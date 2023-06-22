//
// Created by maaya on 16/06/2023.
//

#include "UnionFind.h"

/*------------the implementation of union find class------------*/
Union_Find::~Union_Find() {

    if (m_elements)
        delete[] m_elements;
    if(m_groups)
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
int Union_Find::recursive_height_sum(Node* curr_node) const {
    if (curr_node == nullptr) {
        return 0;
    }
    int recursive_out = recursive_height_sum(curr_node->get_father());
    int my_height = curr_node->get_global_height();
    int sum = recursive_out + my_height;
    return   sum;
}

int Union_Find::get_height(int r_id) const {
    int height = 0;
    Node* element = &m_elements[r_id];

    return recursive_height_sum(element);


}
void Union_Find::shrink_the_tree_path(Union_Find::Node* curr_node, Union_Find::Node* root,int* acumulated_sum_height,
                                      int* balance_factor) {
    if (curr_node == nullptr) {
        return;
    }
    int old = curr_node->global_height;
    curr_node->global_height = *acumulated_sum_height - *balance_factor;
    *balance_factor += old;
    Node* father = curr_node->m_father;
    curr_node->m_father = root;
    shrink_the_tree_path(father, root, acumulated_sum_height, balance_factor);

}
/*
Union_Find::GroupOfNodes * Union_Find::find_group(int r_id) {

    Node* ptr_to_record_node = &m_elements[r_id];
    int acumulated_sum = recursive_height_sum(ptr_to_record_node);


    //like the boxes question from the turtorial
    Node* root = Node::find_root(ptr_to_record_node);
    GroupOfNodes* group_of_node = root->m_group;
    int balance_factor = 0;
    shrink_the_tree_path(ptr_to_record_node, root, &acumulated_sum, &balance_factor);

    return group_of_node;
}*/

Union_Find::GroupOfNodes* Union_Find::find_group(int recordID) {
    Node* currElement = &m_elements[recordID];
    int relativeSum = 0;
    while(currElement->get_father() != nullptr){
        relativeSum += currElement->global_height;
        currElement = currElement->m_father;
    }
    GroupOfNodes* group = currElement->m_group;


    int toSubtract = 0;
    Node* root = currElement;
    currElement = &m_elements[recordID];
    while(currElement->m_father != nullptr ){
        int oldRelativeHeight = currElement->global_height;
        currElement->set_global_height(relativeSum - toSubtract);
        toSubtract += oldRelativeHeight;
        Node* nextElement = currElement->m_father;
        currElement->m_father = root;
        currElement = nextElement;
    }
    return group;

}

//group_1_up contains more elements

Union_Find::GroupOfNodes* Union_Find::Union(GroupOfNodes* groupUp,GroupOfNodes* groupUnder){
    if(groupUp->m_num_of_members > groupUnder->m_num_of_members){
        Node* groupUpRoot = groupUp->m_root;
        Node* groupUnderRoot = groupUnder->m_root;
        groupUpRoot->global_height = groupUpRoot->global_height + groupUnder->m_height;
        groupUnderRoot->global_height= groupUnderRoot->global_height - groupUpRoot->global_height;

        groupUp->m_height = groupUp->m_height + groupUnder->m_height;
        groupUp->m_column = groupUnder->m_column;
        groupUp->m_num_of_members = groupUp->m_num_of_members + groupUnder->m_num_of_members;

        groupUnderRoot->m_group = nullptr;//
        groupUnder->m_root = nullptr;//
        groupUnderRoot->m_father = groupUpRoot;
        return groupUp;
    }
    else{
        Node* groupUpRoot = groupUp->m_root;
        Node* groupUnderRoot = groupUnder->m_root;
        groupUpRoot->global_height = groupUpRoot->global_height + groupUnder->m_height -groupUnderRoot->global_height;

        groupUnder->m_height = groupUp->m_height + groupUnder->m_height;
        groupUnder->m_num_of_members = groupUp->m_num_of_members + groupUnder->m_num_of_members;

        groupUpRoot->m_group = nullptr;
        groupUp->m_root = nullptr;
        groupUpRoot->m_father = groupUnderRoot   ; //
        return groupUnder;
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
        //check if it should be zero instead
        updated_group_array[i].m_height = updated_node_array[i].m_record->get_num_of_copies();
        //the bottom is the record hiself
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
/*Union_Find::Node* Union_Find::Node::get_son() const {
    return m_son;
}
void Union_Find::Node::set_son(Node* s) {
    m_son = s;
}*/

void Union_Find::Node::set_father(Node* father) {
    m_father = father;
}
Union_Find::Node* Union_Find::Node::get_father() const {
    return m_father;
}

Union_Find::Node* Union_Find::Node::find_root(Node *node) {
    assert(node != nullptr);
    Node* temp = node;
    while (temp->m_father)
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


