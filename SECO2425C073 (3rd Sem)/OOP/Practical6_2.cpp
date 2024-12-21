#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class ItemRecord {
public:
    string itemName;
    int itemCode;
    float itemCost;
    int quantity;

    // Constructor
    ItemRecord(string name, int code, float cost, int qty) {
        itemName = name;
        itemCode = code;
        itemCost = cost;
        quantity = qty;
    }
};

// Compare function to sort by item name
bool Compare(ItemRecord i1, ItemRecord i2) {
    return i1.itemName < i2.itemName;
}

int main() {
    vector<ItemRecord> items;
    
    // Adding sample items
    ItemRecord item1("Laptop", 101, 75000.5, 5);
    ItemRecord item2("Mobile", 102, 15000.75, 10);
    ItemRecord item3("Tablet", 103, 25000.25, 8);
    
    items.push_back(item1);
    items.push_back(item2);
    items.push_back(item3);
    
    string name;
    int ch;
    do {
        cout << "\nMenu\n1. Sort the list\n2. Search by name\n3. Display records\nPress any other key to exit: ";
        cin >> ch;

        if (ch == 1) {
            sort(items.begin(), items.end(), Compare);
            cout << "List sorted by item name.\n";
            // Display sorted list
            for (auto i : items) {
                cout << i.itemName << " " << i.itemCode << " " << i.itemCost << " " << i.quantity << endl;
            }
        }
        else if (ch == 2) {
            cout << "Enter the item name: ";
            cin >> name;
            bool found = false;
            for (auto i : items) {
                if (i.itemName == name) {
                    cout << "Item found: " << i.itemName << ", Code: " << i.itemCode 
                         << ", Cost: " << i.itemCost << ", Quantity: " << i.quantity << endl;
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "Item not found\n";
            }
        }
        else if (ch == 3) {
            cout << "Displaying records:\n";
            for (auto i : items) {
                cout << i.itemName << " " << i.itemCode << " " << i.itemCost << " " << i.quantity << endl;
            }
        }
        else {
            cout << "Exiting...\n";
            break;
        }

    } while (ch >= 1 && ch <= 3);  // Exit when any other key is pressed

    return 0;
}
