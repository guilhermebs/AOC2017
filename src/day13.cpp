#include <iostream>
#include <chrono>
#include <fstream>

#include "helper.hpp"

int position(int t, int range)
{
    int period = range + (range - 2);
    int rem = t % period;
    int pos = (rem < range)? rem: 2 * range - rem - 1;
    return pos;
}

void solve()
{
    std::ifstream file("inputs/day13");
    std::string line;
    std::vector<int> ranges;
    while (getline(file, line))
    {
        auto s = tokenize(line, ": ");
        while (ranges.size() < (size_t) stoi(s[0]))
            ranges.push_back(-1);
        ranges.push_back(stoi(s[1]));
    }
    std::cout << ranges.size() << std::endl;
    std::cout << ranges.back() << std::endl;
    int part1_sol = 0;
    for (size_t t=0; t < ranges.size(); t++)
    {
        auto pos = position(t, ranges[t]);
        if (pos == 0)
            part1_sol += t * ranges[t];
    }
    std::cout << "Part 1 solution: " << part1_sol <<  std::endl;

    int part2_sol = 0;
    while (true)
    {
        int t = part2_sol;
        bool caught = false;
        for (auto range: ranges)
        {
            if (position(t, range) == 0)
            {
                caught = true;
                break;
            }
            t++;
        }
        if (!caught) break;
        part2_sol++;
    };

    std::cout << "Part 2 solution: " << part2_sol <<  std::endl;
    
}

int main()
{
    auto started = std::chrono::high_resolution_clock::now();
    solve();
    auto done = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(done-started).count() << "ms\n";
}


