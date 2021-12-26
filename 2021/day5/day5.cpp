#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>
#include <array>

using namespace std;

static int board1[1000][1000];
static int board2[1000][1000];


struct Data
{
    std::pair<int,int> startpoint, endpoint;
};

void GetOptions(const std::string &input, Data &data)
{
    static char part1[10], part2[10];

    sscanf( input.c_str(), "%s->[^->]", part1);
    sscanf( input.c_str(), "%*[^->]->%s", part2);

    sscanf(part1, "%d,[^,]", &data.startpoint.first);
    sscanf(part1, "%*[^,],%d", &data.startpoint.second);
    sscanf(part2, "%d,[^,]", &data.endpoint.first);
    sscanf(part2, "%*[^,],%d", &data.endpoint.second);
}


void traverseCoordinates(std::pair<int,int> startPoint, std::pair<int,int>endPoint)
{    
    int xDiff = endPoint.first - startPoint.first  ;
    int yDiff = endPoint.second - startPoint.second ;

    bool isHorizontal = (xDiff == 0 || yDiff == 0);

    int xIncrement = xDiff == 0 ? 0 : (xDiff / abs(xDiff));
    int yIncrement = yDiff == 0 ? 0 :  (yDiff/ abs(yDiff));

    startPoint.first-=xIncrement;
    startPoint.second-=yIncrement;

    while((startPoint.first != endPoint.first ) || (startPoint.second != endPoint.second))
    {
        startPoint.first+=xIncrement;
        startPoint.second+=yIncrement;

        if(isHorizontal)
        {
            board1[startPoint.first][startPoint.second]++;
        }

        board2[startPoint.first][startPoint.second]++;

    }
}


void ParseInput()
{
    std::ifstream data("./input.txt");
    std::string temp;
    
    if(data.is_open())
    {
        Data d;

        while(std::getline(data, temp))
        {
            GetOptions(temp, d);
            traverseCoordinates(d.startpoint, d.endpoint);
        }
    }
}

int solution1()
{
    int answers = 0;
    for(int row = 0; row < 1000; ++row)
    {
        for(int col =0; col < 1000; ++col)
        {
            if(board1[row][col] >= 2)
            {
                ++answers;
            }
        }
    }
    return answers;
}

int solution2()
{
    int answers = 0;
    for(int row = 0; row < 1000; ++row)
    {
        for(int col =0; col < 1000; ++col)
        {
            if(board2[row][col] >= 2)
            {
                ++answers;
            }
        }
    }
    return answers;
}

int main()
{
    ParseInput();
    
    cout << solution1() << "\n";
    cout << solution2() << "\n";

    return 0;
}