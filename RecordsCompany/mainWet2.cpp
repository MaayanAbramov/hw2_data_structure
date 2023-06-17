//#include "recordsCompany.h"
#include "utilesWet2.h"
#include <string>
#include <iostream>
#include <vector>

#include "Customer.h"
#include "hash_table.h"
#include "UnionFind.h"
#include "AvlTree.h"
#include "RankTree.h"
#include "Record.h"

using namespace std;

void print(string cmd, StatusType res);

void print(string cmd, Output_t<bool> res);

template<typename T>
void print(string cmd, Output_t<T> res);

vector<int> getRecordsStocks();


int main()
{
    // Create records
    Record* record1 = new Record(0, 100, 0);
    Record* record2 = new Record(1, 200, 0);
    Record* record3 = new Record(2, 300, 0);
    Record* record4 = new Record(3, 400, 0);
    Record* record5 = new Record(4, 500, 0);
    Record* record6 = new Record(5, 600, 0);
    Record* record7 = new Record(6, 700, 0);

    Union_Find::Node* node1 = new Union_Find::Node();
    node1->m_record = record1;
    Union_Find::Node* node5 = new Union_Find::Node();
    node1->m_record = record5;

    // Create Union_Find object
    Union_Find unionFind;

    // Create and initialize the first group with 4 records
    Union_Find::GroupOfNodes* group1 = new Union_Find::GroupOfNodes();
    group1->set_num_of_members(4);
    group1->set_height(1500);
    group1->set_column(record3->get_r_id());
    group1->set_root(node1);

    // Create and initialize the second group with 3 records
    Union_Find::GroupOfNodes* group2 = new Union_Find::GroupOfNodes();
    group2->set_num_of_members(3);
    group2->set_height(1800);
    group2->set_column(record7->get_r_id());
    group2->set_root(node5);

    // Union the two groups
    Union_Find::GroupOfNodes* mergedGroup = unionFind.Union(group1, group2);

    // Print details of the merged group
    std::cout << "Merged Group Details:" << std::endl;
    std::cout << "Number of Members: " << mergedGroup->get_num_of_members() << std::endl;
    std::cout << "Height: " << mergedGroup->get_height() << std::endl;
    std::cout << "Column: " << mergedGroup->get_column() << std::endl;
    std::cout << "Root Record ID: " << mergedGroup->get_root()->get_record()->get_r_id() << std::endl;

    // Clean up memory
    delete record1;
    delete record2;
    delete record3;
    delete record4;
    delete record5;
    delete record6;
    delete record7;

    delete group1;
    delete group2;

    /*
    string op;
    RecordsCompany *test_obj = new RecordsCompany();
    while (cin >> op)
    {

        // check operation
        if (!op.compare("newMonth"))
        {
            // get params
            vector<int> stocks_vec = getRecordsStocks();

            // call function
            print(op, test_obj->newMonth(&stocks_vec[0], stocks_vec.size()));
        }
        else if (!op.compare("addCostumer"))
        {
            int c_id, phone;
            cin >> c_id; cin >> phone;

            print(op, test_obj->addCostumer(c_id, phone));
        }
        else if(!op.compare("getPhone"))
        {
            int c_id;
            cin >> c_id;

            print(op, test_obj->getPhone(c_id));
        }
        else if(!op.compare("makeMember"))
        {
            int c_id;
            cin >> c_id;

            print(op, test_obj->makeMember(c_id));
        }
        else if(!op.compare("isMember"))
        {
            int c_id;
            cin >> c_id;

            print(op, test_obj->isMember(c_id));
        }
        else if(!op.compare("buyRecord"))
        {
            int c_id, r_id;
            cin >> c_id; cin >> r_id;

            print(op, test_obj->buyRecord(c_id, r_id));
        }
        else if(!op.compare("addPrize"))
        {
            int c_id1, c_id2, amount;
            cin >> c_id1; cin >> c_id2; cin >> amount;

            print(op, test_obj->addPrize(c_id1, c_id2, amount));
        }
        else if(!op.compare("getExpenses"))
        {
            int c_id;
            cin >> c_id;

            print(op, test_obj->getExpenses(c_id));
        }
        else if(!op.compare("putOnTop"))
        {
            int r_id1, r_id2;
            cin >> r_id1; cin >> r_id2;

            print(op, test_obj->putOnTop(r_id1, r_id2));
        }
        else if(!op.compare("getPlace"))
        {
            int r_id, column, hight;
            cin >> r_id;
            StatusType res = test_obj->getPlace(r_id, &column, &hight);
            if (res != StatusType::SUCCESS)
            {
                print(op, res);
            }
            else
            {
                cout << op << ": column=" << column << ", hight=" << hight << endl;
            }
        }
        else
        {
            cout << "Unknown command: " << op << endl;
            return -1;
        }
        // Verify no faults
        if (cin.fail())
        {
            cout << "Invalid input format " << endl;
            return -1;
        }
    }
    delete test_obj;*/
    return 0;
}


static const char *StatusTypeStr[] =
        {
                "SUCCESS",
                "ALLOCATION_ERROR",
                "INVALID_INPUT",
                "FAILURE",
                "ALREADY_EXISTS",
                "DOESNT_EXISTS"
        };

void print(string cmd, StatusType res)
{
    cout << cmd << ": " << StatusTypeStr[(int) res] << endl;
}


void print(string cmd, Output_t<bool> res)
{
    if (res.is_res())
    {
        if (res.ans())
            cout << cmd << ": True" << endl;
        else
            cout << cmd << ": False" << endl;
    }
    else
    {
        cout << cmd << ": " << StatusTypeStr[(int) res.status()] << endl;
    }
}


template<typename T>
void print(string cmd, Output_t<T> res)
{
    if (res.is_res())
    {
        cout << cmd << ": " << res.ans() << endl;
    }
    else
    {
        cout << cmd << ": " << StatusTypeStr[(int) res.status()] << endl;
    }
}

vector<int> getRecordsStocks()
{
    int num, len;
    cin >> len;
    char bracket;
    cin >> bracket;

    vector<int> stocks_vec = vector<int>();
    for(int i = 0; i < len; i ++)
    {
        cin >> num;
        stocks_vec.push_back(num);
    }
    cin >> bracket;

    return stocks_vec;
}