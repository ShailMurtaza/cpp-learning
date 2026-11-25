#include <iostream>
#include <ostream>

using namespace std;

int square_square(int a) {
    a *= a;
    return a * a;
}

int test(const int &a) { return a; }

int main() {
    double a{3.4};
    cout << "a = " << a << endl;
    // int b{a};
    int c = square_square(b);
    cout << "Square of Square of b = " << b << " is " << c << endl;

    cout << "Printing arr" << endl;
    int arr[] = {1, 2, 3, 10, 20, 30};
    for (auto x : arr) {
        cout << x << " ";
    }
    cout << endl;

    cout << "Testing Enums" << endl;
    enum Type { string, number };
    enum class Type2 { string, number };
    Type enum1 = string;
    Type enum2 = number;
    cout << "enum1: " << enum1 << " enum2: " << enum2 << endl;

    Type2 type2_enum1 = Type2::string;
    Type2 type2_enum2 = Type2::number;
    cout << "enum1: " << static_cast<int>(type2_enum1) << " enum2: " << static_cast<int>(type2_enum2) << endl;

    int x = 5;
    int &ref{x};
    int *ref2 = &x;
    // x = 10;
    cout << "Ref: " << ref << " Ref2: " << *ref2 << endl;
    test(x);
    return 0;
}
