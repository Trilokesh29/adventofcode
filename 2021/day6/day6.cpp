#include <sstream>
#include <iostream>
#include <string>
#include <fstream>
#include <deque>
#include <numeric>
#include <vector>
#include <algorithm>

using namespace std;

static constexpr int kTimeBetweenSpawns = 7;
static constexpr int kTimeToFirstSpawn = 2;
static constexpr int kNumBuckets = kTimeBetweenSpawns + kTimeToFirstSpawn;


void init_population(std::string st , char sep, std::vector<int64_t> &splited)
{
    std::stringstream ss(st);

    for (int num; ss >> num;) {

        splited[num]++;

        if (ss.peek() == sep)
            ss.ignore();
    }
}

void PrintPopulation(const std::vector<int> &population_ref)
{
    cout << "printing population .... \n";
    for(auto data : population_ref)
    {
        cout << data << "\t";
    }
    cout << "\n";
}

int64_t day6(vector<int64_t> &buckets, int numDays=80)
{
    for (int day = 0; day < numDays; ++day)
    {
        int64_t spawners = buckets[0];
        buckets.erase(buckets.begin());
        buckets.push_back(spawners);
        buckets[kTimeBetweenSpawns - 1] += spawners;
    }

    return accumulate(begin(buckets), end(buckets), 0ll);
}


int main()
{
    std::ifstream input("input.txt");

    std::string inp;
    
    if(input.is_open())
    {
        input >> inp;

        std::vector<int64_t> population(kNumBuckets, 0);

        init_population(inp, ',', population);

        cout << day6(population) << "\n";
        cout << day6(population, 256) << "\n";
    }
}