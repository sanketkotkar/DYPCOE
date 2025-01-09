#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Student {
    int rollno;
    string name, division, address;
    
public:
    int add() {
        cout << "Enter Student Roll No.: ";
        cin >> rollno;
        cout << "Enter Student Name: ";
        cin >> name;
        cout << "Enter Division: ";
        cin >> division;
        cout << "Enter Student Address: ";
        cin >> address;

        fstream f;
        f.open("data.txt", ios::in);
        if (f) {
            int fileRollNo;
            string fileName, fileDivision, fileAddress;
            while (f >> fileRollNo >> fileName >> fileDivision >> fileAddress) {
                if (fileRollNo == rollno) {
                    cout << "Roll No. Already Exists.\n";
                    f.close();
                    return -1;
                }
            }
        }

        f.close();
        f.open("data.txt", ios::app); // Append new record
        f << rollno << " " << name << " " << division << " " << address << endl;
        f.close();
        cout << "Record added successfully.\n";
        return 0;
    }

    void del() {
        fstream f;
        f.open("data.txt", ios::in);
        if (!f) {
            cout << "File not found.\n";
            return;
        }

        cout << "Enter Roll No. to delete a record: ";
        cin >> rollno;

        fstream tempFile;
        tempFile.open("temp.txt", ios::out);
        int fileRollNo;
        string fileName, fileDivision, fileAddress;
        bool found = false;

        while (f >> fileRollNo >> fileName >> fileDivision >> fileAddress) {
            if (fileRollNo != rollno) {
                tempFile << fileRollNo << " " << fileName << " " << fileDivision << " " << fileAddress << endl;
            } else {
                found = true;
            }
        }

        f.close();
        tempFile.close();

        if (found) {
            remove("data.txt");
            rename("temp.txt", "data.txt");
            cout << "Record deleted successfully.\n";
        } else {
            cout << "Record not found.\n";
        }
    }

    void display() {
        fstream f;
        f.open("data.txt", ios::in);
        if (!f) {
            cout << "No records to display.\n";
            return;
        }

        cout << "All Student Records:\n";
        int fileRollNo;
        string fileName, fileDivision, fileAddress;
        while (f >> fileRollNo >> fileName >> fileDivision >> fileAddress) {
            cout << "Roll No.: " << fileRollNo << "\n";
            cout << "Name: " << fileName << "\n";
            cout << "Division: " << fileDivision << "\n";
            cout << "Address: " << fileAddress << "\n";
            cout << "--------------------------\n";
        }
        f.close();
    }

    void search() {
        fstream f;
        f.open("data.txt", ios::in);
        if (!f) {
            cout << "No records to search.\n";
            return;
        }

        int searchRollNo;
        cout << "Enter Roll No. to search: ";
        cin >> searchRollNo;

        bool found = false;
        int fileRollNo;
        string fileName, fileDivision, fileAddress;
        while (f >> fileRollNo >> fileName >> fileDivision >> fileAddress) {
            if (fileRollNo == searchRollNo) {
                found = true;
                cout << "Student Data:\n";
                cout << "Roll No.: " << fileRollNo << "\n";
                cout << "Name: " << fileName << "\n";
                cout << "Division: " << fileDivision << "\n";
                cout << "Address: " << fileAddress << "\n";
                break;
            }
        }

        if (!found) {
            cout << "Record not found.\n";
        }

        f.close();
    }
};

int main() {
    Student s;
    int ch;

    do {
        cout << "\nMenu:\n";
        cout << "1. Add Student Data\n";
        cout << "2. Remove a Student Record\n";
        cout << "3. Display All Students\n";
        cout << "4. Search Student Data by Roll No.\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> ch;

        switch (ch) {
            case 1:
                s.add();
                break;
            case 2:
                s.del();
                break;
            case 3:
                s.display();
                break;
            case 4:
                s.search();
                break;
            case 5:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (ch != 5);

    return 0;
}

