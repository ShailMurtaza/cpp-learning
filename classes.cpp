#include <iostream>
#include <string>

using namespace std;

class Complex {
  private:
    double *a, *b;
    string title;

  public:
    Complex(string title) {
        a = new double;
        b = new double;
        *a = 0;
        *b = 0;
        this->title = title;
        cout << title << ": Unparameterized constructor is called" << endl;
    }
    Complex(double a, double b, string title) {
        this->a = new double;
        this->b = new double;
        *this->a = a;
        *this->b = b;
        this->title = title;
        cout << title << ": Parameterized Constructor is called" << endl;
    }

    Complex(Complex &c) {
        cout << title << ": Copy Constructor" << endl;
        this->a = new double;
        this->b = new double;
        *this->a = c.get_a();
        *this->b = c.get_b();
    }

    Complex(Complex &&c) {
        cout << c.get_title() << ": Move Constructor" << endl;
        this->a = c.a;
        this->b = c.b;
        c.a = nullptr;
        c.b = nullptr;
    }
    ~Complex() {
        cout << title << ": Destruction" << endl;
        if (a) {
            delete a;
        }
        if (b){
            delete b;
        }
    }
    void operator=(Complex &&c) {
        cout << title << ": Move Assignment Operator" << endl;
        *this->a = c.get_a();
        *this->b = c.get_b();
    }
    void operator=(const Complex &c) {
        cout << title << ": Copy Assignment Operator" << endl;
        *this->a = c.get_a();
        *this->b = c.get_b();
    }
    Complex operator+(Complex &c) {
        Complex temp{"Temp"};
        temp.set(*this->a + c.get_a(), *this->b + c.get_b());
        return temp;
    }
    double get_a() const { return *this->a; }
    double get_b() const { return *this->b; }
    string get_title() const { return this->title; }
    void print() { cout << this->title << ": Real Part: " << *this->a << " Imaginary Part: " << *this->b << endl; }
    void set(double a, double b) {
        *this->a = a;
        *this->b = b;
    }
};

int main() {
    Complex c1{"c1"};
    Complex c2{10, 20, "c2"};
    Complex c3{"c3"};
    c1 = c2;
    c2.set(1, 2);
    c1.print();
    c2.print();
    Complex c4{"c4"};
    c4 = c1 + c2 + c3;
    c4.print();
    return 0;
}
