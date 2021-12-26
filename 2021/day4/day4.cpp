#include <vector>
#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include <unordered_set>

using namespace std;


void GetOptions(std::stringstream &input, std::vector<int> & options)
{
    std::string segment;

    while(std::getline(input, segment, ','))
    {
        options.push_back(stoi(segment)); //Split string at '_' character
    }
}

std::vector<int> GetRow(std::string &input)
{
    std::vector<int> row;
    row.reserve(5);

    for(int index =0; index < input.size();)
    {
        if(input[index] != ' ' && input[index + 1] != ' ')
        {
            string temp;
            temp.push_back(input[index]);
            temp.push_back(input[index + 1]);
            index += 2;

            row.push_back(stoi(temp));
        }
        else if(input[index] != ' ')
        {
            row.push_back((input[index] - '0'));
            ++index;
        }
        else
        {
            ++index;
        }
    }

    return row;
}

void ReadInput(std::vector<int> & options, std::vector<std::vector<std::vector<int>>> & boards)
{
    std::ifstream data("./input.txt");
    std::string temp;
    
    if(data.is_open())
    {
        std::vector<std::vector<int>> tempBoard;
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

void printBoards(const std::vector<std::vector<std::vector<int>>> & boards)
{
    for(int board = 0; board < boards.size(); ++ board)
    {
        cout << "board no " << board << "\n";
        for(int row = 0; row < 5; ++row)
        {
            for(int col = 0; col < 5; ++col)
            {
                cout << boards[board][row][col] << "\t";
            }
            cout << "\n";
        }
    }
}

std::pair<int, int> findCell(int num, const std::vector<std::vector<int>>  &board)
{
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j)
        {
            if(board[i][j] == num) 
                return {i,j};
        }

    }

    return {-1,-1};
}


bool checkRows(const std::vector<std::vector<int>> & board)
{
    bool won;
    for(std::vector<int> row : board)
    {
        won = true;
        for(int cell : row)
        {
            if(cell != -1)
            {
                won = false;
                break;
            }
        }
        if(won) return won;
    }
    return won;
}

bool checkCols(const std::vector<std::vector<int>>&  board)
{
    bool won;
    for (int i = 0; i < 5; ++i) {
        won = true;
        for (int j = 0; j < 5 ; ++j)
        {
            if(board[j][i] != -1)
            {
                won = false;
                break;
            }

        }
        if(won) return won;
    }
    return won;
}

bool won(const std::vector<std::vector<int>>&  board)
{
    return checkRows(board) || checkCols(board);
}

int unMarkedSum(const std::vector<std::vector<int>>&  board)
{
    int sum = 0;
    for(std::vector<int> row : board)
    {

        for(int cell : row)
        {
            if(cell !=-1) sum+=cell;
        }

    }
    return sum;
}

int part1(std::vector<int> deck,std::vector<std::vector<std::vector<int>>> boards)
{
    for(int card : deck)
    {
        for (int i = 0; i < boards.size(); ++i) {

            std::pair<int,int> pos = findCell(card,boards[i]);
            if(pos.first != -1)
            {
                boards[i][pos.first][pos.second] = -1;

                if (won(boards[i])) {
                    return unMarkedSum(boards[i]) * card;
                }
            }

        }
    }
    return -1;

}

int part2(std::vector<int> deck,std::vector<std::vector<std::vector<int>>> boards)
{
    std::unordered_set<int> boards_status;

    for(int card : deck)
    {
        for (int i = 0; i < boards.size(); ++i) {

            if(boards_status.count(i) == 0)
            {

                std::pair<int, int> pos = findCell(card, boards[i]);

                if (pos.first != -1) {

                    boards[i][pos.first][pos.second] = -1;
                    
                    if (won(boards[i])) {

                        boards_status.insert(i);

                        if(boards_status.size() == boards.size()) 
                        {
                            return unMarkedSum(boards[i]) * card;
                        }
                    }
                }
            }
        }
    }
    return -1;

}

int main()
{
    std::vector<std::vector<std::vector<int>>> input;
    std::vector<int> options;
    ReadInput(options, input);

    cout << part1(options, input) << "\n";
    cout << part2(options, input) << "\n";
    return 0;
}