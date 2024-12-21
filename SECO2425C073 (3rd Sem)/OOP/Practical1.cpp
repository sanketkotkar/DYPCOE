#include <iostream>
using namespace std;

class Complex {
public:
    int real;
    int img;

    // Default constructor (0 + 0i)
    Complex() {
        real = 0;
        img = 0;
    }

    // Parameterized constructor
    Complex(int r, int i) {
        real = r;
        img = i;
    }

    // Overload + operator to add two complex numbers
    Complex operator+(const Complex& c) const {
        Complex temp;
        temp.real = real + c.real;
        temp.img = img + c.img;
        return temp;
    }

    // Overload * operator to multiply two complex numbers
    Complex operator*(const Complex& c) const {
        Complex temp;
        temp.real = real * c.real - img * c.img;
        temp.img = real * c.img + img * c.real;
        return temp;
    }

    // Overload >> operator to input a complex number
    friend istream& operator>>(istream& input, Complex& c) {
        cout << "Enter Real part: ";
        input >> c.real;
        cout << "Enter Imaginary part: ";
        input >> c.img;
        return input;
    }

    // Overload << operator to output a complex number
    friend ostream& operator<<(ostream& output, const Complex& c) {
        output << c.real;
        if (c.img >= 0) {
            output << "+" << c.img << "i"; // Print '+' if img is non-negative
        } else {
            output << c.img << "i"; // Just print if img is negative
        }
        return output;
    }
};

int main() {
    Complex c1, c2;

    // Input two complex numbers
    cin >> c1 >> c2;

    // Add the two complex numbers
    Complex sum = c1 + c2;

    // Multiply the two complex numbers
    Complex product = c1 * c2;

    // Output the sum and product
    cout << "Sum: " << sum << endl;
    cout << "Product: " << product << endl;

    return 0;
}

