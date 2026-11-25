#include <iostream>
#include <cassert>

using namespace std;

class Vector {
  private:
    int *elem;
    unsigned int size;

  public:
    Vector(int *elem, unsigned int size) {
        this->elem = elem;
        this->size = size;
    }

    int &operator[](int i) {
        if (i > size - 1) {
            cout << "Index out of bound" << endl;
            throw out_of_range{"Vector::operator[]"};
        }
        return elem[i];
    }
    void print() {
        cout << "[";
        for (unsigned int i = 0; i != size; i++) {
            cout << elem[i];
            if (i != size - 1)
                cout << ", ";
        }
        cout << "]" << endl;
    }
};

int main() {
    int arr[]{10, 20, 30, 1};
    Vector v{arr, sizeof(arr) / sizeof(int)};
    v.print();
    cout << v[4];
    return 0;
}
