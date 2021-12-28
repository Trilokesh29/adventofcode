#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <stack>
#include <string>
#include <unordered_set>
#include <vector>

std::map<char, int> illegalPoints = {
    {')', 3}, {']', 57}, {'}', 1197}, {'>', 25137}};

std::map<char, int> autoCompletePoints = {
    {'(', 1}, {'[', 2}, {'{', 3}, {'<', 4}};

const std::unordered_set<char> closing{')', '}', ']', '>'};

std::map<char, char> pairs{{
                               ')',
                               '(',
                           },
                           {']', '['},
                           {'}', '{'},
                           {'>', '<'}};

auto syntax_error_score(const std::string &data) {
  std::stack<char> ref;
  for (auto val : data) {
    if (closing.count(val) == 0) {
      ref.push(val);
    } else {
      if (ref.size() > 0) {
        if (ref.top() != pairs[val]) {
          return illegalPoints[val];
        } else {
          ref.pop();
        }
      }
    }
  }

  return 0;
}

std::uint64_t autocomplete_score(const std::vector<std::string> &input,
                                 uint32_t incomplete_count) {

  std::vector<uint64_t> scores;

  for (const auto &data : input) {
    std::stack<char> ref;
    bool syntax_error = false;
    for (auto val : data) {
      if (closing.count(val) == 0) {
        ref.push(val);
      } else {
        if (ref.size() > 0) {
          if (ref.top() != pairs[val]) {
            syntax_error = true;
            break;
          } else {
            ref.pop();
          }
        }
      }
    }

    if (!syntax_error) {
      uint64_t temp_score = 0;
      while (ref.size() > 0) {
        temp_score =
            (temp_score * incomplete_count) + autoCompletePoints[ref.top()];
        ref.pop();
      }
      scores.push_back(temp_score);
    }
  }

  if (!scores.empty()) {
    std::sort(scores.begin(), scores.end());
    return scores[scores.size() / 2];
  }

  return 0;
}

int main() {
  std::ifstream in("input.txt");
  std::vector<std::string> input;
  uint64_t sum = 0;

  if (in.is_open()) {
    std::string row;
    while (!in.eof()) {
      std::getline(in, row);
      sum += syntax_error_score(row);
      input.push_back(row);
    }
  }

  std::cout << "syntax_error_score = " << sum << "\n";
  std::cout << "autocomplete score = " << autocomplete_score(input, 5) << "\n";
}
