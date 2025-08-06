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

    vector<string> data(nFrames), received(nFrames, "");
    for (int i = 0; i < nFrames; i++) {
        cout << "Data for frame " << i + 1 << ": ";
        cin >> data[i];
    }

    int i = 0;
    while (i < nFrames) {
        for (int j = i; j < i + windowSize && j < nFrames; j++) {
            if (received[j] == "") {
                cout << "Sending Frame " << j + 1;
                if (randomTrueFalse()) {
                    cout << " -> Received\n";
                    received[j] = data[j];
                } else {
                    cout << " -> Lost\n";
                }
            }
        }
        while (i < nFrames && received[i] != "") i++;
    }

    cout << "\nAll frames received:\n";
    for (int k = 0; k < nFrames; k++)
        cout << "Frame " << k + 1 << ": " << received[k] << "\n";
}
