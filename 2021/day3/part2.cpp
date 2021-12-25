#include <iostream>
#include "../parser.h"
#include <algorithm>

using namespace std;

int solution(std::vector<std::string> input)
{
    size_t bit_count = input[0].length();
    int gamma_rate = 0;
    int epsilon_rate = 0;

    for(auto index =0; index < bit_count ; ++index)
    {
        std::vector<int> temp;
        temp.reserve(input.size());
        
        for(const auto &it : input)
        {
            temp.push_back(it[index] - '0');
        }

        const size_t count_of_1 = std::count(temp.begin(), temp.end(), 1);
        if (count_of_1 ==  std::max(count_of_1, (input.size() - count_of_1)))
        {
            gamma_rate = (gamma_rate << 1) | 1;
            epsilon_rate = (epsilon_rate << 1) | 0;
        }
        else
        {
            gamma_rate = (gamma_rate << 1) | 0;
            epsilon_rate = (epsilon_rate << 1) |1;
        }
    }

    return gamma_rate * epsilon_rate;
}


int main()
{
    std::fstream obj("./input.txt");
    cout << solution(GetInput(obj));
    return 0;
}