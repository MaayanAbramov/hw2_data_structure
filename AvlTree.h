//
// Created by maaya on 06/06/2023.
//

#ifndef RECORDSCOMPANY_AVLTREE_H
#define RECORDSCOMPANY_AVLTREE_H

#define H_OF_LEAF 0

#include <iostream>
using namespace std;

template <class T>
class AvlTree{
public:
    class Node {
    public:
        T m_data;
        int m_height;
        int m_balance_factor;
        Node* m_ptr_left;
        Node* m_ptr_right;
        Node* m_ptr_father;
        explicit Node(const T &data) : m_data(data), m_height(H_OF_LEAF), m_balance_factor(0), m_ptr_left(nullptr),
                                       m_ptr_right(nullptr), m_ptr_father(nullptr) {}
        T getData(){return this->m_data;}
    };
public:
    Node* ptr_main_root;
    int m_num_elements;
    AvlTree() : ptr_main_root(nullptr), m_num_elements(0) {}

    void deleteNodesOfTree(Node* curr_node) { // the argument is only for the recursive calls
        //if we got to the leaf's child (which does not exist)
        if (curr_node == nullptr) {
            return;
        }
        //recursive calls
        deleteNodesOfTree(curr_node->m_ptr_right);
        deleteNodesOfTree(curr_node->m_ptr_left);
        m_num_elements--;
        delete curr_node;
    }


    ~AvlTree() {
        deleteNodesOfTree(ptr_main_root);
    }


    // a function that gets the key and returns true if the given key is in the tree
    bool is_key_exists(Node* main_root, const T& key) {
        if (main_root == nullptr) {
            return false;
        }

        if (main_root->m_data == key) {
            return true;
        }
        else if (main_root->m_data < key){
            return is_key_exists(main_root->m_ptr_right, key);
        }
        else if (main_root->m_data > key) {
            return is_key_exists(main_root->m_ptr_left, key);
        }
        return false; // doesn't suppose to get here
    }


    // If the function gets a key that does not exist, returns nullptr
    // returns a pointer to a node with a given value
    // the value is a node in a tree, and ptr_node is not a null
    // a function that gets the key and returns the pointer to it
    T* find_pointer_t(Node* ptr_node, const T& key) {
        bool if_exists = is_key_exists(ptr_main_root, key);
        if (!if_exists) {
            return nullptr;
        }

        if (ptr_node->m_data == key) {
            return &(ptr_node->m_data);
        }
        else if (ptr_node->m_data < key) {
            return find_pointer_t(ptr_node->m_ptr_right, key);
        }
        else {
            return find_pointer_t(ptr_node->m_ptr_left, key);
        }
    }


    // If the function gets a key that does not exist, returns nullptr
    // returns a pointer to a node with a given value
    // the value is a node in a tree, and ptr_node is not a null
    // a function that gets the key and returns the pointer to it
    Node* find_pointer_node(Node* ptr_node, const T& key) {
        bool if_exists = is_key_exists(ptr_main_root, key);
        if (!if_exists) {
            return nullptr;
        }

        if (ptr_node->m_data == key) {
            return ptr_node;
        }
        else if (ptr_node->m_data < key) {
            return find_pointer_node(ptr_node->m_ptr_right, key);
        }
        else {
            return find_pointer_node(ptr_node->m_ptr_left, key);
        }
    }

private:
    //------------------------------------tree process functions---------------------
    //a function that gets a pointer to a Node and returns the height of it
    int height(Node* node_ptr) {
        int right_height, left_height;
        if (node_ptr == nullptr) {
            return -1; // 0 or -1?

        }

        if (node_ptr->m_ptr_right == nullptr && node_ptr->m_ptr_left == nullptr) {
            return 0;
        }

        if (node_ptr->m_ptr_right == nullptr) {
            right_height = 0;
        } else {
            right_height = 1 + node_ptr->m_ptr_right->m_height;
        }

        if (node_ptr->m_ptr_left == nullptr) {
            left_height = 0;
        } else {
            left_height = 1 + node_ptr->m_ptr_left->m_height;
        }

        return std::max(right_height, left_height);
    }


    // updates a height and a balance factor of a given node
    void update(Node* source) {
        if(source == nullptr)
            return;
        source->m_height = height(source);
        source->m_balance_factor = difference(source);
    }


    // a function that indicates whether the specific pointer to the sub tree is balanced
    // please notice that this function is not getting null in the implementation
    int difference(Node* node_ptr) {
        //a pointer to a subtree with only one node
        if (node_ptr->m_ptr_right == nullptr && node_ptr->m_ptr_left == nullptr) {
            return 0;
        }

        //a pointer to a subtree with only two nodes -> (a root and a left leaf)
        else if (node_ptr->m_ptr_right == nullptr) {
            return node_ptr->m_ptr_left->m_height - (-1);
        }

        //a pointer to a subtree with only two nodes -> (a root and a right leaf)
        else if (node_ptr->m_ptr_left == nullptr) {
            return -1-node_ptr->m_ptr_right->m_height;
        }

        //a pointer to a subtree with two sons or more
        else {
            return node_ptr->m_ptr_left->m_height - node_ptr->m_ptr_right->m_height;
        }
    }

    // left left rotation
    // please notice that this function is not getting null in the implementation
    Node* left_left_rotation(Node* parent) {
        Node* tempA;
        tempA = parent->m_ptr_left;

        if (tempA != nullptr) {
            parent->m_ptr_left = tempA->m_ptr_right;
            tempA->m_ptr_right = parent;
            //cout << "did an action" << endl;

            // changing heights
            update(parent);
            update(tempA);

            // changing pointers to father
            tempA->m_ptr_father = parent->m_ptr_father;
            parent->m_ptr_father = tempA;

            if (parent->m_ptr_left != nullptr) {
                parent->m_ptr_left->m_ptr_father = parent;
            }
        }
        return tempA;
    }

    // right right rotation
    // please notice that this function is not getting null in the implementation
    Node* right_right_rotation(Node* parent) {
        Node* tempA;
        tempA = parent->m_ptr_right;

        if (tempA != nullptr) {
            parent->m_ptr_right = tempA->m_ptr_left;
            tempA->m_ptr_left = parent;

            // changing heights
            update(parent);
            update(tempA);

            // changing pointers to father
            tempA->m_ptr_father = parent->m_ptr_father;
            parent->m_ptr_father = tempA;

            if (parent->m_ptr_right != nullptr) {
                parent->m_ptr_right->m_ptr_father = parent;
            }
        }
        return tempA;
    }

    // left right rotation
    // please notice that this function is not getting null in the implementation
    Node* left_right_rotation(Node* parent) {
        if (parent->m_ptr_left == nullptr) {
            return parent;
        }

        Node* tempA;
        tempA = parent->m_ptr_left;

        Node* tempB;
        tempB = tempA->m_ptr_right;

        if (tempB != nullptr) {
            parent->m_ptr_left = tempB->m_ptr_right;
            tempB->m_ptr_right = parent;

            tempA->m_ptr_right = tempB->m_ptr_left;
            tempB->m_ptr_left = tempA;

            // changing heights
            update(parent);
            update(tempA);
            update(tempB);

            // changing pointers to father
            tempB->m_ptr_father = parent->m_ptr_father;
            tempA->m_ptr_father = tempB;
            parent->m_ptr_father = tempB;

            if (tempA->m_ptr_right != nullptr) {
                tempA->m_ptr_right->m_ptr_father = tempA; // Bl
            }
            if (parent->m_ptr_left != nullptr) {
                parent->m_ptr_left->m_ptr_father = parent; // Br
            }
        }

        return tempB;
    }

    // right left rotation
    // please notice that this function is not getting null in the implementation
    Node* right_left_rotation(Node* parent) {
        if (parent->m_ptr_right == nullptr) {
            return parent;
        }

        Node* tempA;
        tempA = parent->m_ptr_right;
        Node* tempB;
        tempB = tempA->m_ptr_left;

        if (tempB != nullptr) {
            parent->m_ptr_right = tempB->m_ptr_left;
            tempB->m_ptr_left = parent;

            tempA->m_ptr_left = tempB->m_ptr_right;
            tempB->m_ptr_right = tempA;

            // changing heights
            update(parent);
            update(tempA);
            update(tempB);

            // changing pointers to father
            tempB->m_ptr_father = parent->m_ptr_father;
            tempA->m_ptr_father = tempB;
            parent->m_ptr_father = tempB;

            if (parent->m_ptr_right != nullptr) {
                parent->m_ptr_right->m_ptr_father = parent;
            }
            if (tempA->m_ptr_left != nullptr) {
                tempA->m_ptr_left->m_ptr_father = tempA;
            }
        }

        return tempB;
    }


    // NOTICE: the values here are slightly different from the presentation
    //a function that gets a pointer to a sub tree and makes him an avl sub tree
    Node* balance(Node* ptr_node) {
        int balance_factor = ptr_node->m_balance_factor;

        if (balance_factor == 2) {
            if (difference(ptr_node->m_ptr_left) >=0) {
                ptr_node = left_left_rotation(ptr_node);
            }
            else if (difference(ptr_node->m_ptr_left) == -1) {
                ptr_node = left_right_rotation(ptr_node);
            }
        }
        else if (balance_factor == -2) {
            if (difference(ptr_node->m_ptr_right) <= 0) {
                ptr_node = right_right_rotation(ptr_node);
            }
            else if (difference(ptr_node->m_ptr_right) == 1) {
                ptr_node = right_left_rotation(ptr_node);
            }
        }

        return ptr_node;
    }

public:
    //insert a new node to a tree while keeping it avl balanced
    Node* insert(Node* source, const T& key) {
        if (source == nullptr) {
            //updates m_data, m_ptr_left, m_ptr_right and the rest - constructor
            source = new Node(key); //TO DO : check where need to be deleted

            if (ptr_main_root == nullptr) {
                ptr_main_root = source;
            }

            m_num_elements++;
            return source;
        }

        else if(source->m_data > key) {
            auto temp = insert(source->m_ptr_left, key);
            source->m_ptr_left = temp;
            temp->m_ptr_father = source;

            update(source);
            source = balance(source);
        }

        else if (source->m_data < key) {
            //source->m_height++;
            auto temp = insert(source->m_ptr_right, key);
            source->m_ptr_right = temp;
            temp->m_ptr_father = source;
            update(source);
            source = balance(source);
        }

        ptr_main_root = find_main_root(source);
        return source;
    }

public:
    Node* find_main_root(Node* node) {
        if (node == nullptr) {
            return nullptr;
        }
        if (node->m_ptr_father == nullptr) {
            return node;
        }
        return find_main_root(node->m_ptr_father);
    }


    // deletes a note of a tree while keeping it avl balanced
    void remove_node(Node* main_root, const T& key) {

        Node* ptr_v = find_pointer_node(main_root, key);
        if (ptr_v == nullptr) {
            return;
        }
        m_num_elements--;
        Node* temp = ptr_v->m_ptr_father;

        // if ptr_v is a leaf - delete it
        if (ptr_v->m_ptr_left == nullptr && ptr_v->m_ptr_right == nullptr) {
            // removes an only root of a tree
            if (temp == nullptr) {
                ptr_main_root = nullptr;
            }

            // if ptr_v is a left son
            else if (temp->m_ptr_left == ptr_v) {
                temp->m_ptr_left = nullptr;
            }

            // if ptr_v is a right son
            else {
                temp->m_ptr_right = nullptr;
            }

            ptr_v->m_ptr_father = nullptr;
            delete ptr_v;
        }

        // if ptr_v has only left son
        else if (ptr_v->m_ptr_left != nullptr && ptr_v->m_ptr_right == nullptr) {
            //cout << "remove | case 2 "<< endl;
            if (temp == nullptr) {
                ptr_main_root = ptr_v->m_ptr_left;
            }

            // checks if ptr_v is a left son or a right son to his father
            if ((ptr_v->m_ptr_father != nullptr) && (ptr_v->m_ptr_father->m_ptr_left == ptr_v)) {
                ptr_v->m_ptr_father->m_ptr_left = ptr_v->m_ptr_left;
            }
            else if (ptr_v->m_ptr_father != nullptr) {
                ptr_v->m_ptr_father->m_ptr_right = ptr_v->m_ptr_left;
            }

            ptr_v->m_ptr_left->m_ptr_father = ptr_v->m_ptr_father;
            ptr_v->m_ptr_father = nullptr;
            delete ptr_v;
        }

        // if ptr_v has only right son
        else if (ptr_v->m_ptr_left == nullptr && ptr_v->m_ptr_right != nullptr) {
            if (temp == nullptr) {
                ptr_main_root = ptr_v->m_ptr_right;
            }

            // checks if ptr_v is a left son or a right son to his father
            if ((ptr_v->m_ptr_father != nullptr) && (ptr_v->m_ptr_father->m_ptr_left == ptr_v)) {
                ptr_v->m_ptr_father->m_ptr_left = ptr_v->m_ptr_right;
            }

            else if (ptr_v->m_ptr_father != nullptr) {
                ptr_v->m_ptr_father->m_ptr_right = ptr_v->m_ptr_right;
            }

            ptr_v->m_ptr_right->m_ptr_father = ptr_v->m_ptr_father;
            ptr_v->m_ptr_father = nullptr; // check if it works (and if its necessary?)
            delete ptr_v;
        }

        // if ptr_v has both sons
        else {
            Node* ptr_w = find_next_inorder(main_root, ptr_v);

            T temp_data = ptr_v->m_data;
            ptr_v->m_data = ptr_w->m_data;
            ptr_w->m_data = temp_data;

            temp = ptr_w->m_ptr_father;

            // if ptr_w is a leaf - delete it
            if (ptr_w->m_ptr_left == nullptr && ptr_w->m_ptr_right == nullptr) {
                // if ptr_w is a left son
                if (temp->m_ptr_left == ptr_w) {
                    temp->m_ptr_left = nullptr;
                }

                // if ptr_w is a right son
                else {
                    temp->m_ptr_right = nullptr;
                }

                ptr_w->m_ptr_father = nullptr;
                delete ptr_w;
            }

            // if ptr_w has only left son
            else if (ptr_w->m_ptr_left != nullptr && ptr_w->m_ptr_right == nullptr) {

                // checks if ptr_w is a left son or a right son to his father
                if (ptr_w->m_ptr_father->m_ptr_left == ptr_w) {
                    ptr_w->m_ptr_father->m_ptr_left = ptr_w->m_ptr_left;
                }
                else {
                    ptr_w->m_ptr_father->m_ptr_right = ptr_w->m_ptr_left;
                }

                ptr_w->m_ptr_left->m_ptr_father = ptr_w->m_ptr_father;
                ptr_w->m_ptr_father = nullptr;
                delete ptr_w;
            }

            // if ptr_w has only right son
            else if (ptr_w->m_ptr_left == nullptr && ptr_w->m_ptr_right != nullptr) {

                // checks if ptr_w is a left son or a right son to his father
                if (ptr_w->m_ptr_father->m_ptr_left == ptr_w) {
                    ptr_w->m_ptr_father->m_ptr_left = ptr_w->m_ptr_right;
                }
                else {
                    ptr_w->m_ptr_father->m_ptr_right = ptr_w->m_ptr_right;
                }

                ptr_w->m_ptr_right->m_ptr_father = ptr_w->m_ptr_father;
                ptr_w->m_ptr_father = nullptr;
                delete ptr_w;
            }


        }

        if (temp == nullptr) {
            return;
        }

        Node* temp_backup = temp;
        update(temp);
        temp = balance(temp);
        Node* temps_father = nullptr;

        while (temp != nullptr) {
            update(temp);
            temps_father = temp->m_ptr_father;
            temp = balance(temp);
            temp->m_ptr_father = temps_father;
            if ((temps_father != nullptr) && (temps_father->m_data > temp->m_data)) {
                temps_father->m_ptr_left = temp;
                temps_father->m_ptr_right = temp->m_ptr_father->m_ptr_right;
            }
            else if ((temps_father != nullptr) && (temps_father->m_data < temp->m_data)){
                temps_father->m_ptr_right = temp;
                temps_father->m_ptr_left = temp->m_ptr_father->m_ptr_left;
            }

            temp = temp->m_ptr_father;
            if (temp != nullptr) {
                temp_backup = temp;
            }
        }

        update(temp_backup);
        temp_backup = balance(temp_backup);
        update(temp_backup);
        ptr_main_root = find_main_root(temp_backup);
    }


// HELPER FUNCTIONS

private:
    // updates a height and a balance factor of a given node + all nodes above till root
    void recursive_update(Node* main_root, Node* curr) {
        if (curr == main_root) {
            update(main_root);
            return;
        }
        update(curr);
        recursive_update(main_root ,curr->m_ptr_father);
    }

    // we don't need this function anymore because we save a pointer to a father in each node ??
    // assuming there is at least one node in a tree
    //a function that gets a pointer to a sun and return a pointer to his father
    Node* find_father(Node* node_ptr, int val_of_son) {
        // checks right branch
        if (val_of_son > node_ptr->m_data) {
            if ((node_ptr->m_ptr_right != nullptr) && (node_ptr->m_ptr_right->m_data == val_of_son)) {
                return node_ptr;
            }

            else if (node_ptr->m_ptr_right != nullptr) {
                return find_father(node_ptr->m_ptr_right, val_of_son);
            }
        }

        // checks left branch
        else if (val_of_son < node_ptr->m_data) {
            if ((node_ptr->m_ptr_left != nullptr) && (node_ptr->m_ptr_left->m_data == val_of_son)) {
                return node_ptr;
            }

            else if (node_ptr->m_ptr_right != nullptr) {
                return find_father(node_ptr->m_ptr_left, val_of_son);
            }
        }

        // we tried to find a father of a root and there isn't any
        else {
            return nullptr;
        }
    }

    //the function is getting a right leaf and returns his legal father
    //the function finds the father in order (or grandfather) (or grand - grand father)
    Node* distant_grandfather_inorder(Node* ptr_node, Node* ptr_node_v) {
        if (ptr_node_v->m_ptr_father == nullptr) { //the right leaf in the edge has no father
            return nullptr;
        }

        if (ptr_node_v->m_ptr_father->m_ptr_left == ptr_node_v) {
            return ptr_node_v->m_ptr_father;
        }
        else {
            return distant_grandfather_inorder(ptr_node, ptr_node_v->m_ptr_father);
        }
        return nullptr; //dont suppose to get here
    }


    // Notice: need to consider the case that the edge right son is given in the argument
    // the function returns nullptr if there is no father (meaning we got upper than the root)
    // both of  the following func need debugging!
    //a function that gets a pointer to node v and returns a pointer to his consecutive in inorder
    Node* find_next_inorder(Node* node_ptr, Node* node_ptr_v) {
        // if node_ptr_v->m_ptr_right == nullptr && node_ptr_v is a left son
        if ((node_ptr_v->m_ptr_right == nullptr) &&
            ((node_ptr_v->m_ptr_father!= nullptr) &&
             (node_ptr_v->m_ptr_father->m_ptr_left != nullptr) &&
             (node_ptr_v->m_ptr_father->m_ptr_left == node_ptr_v))) {

            return node_ptr_v->m_ptr_father;
        }

        // if node_ptr_v->m_ptr_right != nullptr
        else if (node_ptr_v->m_ptr_right != nullptr) {
            return distant_son(node_ptr_v->m_ptr_right);
        }

        else {
            return distant_grandfather_inorder(node_ptr, node_ptr_v);
        }
    }


    // returns the leftmost leaf of a current node
    Node* distant_son(Node* node_ptr_v) {
        if (node_ptr_v->m_ptr_left == nullptr) {
            return node_ptr_v;
        }

        return distant_son(node_ptr_v->m_ptr_left);
    }

};


#endif //RECORDSCOMPANY_AVLTREE_H
