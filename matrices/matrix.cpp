#include <cmath>
#include <iomanip>
#include <iostream>

#define DIM 10000
using namespace std;

void init(float **matrix_a, float **matrix_b, float **matrix_c) {
    for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < DIM; j++) {
            matrix_a[i][j] = sin(i + j);
            matrix_b[i][j] = sin(i - j);
            matrix_c[i][j] = 0;
        }
    }
}

void add(float const *const *const matrix_a, float const *const *const matrix_b, float *const *const matrix_c) {
    for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < DIM; j++) {
            matrix_c[i][j] = matrix_a[i][j] + matrix_b[i][j];
        }
    }
}

/*
void test(float **const matrix) {
    matrix = new float *[DIM];
    matrix[0] = new float[DIM];
    matrix[0][0] = 10;
}
*/

void print(float **matrix) {
    for (int i = 0; i < DIM; ++i) {
        std::cout << "║ ";
        for (int j = 0; j < DIM; ++j) {
            std::cout << std::fixed << std::setprecision(2) << std::setw(6) << matrix[i][j] << " ";
        }
        std::cout << "    ║\n";
    }
}

int main() {
    float **matrix_a;
    matrix_a = new float *[DIM];
    float **matrix_b = new float *[DIM];
    float **matrix_c = new float *[DIM];
    for (int i = 0; i < DIM; i++) {
        matrix_a[i] = new float[DIM];
        matrix_b[i] = new float[DIM];
        matrix_c[i] = new float[DIM];
    }
    init(matrix_a, matrix_b, matrix_c);
    add(matrix_a, matrix_b, matrix_c);
    /*
    print(matrix_a);
    print(matrix_b);
    print(matrix_c);
    */
}
