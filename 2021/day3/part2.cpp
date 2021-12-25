#include <iostream>
#include "../parser.h"
#include <algorithm>

using namespace std;


void filter(std::vector<std::string> &input, int bit, int ref)
{
    auto newend = std::remove_if(input.begin(), input.end(), [&bit, &ref](auto &data){
            return (data[bit] -'0') != ref;
    });

    input.erase(newend, input.end());
}

template<typename T>
auto findvalue(std::vector<std::string> input, T identifier)
{
    const size_t bit_count = input[0].length();
    for(int index =0; index < bit_count; ++index)
    {
        if(input.size() == 1)
        {
            break;
        }

        std::vector<int> temp;
        temp.reserve(input.size());
        
        for(const auto &it : input)
        {
            temp.push_back(it[index] - '0');
        }

        const size_t count_of_1 = std::count(temp.begin(), temp.end(), 1);
        const size_t count_of_0 = (input.size() - count_of_1);

        if (count_of_1 > count_of_0)
        {
            if(identifier == "o2")
                filter(input, index, 1);
            else
                filter(input, index, 0);
        }
        else if(count_of_1 < count_of_0)
        {
            if(identifier == "o2")
                filter(input, index, 0);
            else
                filter(input, index, 1);
        }
        else
        {
            if(identifier == "o2")
                filter(input, index, 1);
            else
                filter(input, index, 0);
        }
    }

    int data = 0;
    for(int index = 0; index < input[0].length(); ++index)
    {
        data = (data << 1) | (input[0][index] -'0');
    }

    return data;
}

auto solution(std::vector<std::string> input)
{
    size_t bit_count = input[0].length();
    return findvalue(input, "co2") * findvalue(input, "o2");
}


int main()
{
    std::fstream obj("./input.txt");
    cout << solution(GetInput(obj));
    return 0;
}