//#include "recordsCompany.h"
#include "utilesWet2.h"
#include <string>
#include <iostream>
#include <vector>

#include "Costumer.h"
#include "hash_table.h"

using namespace std;

void print(string cmd, StatusType res);

void print(string cmd, Output_t<bool> res);

template<typename T>
void print(string cmd, Output_t<T> res);

vector<int> getRecordsStocks();


int main()
{
    // Create a hash_table of Costumer objects
    hash_table<Costumer> table;

    // Create 15 customers
    std::vector<Costumer> customers;
    for (int i = 0; i < 33; i++) {
        Costumer c(i, i + 100, i % 2 == 0);
        table.insert_to_array(c, i);
    }

    // Insert all customers to the hash_table


    for (int i = 0; i < 33; i++) {
        Costumer c(i, i + 100, i % 2 == 0);
        if (table.find(i) == nullptr) {
            cout << "Customer with id " << c.get_id() << " not found." << std::endl;
        }
    }

    // Create two more customers with different ids
    /*Costumer extraCustomer1(15, 115, true);
    Costumer extraCustomer2(16, 116, false);
    Costumer extraCustomer3(17, 117, false);

    // Insert the extra customers to the hash_table
    table.insert_to_array(extraCustomer1, extraCustomer1.get_id());
    table.insert_to_array(extraCustomer2, extraCustomer2.get_id());
    table.insert_to_array(extraCustomer3, extraCustomer3.get_id());
*/
    // Print the values of m_size and m_count_elements
    std::cout << "Size of the hash_table: (expected 64)" << table.m_size << std::endl;
    std::cout << "Number of elements in the hash_table (expected 33): " << table.m_count_elements << std::endl;

    // Check if a random customer from before can still be found
    Costumer randomCustomer1(0, 100, true);
    if (table.find(randomCustomer1.get_id())) {
        std::cout << "Customer with id " << randomCustomer1.get_id() << " found." << std::endl;
    } else {
        std::cout << "Customer with id " << randomCustomer1.get_id() << " not found." << std::endl;
    }

    Costumer randomCustomer2(7, 107, false);
    if (table.find(randomCustomer2.get_id())) {
        std::cout << "Customer with id " << randomCustomer2.get_id() << " found." << std::endl;
    } else {
        std::cout << "Customer with id " << randomCustomer2.get_id() << " not found." << std::endl;
    }
    for (int i = 0; i < 33; i++) {
        Costumer c(i, i + 100, i % 2 == 0);
        if (table.find(i) == nullptr) {
            cout << "Customer with id " << c.get_id() << " not found." << std::endl;
        }
    }

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