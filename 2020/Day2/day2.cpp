#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

namespace {

std::vector<std::string> input;
static int correctPasswords = 0;

std::tuple<std::string, char, int, int> ExtractData(const std::string &data) {

  const auto it = data.find(": ");
  if (it != std::string::npos) {

    std::string password = data.substr(it + 2);
    std::string rest = data.substr(0, it);

    const auto innerIt = rest.find("-");
    if (innerIt != std::string::npos) {
      return std::tuple<std::string, char, int, int>{
          password, rest[rest.size() - 1], stoi(rest.substr(0, innerIt)),
          stoi(rest.substr(innerIt + 1, rest.size() - 4))};
    }
  }
  return {};
}

int CountOfCorrectPasswords() {

  for (const auto &valueAtIndex : input) {
    std::tuple<std::string, char, int, int> data = ExtractData(valueAtIndex);
    auto count = std::count(std::get<0>(data).begin(), std::get<0>(data).end(),
                            std::get<1>(data));

    if ((std::get<2>(data) <= count) && (std::get<3>(data) >= count)) {
      correctPasswords++;
    }
  }

  return correctPasswords;
}

} // namespace

int main() {

  int num;

  std::ifstream file("input.txt");

  if (file.is_open()) {
    std::string line;
    while (std::getline(file, line)) {
      input.push_back(line);
    }
    file.close();
  }

  std::cout << "count = " << CountOfCorrectPasswords() << "\n";

  return 0;
}