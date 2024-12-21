#include <iostream>
#include <vector>
using namespace std;

template <typename T>
void sort(T arr[], int n) 
{
    int min;
    for (int i = 0; i < n - 1; i++) 
    {
        min = i;
        for (int j = i + 1; j < n; j++) 
        {
            if (arr[min] > arr[j]) 
            { 
                min = j;
            }
        }
        // Swap elements
        T temp = arr[i];
        arr[i] = arr[min];
        arr[min] = temp;
    }
    // Output the sorted array
    for (int i = 0; i < n; i++) 
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    int ch, n;
    do 
    {
        cout << "\n\nMenu" << endl;
        cout << "1. Sorting of int array" << endl;
        cout << "2. Sorting of float array" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter Your Choice: ";
        cin >> ch;
        
        if (ch == 3) {
            cout << "Exiting..." << endl;
            break;
        }

        cout << "Enter Size of array: ";
        cin >> n;

        if (ch == 1) 
        {
            vector<int> arr(n); // Use vector for dynamic sizing
            cout << "Enter " << n << " integers:" << endl;
            for (int i = 0; i < n; i++) 
            {
                cin >> arr[i];
            }
            sort<int>(arr.data(), n);  // Pass array to sort function
        } 
        else if (ch == 2) 
        {
            vector<float> arr2(n); // Use vector for dynamic sizing
            cout << "Enter " << n << " floats:" << endl;
            for (int i = 0; i < n; i++) 
            {
                cin >> arr2[i];
            }
            sort<float>(arr2.data(), n);  // Pass array to sort function
        } 
        else {
            cout << "Invalid choice. Please select 1, 2, or 3." << endl;
        }

    } while (ch != 3);

    return 0;
}
