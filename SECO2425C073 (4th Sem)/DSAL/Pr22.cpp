#include <iostream>
using namespace std;

class heap1 {
public:
    void MAX_HEAPIFY(int a[], int i, int n) {
        int l = 2 * i, r = (2 * i + 1), largest, loc;
        largest = (l <= n && a[l] > a[i]) ? l : i;
        if (r <= n && a[r] > a[largest]) largest = r;
        if (largest != i) {
            loc = a[i];
            a[i] = a[largest];
            a[largest] = loc;
            MAX_HEAPIFY(a, largest, n);
        }
    }

    void BUILD_MAX_HEAP(int a[], int n) {
        for (int k = n / 2; k >= 1; k--) MAX_HEAPIFY(a, k, n);
    }

    void HEAPSORT(int a[], int n) {
        BUILD_MAX_HEAP(a, n);
        for (int i = n; i >= 2; i--) {
            swap(a[i], a[1]);
            MAX_HEAPIFY(a, 1, i - 1);
        }
    }

    void accept() {
        int n;
        cout << "Enter the number of students" << endl;
        cin >> n;
        int a[n];
        cout << "Enter the marks of the students " << endl;
        for (int i = 1; i <= n; i++) cin >> a[i];
        HEAPSORT(a, n);
        display(a, n);
    }

    void display(int a[], int n) {
        cout << ":::::::SORTED MARKS::::::" << endl;
        for (int i = 1; i <= n; i++) cout << a[i] << endl;
        cout << "Minimum marks obtained are:" << a[1];
        cout << "\nMaximum marks obtained are:" << a[n];
    }
};

int main() {
    heap1 h;
    h.accept();
    return 0;
}
