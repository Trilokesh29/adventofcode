#include <fstream>
#include <vector>
#include <string>
#include <iostream>

std::vector<std::string> GetInput(std::fstream & source)
{
    std::vector<std::string> data;

    if (source.is_open()) {
        std::string line;
        while (std::getline(source, line)) {
            data.push_back(line);
        }
        source.close();
    }
    return data;
}