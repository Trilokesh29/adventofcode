#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <unordered_set>
#include <vector>

// part1:- count the number of questions to which anyone answered "yes"
// part2:- count the number of questions to which everyone in a group answered
// "yes"

std::uint32_t GetSumForAGroup(const std::vector<std::string> &aGroupInfo) {
  std::unordered_set<char> uniqueData;

  for (const auto &data : aGroupInfo) {
    uniqueData.insert(data.begin(), data.end());
  }

  return uniqueData.size();
}

std::uint32_t CalculateSum_Of_Unique_Yes(
    const std::vector<std::vector<std::string>> &aInputData) {
  std::uint32_t sum = 0;

  for (const auto &groupInfo : aInputData) {

    sum += GetSumForAGroup(groupInfo);
  }

  return sum;
}

uint32_t GetCount_Yes_From_Everyone_In_A_Group(
    const std::vector<std::vector<std::string>> &inputData) {
  uint32_t count = 0;
  std::string reference;
  for (auto &group : inputData) {
    reference = group[0];
    for (int i = 1; i < group.size(); ++i) {
      reference.erase(std::remove_if(reference.begin(), reference.end(),
                                     [&group, &i](char c) {
                                       return group[i].find(c) ==
                                              std::string::npos;
                                     }),
                      reference.end());
    }

    count += reference.size();
  }
  return count;
}

int main() {

  std::ifstream input_file("input.txt");

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

  std::cout << "first solution = " << CalculateSum_Of_Unique_Yes(inputData);
  std::cout << "second solution = "
            << GetCount_Yes_From_Everyone_In_A_Group(inputData);

  return 0;
}