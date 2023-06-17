
#include <cstdio>
#include <exception>
#include "cassert"
#include "Record.h"

#ifndef GROUP_CPP_UNION_FIND_H
#define GROUP_CPP_UNION_FIND_H




class Union_Find
{
public:
    class Node;
    class GroupOfNodes;
private:
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
    int recursive_height_sum(Node* ) const;
    int get_height(int r_id) const;
    /*----------------process functions------*/
    Record* find_root_of_heap(int item);
    //this function also shrunken
    GroupOfNodes* find_group(int r_id) const;
    GroupOfNodes* Union(GroupOfNodes* group_1_up, GroupOfNodes* group_2_down);






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
        Node* m_son;
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
        Node* get_son() const;
        void set_son(Node* );
        void set_father(Node*);
        Node* get_father() const;
        static Node* find_root(Node *node);
        int get_global_height() const;
        void set_global_height(int global_height);




    };

};






template<class T>
Union_Find<T>::Union_Find(int size)
{
    if (size<=0)
        throw std::exception();
    elements = new Node*[size];
    this->size = size;
    for(int i=0; i<size; i++)
    {
        elements[i] = new Node;
        elements[i]->father = nullptr;
        elements[i]->size_of_group = 1;
        elements[i]->element = new T;
        elements[i]->height = 0;
        elements[i]->bottom = elements[i]; //his self
    }
}
template <class T>
void Union_Find<T>::merge(Node* group_to_delete, Node* group_to_insert_to) {


}
template<class T>
void Union_Find<T>::Union(int item_1, int item_2)
{

    Node* item_1_location = find_root_of_heap_aux(item_1);
    Node* item_2_location = find_root_of_heap_aux(item_2);
    if(item_1_location->element == item_2_location->element) { //if by a mistake those are the same groups
        return;
    }
    if(item_1_location->size_of_group <= item_2_location->size_of_group)
    {
        merge(item_1_location, item_2_location); //merge is T method
        item_1_location->father = item_2_location;
        item_2_location->size_of_group += item_1_location->size_of_group;
    }
    else
    {
        merge(item_2_location->element, item_1_location->element);
        item_2_location->father = item_1_location;
        item_1_location->size_of_group += item_2_location->size_of_group;
    }
}

template<class T>
T *Union_Find<T>::find_root_of_heap(int item)
{
    return find_root_of_heap_aux(item)->element;
}

template<class T>
typename Union_Find<T>::Node* Union_Find<T>::find_root_of_heap_aux(int item)
{
    Node* location = elements[item];
    if(!location)
        return nullptr;
    Node* root = Node::find_root(location);
    Node* temp;
    while(location->father) //updating the field father ot the item to be the main root "squizing"
    {
        temp = location->father;
        location->set_father(root);
        location = temp;
    }
    return root;
}

template<class T>
Union_Find<T>::~Union_Find()
{
    for(int i=0; i<size; i++)
    {
        delete elements[i];
    }
    delete[] elements;
}

#endif //GROUP_CPP_UNION_FIND_H
