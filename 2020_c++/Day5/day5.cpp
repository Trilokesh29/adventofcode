#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

uint16_t FindRow(std::string aRowInput, uint8_t index, uint16_t upperLimit,
                 uint16_t lowerLimit) {
  static int row = 0;

  if (index < aRowInput.size()) {

    const char digit = aRowInput[index];
    if (digit == 'F') {
      upperLimit = lowerLimit + (upperLimit - lowerLimit) / 2;
      row = lowerLimit;

    } else {
      lowerLimit += (upperLimit - lowerLimit) / 2 + 1;
      row = upperLimit;
    }

    FindRow(aRowInput, ++index, upperLimit, lowerLimit);
  }

  return row;
}

uint8_t FindCol(std::string aColInput, uint8_t index, uint16_t upperLimit,
                uint16_t lowerLimit) {
  static int col = 0;

  if (index < aColInput.size()) {

    const char digit = aColInput[index];
    if (digit == 'L') {
      upperLimit = lowerLimit + (upperLimit - lowerLimit) / 2;
      col = lowerLimit;

    } else {
      lowerLimit += (upperLimit - lowerLimit) / 2 + 1;

      col = upperLimit;
    }

    FindCol(aColInput, ++index, upperLimit, lowerLimit);
  }

  return col;
}

uint32_t CalculateSeatId(std::string aInput) {

  int row = FindRow(std::string(aInput.begin(), aInput.begin() + 7), 0, 127, 0);
  int col = FindCol(std::string(aInput.begin() + 7, aInput.end()), 0, 7, 0);

  return row * 8 + col;
}

uint32_t GetHighestSeatId(const std::vector<std::string> &puzzle) {
  std::set<uint32_t> seatIds;
  for (const auto &data : puzzle) {
    seatIds.insert(CalculateSeatId(data));
  }

  return *seatIds.rbegin();
}

int main() {

  std::ifstream file("input.txt");
  std::vector<std::string> puzzle;
  puzzle.reserve(950);

  if (file.is_open()) {
    std::string input;
    while (std::getline(file, input)) {
      puzzle.emplace_back(input);
    }
  }

  file.close();

  std::cout << GetHighestSeatId(puzzle);

  return 0;
}