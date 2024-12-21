//Write a program in C++ to use map associative container. The keys will be the names of states and the values will be the populations of the states. When the program runs, the user is prompted to type the name of a state. The program then looks in the map, using the state name as an index and returns the population of the state.
#include <iostream>
#include <map>
using namespace std;

int main()
{
    // Initialize the map with states and their populations
    map<string, int> stateData = {
        {"Maharashtra", 112374333},
        {"Gujarat", 60439692},
        {"Rajasthan", 68548437},
        {"Karnataka", 61095297},
        {"Punjab", 27743338}
    };

    string state;
    cout << "Enter State: ";
    cin >> state;

    // Check if the state exists in the map and output the population
    auto it = stateData.find(state); // Use map's find method to search by key

    if (it != stateData.end()) {
        // If found, print the state's population
        cout << "State: " << it->first << " Population: " << it->second << endl;
    } else {
        // If not found, print a message
        cout << "State not found!" << endl;
    }

    return 0;
}
