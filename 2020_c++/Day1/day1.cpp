#include <array>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unordered_set>
#include <vector>

namespace {
constexpr int sum = 2020;
std::vector<int> data;
std::unordered_set<int> complements;

std::array<int, 2> FindTwoNumbers() {
  for (auto valueAtIndex : data) {
    if (complements.find(valueAtIndex) != complements.end()) {
      return std::array<int, 2>{valueAtIndex, sum - valueAtIndex};
    }

    complements.insert(sum - valueAtIndex);
  }

  return {};
}
} // namespace

int main() {

  int num;

  auto fp = fopen("input.txt", "r");

  while (fscanf(fp, " %d", &num) == 1) {
    data.push_back(num);
  }

  const auto result = FindTwoNumbers();
  if (result.size() == 2) {
    std::cout << "Numbers found " << result[0] << "::" << result[1] << "\n";
    std::cout << result[0] * result[1];
  }
  return 0;
}