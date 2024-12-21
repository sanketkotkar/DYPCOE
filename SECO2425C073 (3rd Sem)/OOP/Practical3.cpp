#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

class Publication {
protected:
    string title;
    float price;

public:
    Publication() {
        title = "Unknown";
        price = 0.0;
    }

    void setData() {
        cout << "\nEnter Title: ";
        cin.ignore();
        getline(cin, title);
        cout << "Enter Price: ";
        cin >> price;

        if (price < 0) {
            throw invalid_argument("Price cannot be negative.");
        }
    }

    void displayData() const {
        cout << "\nTitle: " << title << "\nPrice: $" << price;
    }
};

class Book : public Publication {
private:
    int pageCount;

public:
    Book() {
        pageCount = 0;
    }

    void setData() {
        try {
            Publication::setData();
            cout << "Enter Page Count: ";
            cin >> pageCount;

            if (pageCount < 0) {
                throw invalid_argument("Page count cannot be negative.");
            }
        } catch (...) {
            resetData();
            throw; // Rethrow exception for external handling
        }
    }

    void displayData() const {
        Publication::displayData();
        cout << "\nPage Count: " << pageCount << " pages";
    }

    void resetData() {
        title = "Unknown";
        price = 0.0;
        pageCount = 0;
        cout << "Data reset to default values.\n";
    }
};

class Tape : public Publication {
private:
    float playTime;

public:
    Tape() {
        playTime = 0.0;
    }

    void setData() {
        try {
            Publication::setData();
            cout << "Enter Play Time (in minutes): ";
            cin >> playTime;

            if (playTime < 0) {
                throw invalid_argument("Play time cannot be negative.");
            }
        } catch (...) {
            resetData();
            throw; // Rethrow exception for external handling
        }
    }

    void displayData() const {
        Publication::displayData();
        cout << "\nPlay Time: " << playTime << " minutes";
    }

    void resetData() {
        title = "Unknown";
        price = 0.0;
        playTime = 0.0;
        cout << "Data reset to default values.\n";
    }
};

int main() {
    Book book;
    Tape tape;

    cout << "Enter details for the book:\n";
    book.setData();

    cout << "\nEnter details for the tape:\n";
    tape.setData();

    cout << "\nDisplaying all publication details:\n";

    cout << "\nBook Details:";
    book.displayData();

    cout << "\n\nTape Details:";
    tape.displayData();

    return 0;
}
