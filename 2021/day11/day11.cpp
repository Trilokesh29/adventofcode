#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

struct Octopus {

  int value;
  std::vector<Octopus *> adjacent;
  bool flashed = false;

  Octopus(int val) { value = val; }

  int flash() {
    int flash_counter = 0;
    if (this->value > 9) {
      this->flashed = true;
      this->value = 0;
      flash_counter++;

      for (int i = 0; i < adjacent.size(); i++) {
        flash_counter += adjacent[i]->increment();
      }
    }
    return flash_counter;
  }

  int increment() {
    int count_flashes = 0;
    if (!this->flashed) {
      this->value++;
      count_flashes = this->flash();
    }
    return count_flashes;
  }

  void updateAdjacent(std::vector<std::vector<Octopus>> &octopus_grid,
                      int octopus_row, int octopus_column) {
    for (int row_offset = -1; row_offset < 2; ++row_offset) {
      for (int column_offset = -1; column_offset < 2; ++column_offset) {

        if (!(row_offset == 0 && column_offset == 0)) {
          int row = octopus_row + row_offset;
          int column = octopus_column + column_offset;

          if (row > -1 && column > -1 && row < octopus_grid.size() &&
              column < octopus_grid[row].size()) {

            this->adjacent.push_back(&octopus_grid[row][column]);
          }
        }
      }
    }
  }
};

void find_solution(std::vector<std::vector<Octopus>> &oct_grid) {
  int total_flashes = 0;
  int day = 1;

  bool exit = false;

  while (!exit) {
    int this_step_flashes = 0;

    for (int row = 0; row < oct_grid.size(); ++row) {
      for (int col = 0; col < oct_grid[row].size(); ++col) {

        this_step_flashes += oct_grid[row][col].increment();
      }
    }

    // Rests all octopuses flashed status
    for (int row = 0; row < oct_grid.size(); ++row) {
      for (int col = 0; col < oct_grid[row].size(); ++col) {

        oct_grid[row][col].flashed = false;
      }
    }

    if (this_step_flashes == (oct_grid.size() * oct_grid.back().size())) {
      std::cout << "Part Two : " << day << std::endl;
      exit = true;
    }
    total_flashes += this_step_flashes;

    if (day == 100)
      std::cout << "Part One : " << total_flashes << std::endl;

    day++;
  }
}

void parse_input(std::vector<std::vector<Octopus>> &oct_grid) {
  std::string line;
  std::ifstream input("input.txt");
  if (input.fail())
    std::cout << "Failed to open file";
  else {

    while (input.peek() != EOF) {
      std::string line;
      input >> line;
      std::vector<Octopus> oct_row;
      for (char digit : line) {
        oct_row.push_back(Octopus(digit - '0'));
      }

      oct_grid.push_back(oct_row);
    }
  }
}

int main() {
  std::vector<std::vector<Octopus>> oct_grid;

  parse_input(oct_grid);

  for (int row = 0; row < oct_grid.size(); ++row) {
    for (int col = 0; col < oct_grid[row].size(); ++col) {
      oct_grid[row][col].updateAdjacent(oct_grid, row, col);
    }
  }

  find_solution(oct_grid);

  return 0;
}