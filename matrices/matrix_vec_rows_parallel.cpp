#include <cmath>
#include <iomanip>
#include <iostream>
#include <thread>
#include <vector>

// #define DIM 20000
#define ROWS 4000
#define COLS 4000
using namespace std;
using Matrix = vector<vector<float>>;

void init(Matrix &matrix_a, Matrix &matrix_b, Matrix &matrix_c) {
    const int rows_a = matrix_a.size();
    const int cols_a = matrix_a[0].size();
    const int rows_b = matrix_b.size();
    const int cols_b = matrix_b[0].size();
    const int rows_c = matrix_c.size();
    const int cols_c = matrix_c[0].size();
    for (int i = 0; i < rows_a; i++) {
        for (int j = 0; j < cols_a; j++) {
            matrix_a[i][j] = i * cols_a + (j + 1);
        }
    }
    for (int i = 0; i < rows_b; i++) {
        for (int j = 0; j < cols_b; j++) {
            matrix_b[i][j] = i * cols_a + (j + 1);
        }
    }
    for (int i = 0; i < rows_c; i++) {
        for (int j = 0; j < cols_c; j++) {
            matrix_c[i][j] = 0;
        }
    }
}

void multiply(const Matrix &matrix_a, const Matrix &matrix_b, Matrix &matrix_c, int row_start, int row_end) {
    if (!matrix_a.size() || !matrix_a[0].size() || !matrix_b.size() || !matrix_b[0].size())
        return;
    const int rows_a = matrix_a.size();
    const int cols_a = matrix_a[0].size();
    const int rows_b = matrix_b.size();
    const int cols_b = matrix_b[0].size();
    const int rows_c = matrix_c.size();
    const int cols_c = matrix_c[0].size();
    if (cols_a != rows_b || rows_c != rows_a || cols_c != cols_b) {
        cout << "Invalid matrix layout for multiplicaiton" << endl;
        return;
    }
    for (int i = row_start; i <= row_end; i++) {
        for (int j = 0; j < cols_a; j++) {
            for (int k = 0; k < cols_b; k++) {
                matrix_c[i][k] += matrix_a[i][j] * matrix_b[j][k];
            }
        }
    }
}

void parallelize_multiply(const Matrix &matrix_a, const Matrix &matrix_b, Matrix &matrix_c) {
    if (ROWS <= 0)
        return;
    // get number of total threads in system
    int system_threads = thread::hardware_concurrency();
    if (system_threads == 0) {
        system_threads = 1;
    }
    // if rows are less than system_threads then just use rows as number of threads to create
    const int num_threads = ROWS < system_threads ? ROWS : system_threads;
    //  calculate how many rows should to allocated to each thread
    const int rows_per_thread = floor(ROWS / num_threads);
    const int extra_rows = ROWS % num_threads;

    vector<thread> threads;
    threads.reserve(num_threads + (extra_rows ? 1 : 0));
    cout << "THREADS: " << num_threads << endl;

    int start_col, end_col;
    for (int i = 0; i < num_threads; i++) {
        start_col = i * rows_per_thread;
        end_col = start_col + rows_per_thread - 1;
        threads.emplace_back(multiply, cref(matrix_a), cref(matrix_b), ref(matrix_c), start_col, end_col);
    }
    // if there are extra rows then create a new thread to calculate them too
    if (extra_rows) {
        start_col = rows_per_thread * num_threads;
        end_col = start_col + extra_rows - 1;
        threads.emplace_back(multiply, cref(matrix_a), cref(matrix_b), ref(matrix_c), start_col, end_col);
    }
    for (auto &t : threads) {
        t.join();
    }
}

void print(Matrix &matrix) {
    for (int i = 0; i < matrix.size(); ++i) {
        std::cout << "║ ";
        for (int j = 0; j < matrix[0].size(); ++j) {
            std::cout << std::fixed << std::setprecision(2) << std::setw(6) << matrix[i][j] << " ";
        }
        std::cout << "    ║\n";
    }
    std::cout << endl;
}

int main() {
    cout << "RUNNING!" << endl;
    Matrix matrix_a(ROWS, vector<float>(COLS));
    Matrix matrix_b(ROWS, vector<float>(COLS));
    Matrix matrix_c(ROWS, vector<float>(COLS));
    init(matrix_a, matrix_b, matrix_c);
    cout << "Initialized!" << endl;
    parallelize_multiply(matrix_a, matrix_b, matrix_c);
    // multiply(matrix_a, matrix_b, matrix_c, 0, ROWS - 1);
    /*
    print(matrix_a);
    print(matrix_b);
    print(matrix_c);
     */
}
