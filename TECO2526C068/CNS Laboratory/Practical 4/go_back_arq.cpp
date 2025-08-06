#include <iostream>
#include <vector>
#include <random>
using namespace std;

bool randomTrueFalse() {
    static random_device rd;
    static mt19937 gen(rd());
    static uniform_int_distribution<> dis(0, 1);
    return dis(gen) == 1;
}

int main() {
    int nFrames, windowSize;
    cout << "Enter number of frames: ";
    cin >> nFrames;
    cout << "Enter window size: ";
    cin >> windowSize;

    vector<string> data(nFrames);
    for (int i = 0; i < nFrames; i++) {
        cout << "Data for frame " << i + 1 << ": ";
        cin >> data[i];
    }

    int i = 0;
    while (i < nFrames) {
        bool errorOccurred = false;
        for (int j = i; j < i + windowSize && j < nFrames; j++) {
            cout << "Sending Frame " << j + 1;
            if (randomTrueFalse()) {
                cout << " -> Received\n";
            } else {
                cout << " -> Lost\n";
                errorOccurred = true;
                break;
            }
        }
        if (errorOccurred) {
            cout << "Resending from Frame " << i + 1 << "\n";
        } else {
            i += windowSize;
        }
    }
}
