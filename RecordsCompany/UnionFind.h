
#ifndef UNION_FIND_H
#define UNION_FIND_H

#include "Record.h"


class UnionFind{

public:

    class Group;
    class Element;

    /* UnionFind - constructor for the class*/
    UnionFind();

    /* destructor of union find */
    ~UnionFind();

    /* no copy constructor */
    UnionFind(const UnionFind& other) = delete;

    /* no assignment operator */
    UnionFind& operator=(const UnionFind& other) = delete;

    /**
     * newStock - re initialize the union find to suit with the new stock. all the previous data is deleted
     * 
     * @param records_stocks - array contains the stocks of each record
     * @param number_of_records - the number of records of the stock
     * 
     * @exception std::bac_alloc exception might be thrown in case allocation failed
    */
    void newStock(int* records_stocks,int number_of_records);

    /**
     * putOn - puts groupUp on top of groupUnder (unions the groups)
     * 
     * @param groupUp - the group to put above the groupUnder
     * @param groupUnder - the group to put under the groupUp
     * @return
     * returns the unioned group after putting groupUp on top of groupUnder
    */
    Group* putOn(Group* groupUp,Group* groupUnder);

    /**
     * find - finds the group of the given element
     * 
     * @param recordID - the recordID of which we want to find his group
     * @return
     * returns the group the given element is inside
    */
    Group* find(int recordID) const;

    /**
     * getHeight - gets the height of the record
     * 
     * @param recordID - the recordID of which we want the height
     * @return
     * returns the height of the record
    */
    int getHeight(int recordID) const;

    /**
     * getRecord - gets the record with the recordID given as argument
     * 
     * @param recordID - the recordID of the record we want to get
     * @return
     * returns pointer to the record with the given recordID
    */
    Record* getRecord(int recordID) const;

    /**
     * getSize - gets the size of the union find
     * 
     * @return
     * returns the number of elements in the union find
    */
    int getSize() const;

private:

    Element* m_elements;
    Group* m_groups;
    int m_size;

    /* Initial size of the union find */
    static const int INITIAL_SIZE = 0;

};


class UnionFind::Group {

public:

    /**
     * Group - constructor for the class
    */
    Group(): m_root(nullptr), m_height(INITIAL_HEIGHT),
        m_column(INITIAL_COLUMN),m_elementsNum(INITIAL_ELEMENTS_NUM) {}


    /* no copy constructor */
    Group(const Group& other) = delete;

    /* no assignemnt operator */
    Group& operator=(const Group& other) = delete;


    /**
     * getRoot - gets the root of the group
     * 
     * @return
     * returns the root of the group
    */
    Element* getRoot() const{
        return m_root;
    }

    /**
     * getHeight - gets the height of the group
     * 
     * @return returns the height of the group
    */
    int getHeight() const{
        return m_height;
    }

    /**
     * getColumn - gets the column of the group
     * 
     * @return
     * returns the column of the group
    */
    int getColumn() const{
        return m_column;
    }
    

    /**
     * getElementsNum - gets the number of elements in the group
     * 
     * @return
     * returns the number of elements in the group
    */
    int getElementsNum() const{
        return m_elementsNum;
    }

    /**
     * setRoot - sets the element root of the group
     * 
     * @param root - the root of the group
    */
    void setRoot(Element* root){
        m_root = root;
    }

    /**
     * setHeight - sets height of the group
     * 
     * @param height - the height of the group
    */
    void setHeight(int height){
        m_height = height;
    }

    void setColumn(int column){
        m_column = column;
    }

    /**
     * setElemensNum - sets the number of elements in the group
     * 
     * @param elementsNum - the number of elements in the group
    */
    void setElementsNum(int elementsNum){
        m_elementsNum = elementsNum;
    }

private:
    Element* m_root;
    int m_height;
    int m_column;
    int m_elementsNum;
    
    friend class UnionFind;

    /* initial height of empty group */
    static const int INITIAL_HEIGHT = 0;

    /* initial column of empty group */
    static const int INITIAL_COLUMN = -1;

    /* initial elements number of empty group */
    static const int INITIAL_ELEMENTS_NUM = 0;

    /* size of group with 1 element */
    static const int UNIT_SIZE = 1;
};



class UnionFind::Element {

public:
    /**
     * Element - constructor for the class
    */
    Element(): m_record(nullptr),m_group(nullptr),
        m_next(nullptr),m_relativeHeight(INITIAL_RELATIVE_HEIGHT) {}
        
    /**
     *  ~Elemennt - destructor for the class
     */
    ~Element() {
        delete m_record;
    }

    /* no copy constructor */
    Element(const Element& other);

    /* no assignment operator */
    Element& operator=(const Element& other) = delete;

    /**
     * getRecord - gets the element of the class
     * 
     * @return
     * returns the record
    */
    Record* getRecord() const{
        return m_record;
    }

    /**
     * getGroup - gets the group the element is inside
     * 
     * @return
     * returns the group of which the element is in
    */
    Group* getGroup() const{
        return m_group;
    }

    /**
     * getNext - gets the next element in the road to root
     * 
     * @return
     * returns the next element
    */
    Element* getNext() const{
        return m_next;
    }

    /**
     * getRelativeHeight - gets the relative height of the element
     * 
     * @return
     * returns the relative height of the element
    */
    int getRelativeHeight() const{
        return m_relativeHeight;
    }

    /**
     * setRecord - sets the record of the element
     * 
     * @param record - the record of the element
    */
    void setRecord(Record* record){
        m_record = record;
    }

    /**
     * setGroup - sets the new group of the element
     * 
     * @param group - the new group
     * 
    */
    void setGroup(Group* group){
        m_group = group;
    }

    /**
     * setNextElement - sets the next element
     * 
     * @param next - the next element
    */
    void setNextElement(Element* next){
        m_next = next;
    }

    /**
     * setRelativeHeight - sets the new relative height
     * 
     * @param relativeHeigh - the new relative height
    */
    void setRelativeHeight(int relativeHeight){
        m_relativeHeight = relativeHeight;
    }

private:

    Record* m_record;
    Group* m_group;
    Element* m_next;
    int m_relativeHeight;

    friend class UnionFind;

    /* Initial relative height */
    static const int INITIAL_RELATIVE_HEIGHT = 0;
};




#endif //UNION_FIND_H