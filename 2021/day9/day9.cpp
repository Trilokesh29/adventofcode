#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

std::uint64_t get_risk(const std::vector<std::vector<int>> &input_patterns) {

  std::uint64_t risk = 0;

  const size_t row_size = input_patterns.size();
  for (int row = 0; row < row_size; ++row) {
    const size_t col_size = input_patterns[row].size();
    for (int col = 0; col < col_size; ++col) {
      if (row > 0 && input_patterns[row - 1][col] <= input_patterns[row][col])
        continue;
      if (col > 0 && input_patterns[row][col - 1] <= input_patterns[row][col])
        continue;
      if (row < row_size - 1 &&
          input_patterns[row + 1][col] <= input_patterns[row][col])
        continue;
      if (col < col_size - 1 &&
          input_patterns[row][col + 1] <= input_patterns[row][col])
        continue;

      risk += (input_patterns[row][col] + 1);
    }
  }

  return risk;
}

int dfs(int row, int col, const std::vector<std::vector<int>> &input,
        std::vector<std::vector<bool>> &marked, size_t row_size,
        size_t col_size) {
  if (row < 0 || col < 0 || row >= row_size || col >= col_size ||
      marked[row][col] == true) {
    return 0;
  }

  marked[row][col] = true;

  return 1 + dfs(row - 1, col, input, marked, row_size, col_size) +
         dfs(row, col - 1, input, marked, row_size, col_size) +
         dfs(row + 1, col, input, marked, row_size, col_size) +
         dfs(row, col + 1, input, marked, row_size, col_size);
}

void initialize(std::vector<std::vector<bool>> &marked, size_t row_size,
                size_t col_size, const std::vector<std::vector<int>> &input) {
  for (size_t row = 0; row < row_size; ++row) {
    for (size_t col = 0; col < col_size; ++col) {
      if (input[row][col] == 9)
        marked[row][col] = true;
    }
  }
}

int find_basin(const std::vector<std::vector<int>> &input) {
  const size_t row_size = input.size();
  const size_t col_size = input[0].size();

  std::vector<std::vector<bool>> marked(row_size,
                                        std::vector<bool>(col_size, false));
  initialize(marked, row_size, col_size, input);

  std::vector<int> result;
  for (size_t row = 0; row < row_size; ++row) {
    for (size_t col = 0; col < col_size; ++col) {
      if (marked[row][col])
        continue;
      result.push_back(dfs(row, col, input, marked, row_size, col_size));
    }
  }

  std::sort(result.begin(), result.end());
  return result[result.size() - 1] * result[result.size() - 2] *
         result[result.size() - 3];
}

void parse_input(const std::string &input_file) {
  std::ifstream in(input_file);
  std::vector<std::vector<int>> input_patterns;
  if (in.is_open()) {
    std::string row;
    while (!in.eof()) {
      std::getline(in, row);
      std::vector<int> temp;
      std::transform(row.begin(), row.end(), std::back_inserter(temp),
                     [](const char &val) { return val - '0'; });

      input_patterns.push_back(temp);
    }
  }

  in.close();

  const auto risk = get_risk(input_patterns);
  std::cout << "risk: " << risk << "\n";

  const auto basin_count = find_basin(input_patterns);
  std::cout << "basin count: " << basin_count << "\n";
}

int main() { parse_input("input.txt"); }