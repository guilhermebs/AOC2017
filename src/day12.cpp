#include <iostream>
#include <chrono>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <deque>

#include "helper.hpp"

std::unordered_set<int> create_group (const std::unordered_map<int, std::vector<int>> &programs, int seed)
{
    std::deque<int> queue = {seed};
    std::unordered_set<int> group;
    while (queue.size())
    {
        int id = queue.back();
        queue.pop_back();
        if (group.contains(id)) continue;
        group.insert(id);
        for (int p: programs.at(id))
        {
            queue.push_back(p);
        }
    }
    return group;
}

void solve ()
{
    std::ifstream file("inputs/day12");
    std::string line;
    std::unordered_map<int, std::vector<int>> programs;
    while (getline(file, line))
    {
        auto s1 = tokenize(line, " <-> ");
        auto id = stoi(s1[0]);
        std::vector<int> targets;
        for (auto t: tokenize(s1[1], ", "))
            targets.push_back(stoi(t));
        programs[id] = targets;
    }
    auto group0 = create_group(programs, 0);
    std::cout << "Part 1 solution: " << group0.size() << std::endl;
    
    int sol_pt2 = 0;
    while (programs.size())
    {
        int seed = programs.begin()->first;
        auto group = create_group(programs, seed);
        for (auto p: group)
            programs.erase(p);
        sol_pt2++;
    }
    
    std::cout << "Part 2 solution: " << sol_pt2 << std::endl;
}


int main()
{
    auto started = std::chrono::high_resolution_clock::now();
    solve();
    auto done = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(done-started).count() << "ms\n";
}

