//
// Created by maaya on 14/06/2023.
//

#ifndef RECORDSCOMPANY_RANKTREE_H
#define RECORDSCOMPANY_RANKTREE_H


#define H_OF_LEAF 0

#include <iostream>
using namespace std;
//#include <string>
//#include <iomanip>

template <class T>
class Getter{
public:
    virtual ~Getter() = default;
    virtual int operator()(T) = 0;
};

template <class T>
class RankTree{
public:
    //void printRankTree(const RankTree<T> &avl);
    class Node {
    public:
        T m_data;
        int m_height;
        int m_balance_factor;
        double m_prize;
        double m_prize2;
        Node* m_ptr_left;
        Node* m_ptr_right;
        Node* m_ptr_father;
        explicit Node(const T &data) : m_data(data), m_height(H_OF_LEAF), m_balance_factor(0), m_prize(0), m_prize2(0),
                                       m_ptr_left(nullptr),m_ptr_right(nullptr), m_ptr_father(nullptr) {}
        T getData(){return this->m_data;}
        int getPrize() {return this->m_prize;}
    };

public:
    Node* ptr_main_root;
    int m_num_elements;
    Getter<T> *m_getter;
    explicit RankTree(Getter<T> *getter) : ptr_main_root(nullptr), m_num_elements(0), m_getter(getter) {}

    void deleteNodesOfTree(Node* curr_node) { // the argument is only for the recursive call15
        //cout << "deleteNodesOfTree | got in" << endl;
        //if we got to the leaf's child (which does not exist)
        if (curr_node == nullptr) {
            return;
        }
        //recursive calls
        deleteNodesOfTree(curr_node->m_ptr_right);
        deleteNodesOfTree(curr_node->m_ptr_left);
        m_num_elements--;
        delete curr_node;
        //cout << "deleteNodesOfTree | got out" << endl;
    }


    ~RankTree() {
        //cout << " ~RankTree | got in --------------------------------------------------------------------------"<<
        // endl;

        deleteNodesOfTree(ptr_main_root);
        delete m_getter;
        //cout << " ~RankTree | got out "<< endl;
    }


    // a function that gets the key and returns true if the given key is in the tree
    bool is_key_exists(Node* main_root, const T& key) {
        if (main_root == nullptr) {
            //cout << "is_key_exists | check" << endl;
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
        //cout << "is_key_exists | got out from the false that Reuven added" << endl;
        return false; // doesn't suppose to get here
    }


    //If the function gets a key that does not exist, returns nullptr
    // returns a pointer to a node with a given value
    // the value is a node in a tree, and ptr_node is not a null
    // a function that gets the key and returns the pointer to it
    T* find_pointer_t(Node* ptr_node, const T& key) {
        bool if_exists = is_key_exists(ptr_main_root, key);
        if (!if_exists) {
            return nullptr;
        }
        //RankTree::Node* ptr_found;

        if (ptr_node->m_data == key) {
            //cout << "I found the pointer of "<< ptr_node->m_data << endl;
            //cout << "and the pointer is " << ptr_node << endl;

            //ptr_found = ptr_node;
            return &(ptr_node->m_data);
        }
        else if (ptr_node->m_data < key) {
            //cout << " curr val of a node is less than key | " << endl;
            //cout << " curr val of a node is: " << ptr_node->m_data << endl;
            return find_pointer_t(ptr_node->m_ptr_right, key);
        }
        else {
            //cout << " curr val of a node is greater than key | " << endl;
            //cout << " curr val of a node is: " << ptr_node->m_data << endl;
            return find_pointer_t(ptr_node->m_ptr_left, key);
        }
    }
    Node* find_pointer_node(Node* ptr_node, const T& key) {
        bool if_exists = is_key_exists(ptr_main_root, key);
        if (!if_exists) {
            return nullptr;
        }
        //RankTree::Node* ptr_found;

        if (ptr_node->m_data == key) {
            //cout << "I found the pointer of "<< ptr_node->m_data << endl;
            //cout << "and the pointer is " << ptr_node << endl;

            //ptr_found = ptr_node;
            return ptr_node;
        }
        else if (ptr_node->m_data < key) {
            //cout << " curr val of a node is less than key | " << endl;
            //cout << " curr val of a node is: " << ptr_node->m_data << endl;
            return find_pointer_node(ptr_node->m_ptr_right, key);
        }
        else {
            //cout << " curr val of a node is greater than key | " << endl;
            //cout << " curr val of a node is: " << ptr_node->m_data << endl;
            return find_pointer_node(ptr_node->m_ptr_left, key);
        }
    }

private:
    //------------------------------------tree process functions---------------------
    //a function that gets a pointer to a Node and returns the height of it
    int height(Node* node_ptr) {
        int right_height, left_height;
        //cout << "height - before ifs | " << endl;
        if (node_ptr == nullptr) {
            //cout << "height - pointer to null | " << endl;
            return -1; // 0 or -1?

        }

        if (node_ptr->m_ptr_right == nullptr && node_ptr->m_ptr_left == nullptr) {
            //cout << "height - right & left pointers of a node are null | " << endl;
            return 0;
        }

        if (node_ptr->m_ptr_right == nullptr) {
            //cout << "height - only right ptr is null | " << endl;
            right_height = 0;
        } else {
            //cout << "height - right ptr is not null | " << endl;
            right_height = 1 + node_ptr->m_ptr_right->m_height;
        }

        if (node_ptr->m_ptr_left == nullptr) {
            //cout << "height - only left ptr is null | " << endl;
            left_height = 0;
        } else {
            //cout << "height - left ptr is not null | " << endl;
            left_height = 1 + node_ptr->m_ptr_left->m_height;
        }

        //cout << "right_height = " << right_height << endl;
        //cout << "left_height = " <<left_height << endl;
        return std::max(right_height, left_height);
    }

    int weight(Node* node_ptr) {
        int right_height, left_height;
        //cout << "height - before ifs | " << endl;
        if (node_ptr == nullptr) {
            //cout << "height - pointer to null | " << endl;
            return 0; // 0 or -1?

        }

        if (node_ptr->m_ptr_right == nullptr && node_ptr->m_ptr_left == nullptr) {
            //cout << "height - right & left pointers of a node are null | " << endl;
            return 0;
        }

        if (node_ptr->m_ptr_right == nullptr) {
            //cout << "height - only right ptr is null | " << endl;
            right_height = 0;
        } else {
            //cout << "height - right ptr is not null | " << endl;
            right_height = 1 + node_ptr->m_ptr_right->m_height;
        }

        if (node_ptr->m_ptr_left == nullptr) {
            //cout << "height - only left ptr is null | " << endl;
            left_height = 0;
        } else {
            //cout << "height - left ptr is not null | " << endl;
            left_height = 1 + node_ptr->m_ptr_left->m_height;
        }

        //cout << "right_height = " << right_height << endl;
        //cout << "left_height = " <<left_height << endl;
        return std::max(right_height, left_height);
    }


    // updates a height and a balance factor of a given node
    void update(Node* source) {
        if(source == nullptr)
            return;
        //cout << "update - before height | " << endl;
        //cout << "update - source->m_height: " << source->m_height << endl;
        //cout << "the argument of height is " << source->m_data << endl;
        source->m_height = height(source);
        //cout << "update - after height & before difference | " << endl;
        source->m_balance_factor = difference(source);
        //cout << "update - after difference | " << endl;
    }

    //a function that indicates whether the specific pointer to the sub tree is balanced
    //Please notice that this function is not getting null in the implementation
    int difference(Node* node_ptr) {
        //a pointer to a subtree with only one node
        if (node_ptr->m_ptr_right == nullptr && node_ptr->m_ptr_left == nullptr) {
            //cout << "difference - right and left is null | " << endl;
            return 0;
        }
            //a pointer to a subtree with only two nodes -> (a root and a left leaf)
        else if (node_ptr->m_ptr_right == nullptr) {
            //cout << "difference - right is null | " << endl;
            return node_ptr->m_ptr_left->m_height - (-1);
        }
            //a pointer to a subtree with only two nodes -> (a root and a right leaf)
        else if (node_ptr->m_ptr_left == nullptr) {
            //cout << "difference - left is null | " << endl;
            return -1-node_ptr->m_ptr_right->m_height;
        }
        else {
            //a pointer to a subtree with a two sons or more
            //cout << "difference - both are not null | " << endl;
            return node_ptr->m_ptr_left->m_height - node_ptr->m_ptr_right->m_height;
        }
    }

    //left left rotation
    //not getting null in arg
    Node* left_left_rotation(Node* parent) {
        Node* tempA;
        tempA = parent->m_ptr_left;

        parent->m_prize2 = acumulated_sum(parent);
        tempA->m_prize2 = acumulated_sum(tempA);

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
        int not_updated_prize_for_A = acumulated_sum(tempA);
        if (not_updated_prize_for_A != tempA->m_prize2)  {
            tempA->m_prize = tempA->m_prize2 - (not_updated_prize_for_A - tempA->m_prize);
        }
        int not_updated_prize_for_B = acumulated_sum(parent);
        if (not_updated_prize_for_B != parent->m_prize2)  {
            parent->m_prize = parent->m_prize2 - (not_updated_prize_for_B - parent->m_prize);
        }

        //cout << "#temp A = " <<tempA->m_data << endl;
        return tempA;

    }

    //right right rotation
    Node* right_right_rotation(Node* parent) {
        Node* tempA;
        tempA = parent->m_ptr_right;

        parent->m_prize2 = acumulated_sum(parent);
        tempA->m_prize2 = acumulated_sum(tempA);

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

        int not_updated_prize_for_A = acumulated_sum(tempA);
        if (not_updated_prize_for_A != tempA->m_prize2)  {
            tempA->m_prize = tempA->m_prize2 - (not_updated_prize_for_A - tempA->m_prize);
        }
        int not_updated_prize_for_B = acumulated_sum(parent);
        if (not_updated_prize_for_B != parent->m_prize2)  {
            parent->m_prize = parent->m_prize2 - (not_updated_prize_for_B - parent->m_prize);
        }


        return tempA;
    }

    //left right rotation
    Node* left_right_rotation(Node* parent) {
        if (parent->m_ptr_left == nullptr) {
            //cout << "LR rotation | parent->m_ptr_left == nullptr" << endl;
            return parent;
        }

        Node* tempA;
        tempA = parent->m_ptr_left;
        //cout << "LR rotation | tempA = parent->m_ptr_left " << endl;
        Node* tempB;
        tempB = tempA->m_ptr_right;
        //cout << "LR rotation |  tempB = tempA->m_ptr_right" << endl;



        if (tempB != nullptr) {
            parent->m_prize2 = acumulated_sum(parent);
            tempA->m_prize2 = acumulated_sum(tempA);
            tempB->m_prize2 = acumulated_sum(tempB);
            parent->m_ptr_right->m_prize2 = acumulated_sum(parent->m_ptr_right);
            tempB->m_ptr_right->m_prize2 = acumulated_sum(tempB->m_ptr_right);
            tempA->m_ptr_left->m_prize2 = acumulated_sum(tempA->m_ptr_left);
            tempB->m_ptr_left->m_prize2 = acumulated_sum(tempB->m_ptr_left);

            //cout << "LR rotation | tempB != nullptr" << endl;
            parent->m_ptr_left = tempB->m_ptr_right;
            //cout << "LR rotation | parent->m_ptr_left = tempB->m_ptr_right" << endl;

            tempB->m_ptr_right = parent;
            //cout << "LR rotation | parent->m_ptr_left = tempB->m_ptr_right" << endl;

            tempA->m_ptr_right = tempB->m_ptr_left;
            //cout << "LR rotation | tempA->m_ptr_right = tempB->m_ptr_left" << endl;
            tempB->m_ptr_left = tempA;
            // cout << "LR rotation | tempB->m_ptr_left = tempA;" << endl;

            // changing heights
            update(parent);
            update(tempA);
            update(tempB);

            // changing pointers to father
            tempB->m_ptr_father = parent->m_ptr_father;
            //cout << "LR rotation | tempB->m_ptr_father = parent->m_ptr_father" << endl;
            tempA->m_ptr_father = tempB;
            //cout << "LR rotation | tempA->m_ptr_father" << endl;
            parent->m_ptr_father = tempB;
            //cout << "LR rotation | parent->m_ptr_father" << endl;

            if (tempA->m_ptr_right != nullptr) {
                tempA->m_ptr_right->m_ptr_father = tempA; // Bl
                //cout << "LR rotation | BL->m_ptr_father" << endl;
            }
            if (parent->m_ptr_left != nullptr) {
                parent->m_ptr_left->m_ptr_father = parent; // Br
                //cout << "LR rotation | Br->m_ptr_father" << endl;
            }

            int not_updated_prize_for_B = acumulated_sum(tempB);
            if (not_updated_prize_for_B != tempB->m_prize2)  {
                tempB->m_prize = tempB->m_prize2 - (not_updated_prize_for_B - tempB->m_prize);
            }
            int not_updated_prize_for_A = acumulated_sum(tempA);
            if (not_updated_prize_for_A != tempA->m_prize2)  {
                tempA->m_prize = tempA->m_prize2 - (not_updated_prize_for_A - tempA->m_prize);
            }
            int not_updated_prize_for_C = acumulated_sum(parent);
            if (not_updated_prize_for_C != parent->m_prize2) {
                parent->m_prize = parent->m_prize2 - (not_updated_prize_for_C - parent->m_prize);
            }
            int not_updated_prize_for_Cr = acumulated_sum(parent->m_ptr_right);
            if (not_updated_prize_for_Cr != parent->m_ptr_right->m_prize2) {
                parent->m_ptr_right->m_prize = parent->m_ptr_right->m_prize2 - (not_updated_prize_for_Cr -
                                                                                parent->m_ptr_right->m_prize);
            }
            int not_updated_prize_for_Br = acumulated_sum(parent->m_ptr_left);
            if (not_updated_prize_for_Br != parent->m_ptr_left->m_prize2) {
                parent->m_ptr_left->m_prize = parent->m_ptr_left->m_prize2 - (not_updated_prize_for_Br -
                                                                              parent->m_ptr_left->m_prize);
            }
            int not_updated_prize_for_Bl = acumulated_sum(tempA->m_ptr_right);
            if (not_updated_prize_for_Bl != tempA->m_ptr_right->m_prize2) {
                tempA->m_ptr_right->m_prize = tempA->m_ptr_right->m_prize2 - (not_updated_prize_for_Bl
                                                                              -tempA->m_ptr_right->m_prize);
            }
            int not_updated_prize_for_Al = acumulated_sum(tempA->m_ptr_left);
            if (not_updated_prize_for_Al != tempA->m_ptr_left->m_prize2) {
                tempA->m_ptr_left->m_prize = tempA->m_ptr_left->m_prize2 - (not_updated_prize_for_Al -
                                                                            tempA->m_ptr_left->m_prize);
            }


        }

        return tempB;
    }

    //right left rotation
    Node* right_left_rotation(Node* parent) {
        if (parent->m_ptr_right == nullptr) {
            return parent;
        }

        Node* tempA;
        tempA = parent->m_ptr_right;
        Node* tempB;
        tempB = tempA->m_ptr_left;

        if (tempB != nullptr) {
            parent->m_prize2 = acumulated_sum(parent);
            tempA->m_prize2 = acumulated_sum(tempA);
            tempB->m_prize2 = acumulated_sum(tempB);
            parent->m_ptr_left->m_prize2 = acumulated_sum(parent->m_ptr_left);
            tempA->m_ptr_right->m_prize2 = acumulated_sum(tempA->m_ptr_right);
            tempB->m_ptr_right->m_prize2 = acumulated_sum(tempB->m_ptr_right);
            tempB->m_ptr_left->m_prize2 = acumulated_sum(tempB->m_ptr_left);




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

            int not_updated_prize_for_B = acumulated_sum(tempB);
            if (not_updated_prize_for_B != tempB->m_prize2)  {
                tempB->m_prize = tempB->m_prize2 - (not_updated_prize_for_B - tempB->m_prize);
            }
            int not_updated_prize_for_A = acumulated_sum(tempA);
            if (not_updated_prize_for_A != tempA->m_prize2)  {
                tempA->m_prize = tempA->m_prize2 - (not_updated_prize_for_A - tempA->m_prize);
            }
            int not_updated_prize_for_C = acumulated_sum(parent);
            if (not_updated_prize_for_C != parent->m_prize2) {
                parent->m_prize = parent->m_prize2 - (not_updated_prize_for_C - parent->m_prize);
            }
            int not_updated_prize_for_Cl = acumulated_sum(parent->m_ptr_left);
            if (not_updated_prize_for_Cl != parent->m_ptr_left->m_prize2) {
                parent->m_ptr_left->m_prize = parent->m_ptr_left->m_prize2 - (not_updated_prize_for_Cl -
                                                                              parent->m_ptr_left->m_prize);
            }
            int not_updated_prize_for_Bl = acumulated_sum(parent->m_ptr_right);
            if (not_updated_prize_for_Bl != parent->m_ptr_right->m_prize2) {
                parent->m_ptr_right->m_prize = parent->m_ptr_right->m_prize2 - (not_updated_prize_for_Bl-
                                                                                parent->m_ptr_right->m_prize);
            }
            int not_updated_prize_for_Br = acumulated_sum(tempA->m_ptr_left);
            if (not_updated_prize_for_Br != tempA->m_ptr_left->m_prize2) {
                tempA->m_ptr_left->m_prize = tempA->m_ptr_left->m_prize2 - (not_updated_prize_for_Br -
                                                                            tempA->m_ptr_left->m_prize);
            }

            int not_updated_prize_for_Ar = acumulated_sum(tempA->m_ptr_right);
            if (not_updated_prize_for_Ar != tempA->m_ptr_right->m_prize2) {
                tempA->m_ptr_right->m_prize = tempA->m_ptr_right->m_prize2 - (not_updated_prize_for_Ar -
                                                                              tempA->m_ptr_right->m_prize);
            }

        }

        return tempB;
    }


    //NOTICE : the values here are slightly different from the presentation
    //a function that gets a pointer to a sub tree and makes him an avl sub tree
    Node* balance(Node* ptr_node) {
        int balance_factor = ptr_node->m_balance_factor;

        if (balance_factor == 2) {
            if (difference(ptr_node->m_ptr_left) >=0) {
                //cout << "balance - before LL-rotation | " << endl;
                ptr_node = left_left_rotation(ptr_node);

                //cout << "balance - after LL-rotation | " << endl;
                //cout << "balance - after LL-rotation tempA = "<< ptr_node->m_data << endl;
            }
            else if (difference(ptr_node->m_ptr_left) == -1) {
                //cout << "balance - before LR-rotation | " << endl;
                ptr_node = left_right_rotation(ptr_node);
                //cout << "balance - after LR-rotation | " << endl;
            }
        }
        else if (balance_factor == -2) {
            if (difference(ptr_node->m_ptr_right) <= 0) {
                //cout << "balance - before RR-rotation | " << endl;
                ptr_node = right_right_rotation(ptr_node);
                //cout << "balance - before RR-rotation | " << endl;
            }
            else if (difference(ptr_node->m_ptr_right) == 1) {
                //cout << "balance - before RL-rotation | " << endl;
                ptr_node = right_left_rotation(ptr_node);
                //cout << "balance - before RL-rotation | " << endl;
            }
        }
        //cout <<" " << endl;

        //cout << "balance - the final root is "<< ptr_node->m_data <<endl;
        return ptr_node;
    }
public:


    //insert a new node to a tree while keeping it avl balanced
    Node* insert(Node* source, const T& key, bool* just_inserted, bool* updated_the_boolean) {
        // initialize the boolean to false
        // to false;
        if (source == nullptr) {
            //updates m_data, m_ptr_left, m_ptr_right and the rest - constructor
            source = new Node(key); //TO DO : check where need to be deleted

            //update(source);

            //source->m_ptr_father = find_father(ptr_main_root, source->m_data);
            // cout << "source.data " << source->m_data << endl;

            if (ptr_main_root == nullptr) {
                ptr_main_root = source;
            }
            //printRankTree();
            //cout << "insert | ptr_main_root == nullptr" << endl;
            //printRankTree(*this);
            m_num_elements++;
            *just_inserted = true;
            return source;
        }

        else if(source->m_data > key) {
            //source->m_height++;
            auto temp = insert(source->m_ptr_left, key, just_inserted, updated_the_boolean);
            source->m_ptr_left = temp;
            temp->m_ptr_father = source;
            //cout <<"insert - problem 1 |  " << endl;
            update(source);
            if (*just_inserted == true && *updated_the_boolean == false) {
                temp->m_prize = (-1) * acumulated_sum(temp);

                *updated_the_boolean = true;
            }


            //cout << "insert - after update & before balance |" << endl;
            source = balance(source); // !!!
            //cout << "insert - got out of balance | " << endl;

            //source->m_ptr_father = find_father(ptr_main_root, source->m_data); // TODO: check if it works
        }

        else if (source->m_data < key) {
            //source->m_height++;
            auto temp = insert(source->m_ptr_right, key, just_inserted, updated_the_boolean);
            source->m_ptr_right = temp;
            temp->m_ptr_father = source;
            update(source);
            if (*just_inserted == true && *updated_the_boolean == false) {
                temp->m_prize = (-1) * acumulated_sum(temp);

                *updated_the_boolean = true;
            }
            source = balance(source); // !!

            //source->m_ptr_father = find_father(ptr_main_root, source->m_data); // TODO: check if it works
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
            //cout << "remove | case 1 "<< endl;
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
            ptr_v->m_ptr_father = nullptr; // check if it works (and if its necessary?)
            delete ptr_v;
        }

            // if ptr_v has only right son
        else if (ptr_v->m_ptr_left == nullptr && ptr_v->m_ptr_right != nullptr) {
            //cout << "remove | case 3 "<< endl;
            if (temp == nullptr) {
                //cout << "remove  |  temp == nullptr " << endl;
                ptr_main_root = ptr_v->m_ptr_right;
                //cout << "remove  |  temp == nullptr, after changing the pointer to a root " << endl;
            }

            // checks if ptr_v is a left son or a right son to his father
            if ((ptr_v->m_ptr_father != nullptr) && (ptr_v->m_ptr_father->m_ptr_left == ptr_v)) {
                //cout << "remove  | ptr_v->m_ptr_father->m_ptr_left == ptr_v  " << endl;
                ptr_v->m_ptr_father->m_ptr_left = ptr_v->m_ptr_right;
            }
            else if (ptr_v->m_ptr_father != nullptr) {
                //cout << "remove  | ptr_v->m_ptr_father->m_ptr_left != ptr_v  " << endl;
                ptr_v->m_ptr_father->m_ptr_right = ptr_v->m_ptr_right;
            }

            //cout << "remove  |  ptr_v->m_ptr_right->m_ptr_father = ptr_v->m_ptr_father " << endl;
            ptr_v->m_ptr_right->m_ptr_father = ptr_v->m_ptr_father;
            ptr_v->m_ptr_father = nullptr; // check if it works (and if its necessary?)
            //cout << "remove  |  delete " << endl;
            delete ptr_v;
        }

            // if ptr_v has both sons
        else {
            //cout << "remove | case 4 "<< endl;
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

                ptr_w->m_ptr_father = nullptr; // check if it works (and if its necessary?)
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
                ptr_w->m_ptr_father = nullptr; // check if it works (and if its necessary?)
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
                ptr_w->m_ptr_father = nullptr; // check if it works (and if its necessary?)
                delete ptr_w;
            }


        }

        if (temp == nullptr) {
            //cout << "remove | temp is nullptr" << endl;
            return;
        } else {
            //cout << "remove | value in temp is: " << temp->m_data << endl;
            //cout << "de- reference to nullptr" <<endl;
        }


        Node* temp_backup = temp; //It doesnt matter the initialization
        update(temp);
        temp = balance(temp);
        Node* temps_father = nullptr; // why?

        //int i = 0;
        while (temp != nullptr) {
            //i++;
            //cout << "got into the while for the #i = " << i<< "time" <<endl;

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
            //cout  << "expected the correct tree" << endl;
            //RankTree::printRankTree(*this);
            //cout << endl << endl;
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
public:
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
        //cout << "find_father - we got to a function find_father | " << endl;
        // checks right branch
        if (val_of_son > node_ptr->m_data) {
            if ((node_ptr->m_ptr_right != nullptr) && (node_ptr->m_ptr_right->m_data == val_of_son)) {
                //cout << "find_father - found the father in a right branch | " << endl;
                return node_ptr;
            }

            else if (node_ptr->m_ptr_right != nullptr) {
                //cout << "find_father - didn't find the father in a right branch, continue | " << endl;
                return find_father(node_ptr->m_ptr_right, val_of_son);
            }
        }

            // checks left branch
        else if (val_of_son < node_ptr->m_data) {
            //cout << "find_father - found the father in a left branch | " << endl;
            if ((node_ptr->m_ptr_left != nullptr) && (node_ptr->m_ptr_left->m_data == val_of_son)) {
                //cout << "i found a father of the left son and it is a " << node_ptr->m_data << endl;
                return node_ptr;
            }

            else if (node_ptr->m_ptr_right != nullptr) {
                //cout << "find_father - didn't find the father in a left branch, continue | " << endl;
                return find_father(node_ptr->m_ptr_left, val_of_son);
            }
        }

            // we tried to find a father of a root and there isn't any
        else {
            //cout << "find_father - didn't find the father because there is no father | " << endl;
            //cout << "we got to a root and there is no father" << endl;
            return nullptr;
        }
    }

    //the function is getting a right leaf and returns his legal father
//the function finds the father in order (or grandfather) (or grand - grand father)
    Node* distant_grandfather_inorder(Node* ptr_node, Node* ptr_node_v) {
        //cout << "distant_grandfather_inorder | got in" << endl;
        //cout << "ptr_node_v->m_data " << ptr_node_v->m_data << endl;
        if (ptr_node_v->m_ptr_father == nullptr) { //the right leaf in the edge has no father
            //cout << "distant_grandfather_inorder | ptr_node_v->m_ptr_father == nullptr" << endl;
            return nullptr;
        }

        if (ptr_node_v->m_ptr_father->m_ptr_left == ptr_node_v) {
            //cout << "distant_grandfather_inorder | ptr_node == ptr_node->m_ptr_father->m_ptr_left" << endl;
            return ptr_node_v->m_ptr_father;
        }
        else {
            //cout << "distant_grandfather_inorder | calls to recursive func" << endl;
            return distant_grandfather_inorder(ptr_node, ptr_node_v->m_ptr_father);
        }
        return nullptr; //dont suppose to get here
    }


    Node* find_next_inorder(Node* node_ptr, Node* node_ptr_v) {

        if ((node_ptr_v->m_ptr_right == nullptr) &&
            ((node_ptr_v->m_ptr_father!= nullptr) &&
             (node_ptr_v->m_ptr_father->m_ptr_left != nullptr) &&
             (node_ptr_v->m_ptr_father->m_ptr_left == node_ptr_v))) {


            //cout << "next inorder | if node_ptr_v->m_ptr_right == nullptr && node_ptr_v is a left son" << endl;
            return node_ptr_v->m_ptr_father;
        }

            // if node_ptr_v->m_ptr_right != nullptr
        else if (node_ptr_v->m_ptr_right != nullptr) {
            //cout << "next inorder | node_ptr_v->m_ptr_right != nullptr" << endl;
            return distant_son(node_ptr_v->m_ptr_right);
        }

        else {
            //cout << "next inorder | going to find distant grandfather" << endl;
            return distant_grandfather_inorder(node_ptr, node_ptr_v);
        }

        cout << "next inorder | end of function" << endl;
    }


// returns the leftmost leaf of a current node
    Node* distant_son(Node* node_ptr_v) {
        if (node_ptr_v->m_ptr_left == nullptr) {
            return node_ptr_v;
        }

        return distant_son(node_ptr_v->m_ptr_left);
    }

public:
    int acumulated_sum(Node* curr_node) {
        if (curr_node->m_ptr_father == nullptr) {
            return curr_node->getPrize();
        }
        int sum = acumulated_sum(curr_node->m_ptr_father);
        sum += curr_node->getPrize();
        return sum;
    }
    void printRankTree(const RankTree<T>& avl) {
        if (avl.ptr_main_root == nullptr) {
            cout << "The tree is empty." << endl;
            return;
        }

        cout << "RankTree:" << endl;
        printNode(avl.ptr_main_root, "", "");
    }

    void printNode(Node* node, const string& indent, const string& arrow) {
        if (node != nullptr) {
            if (node->m_ptr_right != nullptr) {
                printNode(node->m_ptr_right, indent + "     ", "  \\");
            }

            cout << indent;

            cout << arrow << "── ";

            cout << node->m_data << endl;

            if (node->m_ptr_left != nullptr) {
                printNode(node->m_ptr_left, indent + "     ", "  /");
            }
        }
    }


// ranked tree functions

// finds the closest value to min bound (returns val that is >= min)
    Node* find_closest_min(Node* curr_node, int val_to_find, int curr_min) {
        if (curr_node == nullptr) {
            return nullptr;
        }

        if ((*m_getter)(curr_node->m_data) == val_to_find) {
            return curr_node;
        }

        else if ((*m_getter)(curr_node->m_data) < val_to_find) {
            return find_closest_min(curr_node->m_ptr_right, val_to_find, curr_min);
        }

        else {
            return find_closest_min(curr_node->m_ptr_left, val_to_find, (*m_getter)(curr_node->m_data));
        }

        return nullptr;
    }

// finds the closest value to max bound (returns val that is <= max)
    Node* find_closest_max(Node* curr_node, int val_to_find, int curr_max) {
        if (curr_node == nullptr) {
            return nullptr;
        }

        if ((*m_getter)(curr_node->m_data) == val_to_find) {
            return curr_node;
        }

        else if ((*m_getter)(curr_node->m_data) < val_to_find) {
            return find_closest_max(curr_node->m_ptr_right, val_to_find, (*m_getter)(curr_node->m_data));
        }

        else {
            return find_closest_max(curr_node->m_ptr_left, val_to_find, curr_max);
        }

        return nullptr;
    }

    void add_amount(Node* curr_node, bool is_last_turn_right, int upper_bound, double amount) {
        if (curr_node == nullptr) {
            return;
        }

        else if ((*m_getter)(curr_node->m_data) == upper_bound) {
            if (is_last_turn_right) {
                curr_node->m_prize += amount;
            }
            if (curr_node->m_ptr_right != nullptr) {
                curr_node->m_ptr_right->m_prize -= amount;
            }
        }

        else if ((*m_getter)(curr_node->m_data) > upper_bound) {
            if (is_last_turn_right) {
                curr_node->m_prize -= amount;
            }
            add_amount(curr_node->m_ptr_left, false, upper_bound, amount);
        }

        else {
            if (!is_last_turn_right) {
                curr_node->m_prize += amount;
            }
            add_amount(curr_node->m_ptr_right, true, upper_bound, amount);
        }
    }



};



#endif //RECORDSCOMPANY_RANKTREE_H