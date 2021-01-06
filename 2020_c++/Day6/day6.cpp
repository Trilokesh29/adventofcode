#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

std::uint32_t GetSumForAGroup(const std::vector<std::string> &aGroupInfo) {
  std::set<char> uniqueData;

  for (const auto &data : aGroupInfo) {
    uniqueData.insert(data.begin(), data.end());
  }

  return uniqueData.size();
}

std::uint32_t
CalculateSum(const std::vector<std::vector<std::string>> &aInputData) {
  std::uint32_t sum = 0;

  for (const auto &groupInfo : aInputData) {

    sum += GetSumForAGroup(groupInfo);
  }

  return sum;
}

int main() {

  std::ifstream input_file("input_test.txt");

  std::vector<std::vector<std::string>> inputData;

  if (input_file.is_open()) {
    std::string input;
    std::vector<std::string> temp;

    while (std::getline(input_file, input)) {
      if (!input.empty()) {
        temp.push_back(input);
      } else {
        inputData.push_back(temp);
        temp.clear();
      }
    }

    inputData.push_back(temp);
  }

  input_file.close();

  std::cout << "calculated sum = " << CalculateSum(inputData);

  return 0;
}