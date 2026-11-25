#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
  string line;
  ifstream file("test.txt");
  while (getline(file, line)) {
    cout << line << ", ";
  }
  cout << endl;

  vector<int> numbers;
  file.clear();
  file.seekg(0);
  int x;

  while (file >> x) {
    numbers.push_back(x);
  }
  sort(numbers.begin(), numbers.end());

  for (size_t i = 0; i < numbers.size(); i++) {
    cout << numbers.at(i);
    if (i < numbers.size() - 1)
      cout << ", ";
  }

  file.close();
  cout << endl;
}
