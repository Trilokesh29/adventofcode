#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using TPathMap = std::vector<std::string>;

int CountNoOfTreesEncountered(const TPathMap &aPathMap, int aRowMove,
                              int aColMove) {

  const int rowSize = aPathMap.size();
  const int colSize = aPathMap[0].size();
  int rowIndex = aRowMove;
  int colIndex = aColMove;
  int treeCount = 0;

  while (rowIndex < rowSize) {

    if (aPathMap[rowIndex][colIndex] == '#') {
      treeCount++;
    }

    colIndex = (colIndex + aColMove) % colSize;
    rowIndex += aRowMove;
  }

  return treeCount;
}

int CountNoOfTreesEncountered_recursion(const TPathMap &aPathMap, int rowIndex,
                                        int colIndex, int tempRowIndex,
                                        int tempColIndex) {

  static int treeCount = 0;

  if (tempRowIndex < aPathMap.size()) {
    if (aPathMap[tempRowIndex][tempColIndex] == '#') {
      treeCount++;
    }

    tempRowIndex += rowIndex;
    tempColIndex = (tempColIndex + colIndex) % aPathMap[0].size();

    CountNoOfTreesEncountered_recursion(aPathMap, rowIndex, colIndex,
                                        tempRowIndex, tempColIndex);
  }

  return treeCount;
}

int main() {

  TPathMap pathMap;
  pathMap.reserve(350);

  std::ifstream file("input.txt");

  if (file.is_open()) {
    std::string input;
    while (std::getline(file, input)) {
      pathMap.emplace_back(input);
    }
  }
  file.close();

  std::cout << "Number of trees encountered in the given map and movement ="
            << CountNoOfTreesEncountered(pathMap, 1, 3);

  //   std::cout << "tree count via recursion = "
  //             << CountNoOfTreesEncountered_recursion(pathMap, 1, 3, 1, 3);

  return 0;
}