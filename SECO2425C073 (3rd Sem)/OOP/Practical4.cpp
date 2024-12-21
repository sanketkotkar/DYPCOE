#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Student {
private:
    string name, branch;
    int rollNo;

public:
    // Function to accept student data
    void accept() {
        cout << "Enter Student Name: ";
        getline(cin, name);
        cout << "Enter Roll No.: ";
        cin >> rollNo;
        cin.ignore();  // Clears the buffer before branch input
        cout << "Enter Branch: ";
        getline(cin, branch);
    }

    // Function to write student data to file
    void writeToFile() {
        ofstream outFile("student_info.txt", ios::app);  // Append mode
        if (outFile.is_open()) {
            outFile << "Name: " << name << "\n";
            outFile << "Roll No.: " << rollNo << "\n";
            outFile << "Branch: " << branch << "\n\n";
            outFile.close();
            cout << "\nInformation written to file successfully!" << endl;
        } else {
            cerr << "Unable to open file for writing." << endl;
        }
    }

    // Function to display data from file
    void displayFromFile() {
        ifstream inFile("student_info.txt");
        if (inFile.is_open()) {
            string line;
            cout << "\nReading from file:" << endl;
            while (getline(inFile, line)) {
                cout << line << endl;
            }
            inFile.close();
        } else {
            cerr << "Unable to open file for reading." << endl;
        }
    }
};

int main() {
    int numStudents;
    Student student;

    cout << "Enter the number of students' data you want to enter: ";
    cin >> numStudents;
    cin.ignore();  // Clears input buffer after number input

    for (int i = 0; i < numStudents; ++i) {
        cout << "\nEntering data for Student " << i + 1 << ":\n";
        student.accept();      // Accepts student data
        student.writeToFile(); // Writes student data to the file
    }

    // Display all the data from the file
    student.displayFromFile();

    return 0;
}

