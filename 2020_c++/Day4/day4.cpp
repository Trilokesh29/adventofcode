// byr(Birth Year)
// iyr(Issue Year)
// eyr(Expiration Year)
// hgt(Height)
// hcl(Hair Color)
// ecl(Eye Color)
// pid(Passport ID)
// cid(Country ID)

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace {
const std::vector<std::string> AttributesToCheck = {"byr", "iyr", "eyr", "hgt",
                                                    "hcl", "ecl", "pid"};
}

uint32_t
CountNumberOfValidPassports(const std::vector<std::string> &aPassportData) {

  int numberOfValidPassports = 0;

  for (const auto &data : aPassportData) {
    int count = 0;
    for (const auto &checkFact : AttributesToCheck) {

      if (data.find(checkFact) != std::string::npos) {
        count++;
      } else {
        break;
      }
    }
    if (count == AttributesToCheck.size()) {
      numberOfValidPassports++;
    }
  }

  return numberOfValidPassports;
}

void ReadAndParseInput(std::vector<std::string> &apassportData) {
  std::ifstream in("input.txt");

  if (in.is_open()) {
    std::string input;
    std::string temp;

    while (std::getline(in, input)) {
      if (!input.empty()) {
        temp += input;
      } else {
        apassportData.push_back(temp);
        temp.clear();
      }
    }

    apassportData.push_back(temp);
  }
}

int main() {

  std::vector<std::string> passportData;

  ReadAndParseInput(passportData);

  std::cout << "Number of valid passports are = "
            << CountNumberOfValidPassports(passportData);
  return 0;
}
