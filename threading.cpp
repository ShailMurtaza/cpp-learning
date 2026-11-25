#include <chrono>
#include <cmath>
#include <iostream>
#include <thread>

using namespace std;
using namespace std::chrono;

void func() {
    double result = 0;
    for (double i = 0; i < 10000000; i += 0.1) {
        result += sin(i);
    }
    cout << result << endl;
}

int main() {
    auto start = high_resolution_clock::now();

    func();
    func();

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);

    cout << "Without Threads: " << duration.count() << endl;

    start = high_resolution_clock::now();
    thread worker1(func);
    thread worker2(func);

    worker1.join();
    worker2.join();

    end = high_resolution_clock::now();
    duration = duration_cast<microseconds>(end - start);
    cout << "With    Threads: " << duration.count() << endl;
    return 0;
}
