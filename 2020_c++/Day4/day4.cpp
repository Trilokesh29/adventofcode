// byr(Birth Year)
// iyr(Issue Year)
// eyr(Expiration Year)
// hgt(Height)
// hcl(Hair Color)
// ecl(Eye Color)
// pid(Passport ID)
// cid(Country ID)

#include <fstream>
#include <future>
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

uint32_t CountNumberOfValidPassportsAsync(
    const std::vector<std::string> &aPassportData) {

  const std::vector<std::string> passportDataFirstHalf(
      aPassportData.begin(), aPassportData.begin() + aPassportData.size() / 2);

  const std::vector<std::string> passportDataSecondHalf(
      aPassportData.begin() + aPassportData.size() / 2, aPassportData.end());

  auto firstHalf = std::async(std::launch::async, [&passportDataFirstHalf]() {
    return CountNumberOfValidPassports(passportDataFirstHalf);
  });

  auto secondHalf = std::async(std::launch::async, [&passportDataSecondHalf]() {
    return CountNumberOfValidPassports(passportDataSecondHalf);
  });

  return firstHalf.get() + secondHalf.get();
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
            << CountNumberOfValidPassportsAsync(passportData);
  return 0;
}
