#include <iostream>
#include <chrono>
#include <fstream>
#include <array>
#include <unordered_set>
#include "helper.hpp"


using banks = std::array<int, 16>;

banks relocate_memory(const banks &in)
{
    banks result = in;
    auto idx = std::max_element(result.begin(), result.end());
    auto rem = *idx;
    *idx = 0;
    while (rem > 0)
    {
        idx++;
        if (idx == result.end()) idx = result.begin();
        (*idx)++;
        rem--;
    }
    return result; 
}

std::string banks2string(const banks &in)
{
    std::string result = "";
    for (auto &v: in)
        result += "," + std::to_string(v);
    return result;
}

void solve()
{
    banks current = {
        0, 5, 10, 0, 11, 14, 13, 4, 11, 8, 8, 7, 1,	4, 12,11
    };
    auto cur_s = banks2string(current);
    std::unordered_set<std::string> seen;
    int part1_solution = 0;
    while (!seen.contains(cur_s))
    {
        seen.insert(cur_s);
        current = relocate_memory(current);
        cur_s = banks2string(current);
        part1_solution++;
    }
    std::cout << "Part 1 solution: " << part1_solution << std::endl;
    auto ref = cur_s;
    int part2_solution = 0;
    do 
    {
        current = relocate_memory(current);
        cur_s = banks2string(current);
        part2_solution++;
    } while (cur_s != ref);
    std::cout << "Part 2 solution: " << part2_solution << std::endl;
}


int main()
{
    auto started = std::chrono::high_resolution_clock::now();
    solve();
    auto done = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(done-started).count() << "ms\n";
}