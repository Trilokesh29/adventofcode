#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <deque>
#include <fstream>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

void init_population(std::string st, char sep, std::vector<int32_t> &splited) {
  std::stringstream ss(st);

  for (int num; ss >> num;) {
    splited.push_back(num);

    if (ss.peek() == sep)
      ss.ignore();
  }
}

std::tuple<uint64_t, uint64_t>
get_effiecient_position(std::vector<int32_t> &data) {

  const uint64_t max = *std::max_element(data.begin(), data.end());
  uint64_t sum_fuel_part1 = 0, sum_fuel_part2 = 0;

  for (auto position = 0; position < max; ++position) {

    uint64_t temp1 = 0, temp2 = 0;
    for (auto index = 0; index < data.size(); ++index) {
      //   cout << "position: " << position << " data: " << data[index] << "\n";
      temp1 += std::abs(data[index] - position);
      auto diff = std::abs(data[index] - position);
      temp2 += (diff * (diff + 1)) / 2;
    }

    // cout << "sum for position: " << position << " sum:" << temp << "\n";

    if (sum_fuel_part1 == 0) {
      sum_fuel_part1 = temp1;
    } else if (sum_fuel_part1 > temp1) {
      sum_fuel_part1 = temp1;
    }

    if (sum_fuel_part2 == 0) {
      sum_fuel_part2 = temp2;
    } else if (sum_fuel_part2 > temp2) {
      sum_fuel_part2 = temp2;
    }
  }

  return {sum_fuel_part1, sum_fuel_part2};
}

int main() {

  std::ifstream input("input.txt");

  std::string inp;

  std::vector<int32_t> data;

  if (input.is_open()) {
    input >> inp;
    init_population(inp, ',', data);
  }

  const auto [part1, part2] = get_effiecient_position(data);
  cout << "part1 :" << part1 << "\n";
  cout << "part2 :" << part2 << "\n";

  return 0;
}
