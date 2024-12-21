//Write C++ program using STL for sorting and searching user defined records such as personal records (Name, DOB, Telephone number etc) using vector container.

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class PersonalRecord {
public:
    string name;
    int dob;

    PersonalRecord(string n, int d) {
        name = n;
        dob = d;
    }
};

bool Compare(PersonalRecord p1, PersonalRecord p2) {
    return p1.name < p2.name;  // Sorting by name
}

int main() {
    vector<PersonalRecord> record;
    PersonalRecord p1("om", 12);
    PersonalRecord p2("yash", 14);
    PersonalRecord p3("amit", 14);
    record.push_back(p1);
    record.push_back(p2);
    record.push_back(p3);
    
    string name;
    int ch;
    do {
        cout << "\nMenu\n1. Sort the list\n2. Search by name\n3. Display records\nPress any other key to exit: ";
        cin >> ch;

        if (ch == 1) 
        {
            sort(record.begin(), record.end(), Compare);
            cout << "List sorted by name.\n";
            // Display sorted list
            for (auto r : record) {
                cout << r.name << " " << r.dob << endl;
            }
        }
        else if (ch == 2) 
        {
            cout << "Enter the name: ";
            cin >> name;
            bool found = false;
            for (auto r : record) 
            {
                if (r.name == name) 
                {
                    cout << "Record found: " << r.name << ", DOB: " << r.dob << endl;
                    found = true;
                    break;
                }
            }
            if (!found) 
            {
                cout << "Record not found\n";
            }
        }
        else if (ch == 3) 
        {
            cout << "Displaying records:\n";
            for (auto r : record) 
            {
                cout << r.name << " " << r.dob << endl;
            }
        }
        else {
            cout << "Exiting...\n";
            break;
        }

    } while (ch >= 1 && ch <= 3);  // Exit when any other key is pressed

    return 0;
}
