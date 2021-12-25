#include <vector>
#include <iostream>
#include <map>
#include <fstream>
#include <sstream>

using namespace std;


void GetOptions(std::stringstream &input, std::vector<int> & options)
{
    std::string segment;

    while(std::getline(input, segment, ','))
    {
        options.push_back(stoi(segment)); //Split string at '_' character
    }
}

std::vector<std::pair<int,bool>> GetRow(std::string &input)
{
    std::vector<std::pair<int,bool>> row;
    row.reserve(5);

    for(int index =0; index < input.size();)
    {
        if(input[index] != ' ' && input[index + 1] != ' ')
        {
            string temp;
            temp.push_back(input[index]);
            temp.push_back(input[index + 1]);
            index += 2;

            row.push_back({stoi(temp), false});
        }
        else if(input[index] != ' ')
        {
            row.push_back({(input[index] - '0'), false});
            ++index;
        }
        else
        {
            ++index;
        }
    }

    return row;
}

void ReadInput(std::vector<int> & options, std::vector<std::vector<std::vector<std::pair<int, bool>>>> & boards)
{
    std::ifstream data("./input.txt");
    std::string temp;
    
    if(data.is_open())
    {
        std::vector<std::vector<std::pair<int, bool>>> tempBoard;
        tempBoard.reserve(5);

        while(std::getline(data, temp))
        {
            static int count = 0;
            if(count == 0)
            {
                //these are the options
                std::stringstream tmp (temp);
                GetOptions(tmp, options);
                ++count;
            }
            else
            {
                if(temp.size() >0)
                {
                    tempBoard.push_back(GetRow(temp));
                    ++count;
                    if((count - 1) > 0 && (count - 1)  % 5 == 0)
                    {
                        boards.push_back(tempBoard);
                        tempBoard.clear();
                    }
                }
            }

        }
    }
}

std::tuple<bool, int> updateBoards(int option, std::vector<std::vector<std::vector<std::pair<int, bool>>>> & boards)
{
    const auto board_size = boards.size();

    for(int size =0; size < board_size ; ++size)
    {
        // row wise match searching and updating
        for(int row = 0; row < 5 ; ++row)
        {
            int row_found = 0;
            int col = 0;
            for(; col < 5; ++col)
            {
                if(boards[size][row][col].first == option)
                {
                    boards[size][row][col].second = true;
                }

                if(boards[size][row][col].second == true)
                {
                    ++row_found;
                }
            }

            if(row_found == 5)
            {
                return {true, size};
            }
        }


        // col wise match searching
        for(int col = 0; col < 5; ++col)
        {
            int row = 0;
            int col_found = 0;
            for(; row < 5 ; ++row)
            {
                if(boards[size][row][col].first == option)
                {
                    boards[size][row][col].second = true;
                }

                if(boards[size][row][col].second == true)
                {
                    ++col_found;
                }
            }

            if(col_found == 5)
            {
                return {true, size};
            }
        }
    }

    return {false, -1};
}

auto solution(std::vector<int> options, std::vector<std::vector<std::vector<std::pair<int, bool>>>> & boards)
{
    auto unmarked_sum = 0;
    for(auto option: options)
    {
        const auto status = updateBoards(option, boards);
        if(std::get<0>(status))
        {
            const auto board_no = std::get<1>(status) ;

            for(int row = 0; row < 5; ++row)
            {
                for(int col = 0; col < 5 ; ++col)
                {
                    if(!boards[board_no][row][col].second)
                    {
                        unmarked_sum += boards[board_no][row][col].first;
                    }
                }
            }
            return unmarked_sum * option;
            break;
        }
    }

    return 0;
}


int main()
{
    std:;vector<std::vector<std::vector<std::pair<int, bool>>>> input;
    std::vector<int> options;
    ReadInput(options, input);

    cout << solution(options, input) << "\n";
    return 0;
}