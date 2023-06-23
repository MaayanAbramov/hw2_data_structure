
#include <cstdio>
#include <stdexcept>
#include "cassert"
#include "Record.h"

#ifndef UNION_FIND_H
#define UNION_FIND_H




class Union_Find
{
public:
    class Node;
    class GroupOfNodes;

    Node* m_elements; //array of Nodes
    GroupOfNodes* m_groups;//array of groups
    int m_size = 0;
    Node* find_root_of_heap_aux(int item);

public:
    /*---------------the big three---------*/
    explicit Union_Find() : m_elements(nullptr), m_groups(nullptr), m_size(0){}
    ~Union_Find();
    Union_Find& operator=(const Union_Find& other) = delete;
    Union_Find(const Union_Find& other) = delete;
    /*--------------getters and setters-------*/
    Record* get_record_from_array(int r_id) const;
    int get_size() const;
    int recursive_height_sum(Node* , Node*) const;
    int get_height(int r_id) const;
    /*----------------process functions------*/
    void newMonth(int* records_stock, int num_of_records);
    Record* find_root_of_heap(int item);
    //this function also shrunken
    GroupOfNodes * find_group(int r_id);
    GroupOfNodes* Union(GroupOfNodes* group_1_up, GroupOfNodes* group_2_down);
    void shrink_the_tree_path(Node* curr_node, Node* root,int* acumulated_sum_height, int* balance_factor);





public:

    class GroupOfNodes {
    public:
        int m_num_of_members; //number of elements
        int m_height;
        int m_column; //who is at the bottom
        Node* m_root;

        friend class Union_Find;
    public:
        /*---------- the big three--------*/
        GroupOfNodes();
        GroupOfNodes(const GroupOfNodes& other) = delete;
        GroupOfNodes& operator=(const GroupOfNodes& group2) = delete;

        /*------------getters and setters---------*/
        int get_num_of_members() const;
        void set_num_of_members(int num_elements);
        int get_height() const;
        void set_height( int height);
        int get_column() const;
        void set_column(int column);
        Node* get_root() const;

        //Please notice there may be bugs because of the two direction list
        void set_root(Node* root);
    };


    class Node
    {
    public:
        Record* m_record;
        GroupOfNodes* m_group;
        Node* m_father;
        int global_height;

        friend class Union_Find;

        /*-----------------the big three-----------*/
    public:
        Node();
        void resetNode();
        ~Node();
        Node(const Node& other) = delete;
        Node& operator=(const Node& node2) = delete;

        /*----------------getters and setters---------------*/
        Record* get_record() const;
        void set_record(Record* r);
        GroupOfNodes* get_group() const;
        void set_group(GroupOfNodes* g);
        /*Node* get_son() const;
        void set_son(Node* );*/
        void set_father(Node*);
        Node* get_father() const;
        static Node* find_root(Node *node);
        int get_global_height() const;
        void set_global_height(int global_height);
    };


    GroupOfNodes *find(int recordID) const;
};

#endif //UNION_FIND_H
