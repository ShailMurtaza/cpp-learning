#include <iostream>
using namespace std;

class my_complex {
  private:
    double real;
    double img;

  public:
    my_complex(double a, double b) {
        real = a;
        img = b;
    }
    my_complex() {
        real = 0;
        img = 0;
    }
    my_complex &operator+=(my_complex z) {
        real += z.real;
        img += z.img;
        return *this;
    }
    my_complex &operator-=(my_complex z) {
        real -= z.real;
        img -= z.img;
        return *this;
    }

    double get_real() { return this->real; }
    double get_img() { return this->img; }
    void print() { cout << real << ", " << img << endl; }
};

my_complex operator+(my_complex a, my_complex b) {
    a.print();
    return a += b;
}

int main() {
    my_complex c1{10, 20};
    my_complex c2{1, 2};
    c1.print();
    c1 += c2;
    c1.print();
    my_complex c3 = c1 + c2;
    c3.print();
    return 0;
}
