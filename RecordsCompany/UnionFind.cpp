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


// getters and setters
Record* Union_Find::get_record_from_array(int r_id) const {
    return m_elements[r_id].get_record();
}

int Union_Find::get_size() const {
    return m_size;
}

int Union_Find::get_height(int r_id) const {
    Node* node = &m_elements[r_id];
    return recursive_height_sum(node);
}


// aux func
int Union_Find::recursive_height_sum(Node* curr_node) const {
    if (curr_node == nullptr) {
        return 0;
    }
    return curr_node->get_global_height() + recursive_height_sum(curr_node->get_father());
}


void Union_Find::shrink_the_tree_path(Union_Find::Node* curr_node, Union_Find::Node* root,int acumulated_sum_height,
                                      int balance_factor) {
    if (curr_node->m_father == nullptr) {
        return;
    }
    int old = curr_node->global_height;
    curr_node->global_height = acumulated_sum_height - balance_factor;
    balance_factor += old;
    Node* father = curr_node->m_father;
    curr_node->m_father = root;
    shrink_the_tree_path(father, root, acumulated_sum_height, balance_factor);
}

Union_Find::GroupOfNodes * Union_Find::find_group(int r_id) {

    Node* ptr_to_record_node = &m_elements[r_id];
    int acumulated_sum = recursive_height_sum(ptr_to_record_node);


    //like the boxes question from the turtorial
    Node* root = Node::find_root(ptr_to_record_node);
    GroupOfNodes* group_of_node = root->m_group;
    int balance_factor = 0;
    shrink_the_tree_path(ptr_to_record_node, root, acumulated_sum, balance_factor);

    return group_of_node;
}

//group_1_up contains more elements
Union_Find::GroupOfNodes* Union_Find::Union(GroupOfNodes* group_1_up, GroupOfNodes* group_2_down) {
    if (group_1_up->m_num_of_members <= group_2_down->m_num_of_members){
        group_1_up->m_root->global_height += group_2_down->m_height - group_2_down->m_root->global_height;
        group_2_down->m_num_of_members += group_1_up->m_num_of_members;
        group_2_down->m_height += group_1_up->m_height;


        group_1_up->m_root->m_group = nullptr;
        //because the group is not counted anymore

        group_1_up->m_root->m_father = group_2_down->m_root;
        group_1_up->m_root = nullptr;
        return group_2_down;

    }
    else{
        group_1_up->m_column = group_2_down->m_column; //the bottom updating
        group_1_up->m_height = group_1_up->m_height + group_2_down->m_height;

        group_1_up->m_num_of_members = group_1_up->m_num_of_members + group_2_down->m_num_of_members;
        group_1_up->m_root->global_height = group_1_up->m_root->global_height + group_2_down->m_root->global_height;

        group_2_down->m_root->global_height = group_2_down->m_root->global_height - group_1_up->m_root->global_height;


        group_2_down->m_root->m_group = nullptr;//

        //because the group is not counted anymore
        group_2_down->m_root->m_father = group_1_up->m_root; //
        group_2_down->set_root(nullptr);//

        return group_1_up;


    }
}

void Union_Find::newMonth(int* records_stock, int number_of_records)  {
    if(number_of_records == 0){
        delete[] m_elements;
        delete[] m_groups;

        m_elements = nullptr;
        m_groups = nullptr;
        m_size = number_of_records;
        return;
    }

    Node* tempElements = new Node[number_of_records];
    GroupOfNodes* tempGroups;

    try {
        tempGroups = new GroupOfNodes[number_of_records];
    } catch(std::bad_alloc& e) {
        delete[] tempElements;
        throw;
    }

    int initalized = 0;
    try{
        for(int i = 0; i < number_of_records; ++i){
            tempElements[i].m_record = new Record(i,records_stock[i], 0);
            ++initalized;
        }

        for(int i = 0; i < number_of_records; ++i){
            tempGroups[i].m_root = &tempElements[i];
            tempGroups[i].m_height = (tempElements[i].m_record->get_num_of_copies());
            tempGroups[i].m_column = (tempElements[i].m_record->get_r_id());
            tempGroups[i].m_num_of_members = 1;
            tempElements[i].m_group = &tempGroups[i];
        }
        delete[] m_elements;
        delete[] m_groups;

        m_elements = tempElements;
        m_groups = tempGroups;
        m_size = number_of_records;

    } catch(std::bad_alloc& e) {
        for(int i = 0; i < initalized; ++i){
            delete tempElements[i].m_record;
        }
        delete[] tempElements;
        delete[] tempGroups;
    }
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


// getters and setters
Record* Union_Find::Node::get_record() const {
    return m_record;
}

Union_Find::GroupOfNodes* Union_Find::Node::get_group() const {
    return m_group;
}

Union_Find::Node* Union_Find::Node::get_father() const {
    return m_father;
}

int Union_Find::Node::get_global_height() const {
    return global_height;
}

void Union_Find::Node::set_record(Record* r) {
    m_record = r;
}

void Union_Find::Node::set_group(GroupOfNodes* g) {
    m_group = g;
}

void Union_Find::Node::set_father(Node* father) {
    m_father = father;
}

void Union_Find::Node::set_global_height(int num) {
    global_height = num;
}

/*Union_Find::Node* Union_Find::Node::get_son() const {
    return m_son;
}
void Union_Find::Node::set_son(Node* s) {
    m_son = s;
}*/



Union_Find::Node* Union_Find::Node::find_root(Node *node) {
    // if there is no nodes
    if (node == nullptr) {
        return nullptr;
    }

    Node* temp = node;
    while (temp->m_father)
    {
        temp = temp->m_father;
    }
    return temp;
}


/*--------------------the implementation of the group of nodes class---------------*/



/*------------------the implementation of the groups of nodes class--------*/
Union_Find::GroupOfNodes::GroupOfNodes(): m_num_of_members(1), m_height(0), m_column(-1), m_root(nullptr) {}


// getters and setters
int Union_Find::GroupOfNodes::get_num_of_members() const {
    return m_num_of_members;
}
int Union_Find::GroupOfNodes::get_height() const {
    return m_height;
}
int Union_Find::GroupOfNodes::get_column() const {
    return m_column;
}
Union_Find::Node* Union_Find::GroupOfNodes::get_root() const {
    return m_root;
}

void Union_Find::GroupOfNodes::set_num_of_members(int num_elements) {
    m_num_of_members = num_elements;
}
void Union_Find::GroupOfNodes::set_height(int num) {
    m_height = num;
}
void Union_Find::GroupOfNodes::set_column(int column) {
    m_column = column;
}
void Union_Find::GroupOfNodes::set_root(Node* root) {
    m_root = root;
}
