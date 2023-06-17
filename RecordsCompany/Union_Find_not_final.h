
#include <cstdio>
#include <exception>

#ifndef GROUP_CPP_UNION_FIND_H
#define GROUP_CPP_UNION_FIND_H

template <class T>
class Union_Find
{
    class Node
    {
        T* element;
        int size_of_group = 1;
        Node* father = nullptr;

        friend class Union_Find;
        void resetNode(){
            this->size_of_group = 0;
            this->element = nullptr;
            this->father = nullptr;
        }
        ~Node();
        void set_father(Node* father){
            this->m_father = father;
        }
        static Node* find_root(Node *node)
        {
            assert(node != nullptr);
            Node* temp = node;
            while (temp->father)
            {
                temp = temp->father;
            }
            return temp;

        }
    };
    Node** elements;
    int size = 0;
    Node* find_root_of_heap_aux(int item);

public:
    explicit Union_Find(int size);
    T* find_root_of_heap(int item);
    void Union(int item_1, int item_2);
    void merge(Node* group_to_delete, Node* group_to_insert_to);
    Union_Find(const Union_Find& other) = delete;
    Union_Find& operator=(const Union_Find& other) = delete;
    ~Union_Find();
};



template<class T>
Union_Find<T>::Node::~Node()
{
    delete element;
    resetNode();
}

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
    Node* root = Node::find_root(location);;
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
