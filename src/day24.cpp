#include <iostream>
#include <chrono>
#include <fstream>
#include <vector>
#include <queue>
#include <numeric>
#include "helper.hpp"

struct Component
{
    int p1;
    int p2;
    Component(int p1, int p2): p1(p1), p2(p2) {};
    Component(const std::string &line)
    {
        auto split = tokenize(line, "/");
        p1 = stoi(split[0]);
        p2 = stoi(split[1]);
    }
    inline bool fits(const Component &other) const
    {
        return p2 == other.p1;
    }
    inline bool fits_reverse(const Component &other) const
    {
        return p2 == other.p2;
    }
    bool operator== (const Component &other) const
    {
        return ((p1 == other.p1) && (p2 == other.p2)) || ((p1 == other.p2) && (p2 == other.p1));
    }
    Component reverted () const
    {
        return Component(p2, p1);
    }
};

void solve()
{
    std::ifstream file("inputs/day24");
    std::string line;
    std::vector<Component> components;

    while (getline(file, line))
        components.emplace_back(line);
    
    std::queue<std::vector<Component>> bridges;
    bridges.push({Component(0, 0)});
    int part1_sol = 0;
    size_t longest = 0;
    int part2_sol = 0;
    auto strength_sum = [](int sum, const Component &c){ return sum + c.p1 + c.p2; };
    while (bridges.size() > 0)
    {
        //std::cout << "N bridges: " << bridges.size() << std::endl;
        const auto bridge = bridges.front();
        bridges.pop();
        //std::cout << "Bridge: ";
        //for(auto &c: bridge)
        //    std::cout << c.p1 << "/" << c.p2 << " ";
        //std::cout << std::endl;
        auto added_component = false;
        for (auto &c: components)
        {
            if (std::find(bridge.begin(), bridge.end(), c) == bridge.end())
            {
                if (bridge.back().fits(c))
                {
                    auto new_bridge = bridge;
                    new_bridge.push_back(c);
                    bridges.push(new_bridge);
                    added_component = true;
                } else if (bridge.back().fits_reverse(c))
                {
                    auto new_bridge = bridge;
                    new_bridge.push_back(c.reverted());
                    bridges.push(new_bridge);
                    added_component = true;
                }
           }
        }
        if (!added_component)
        {
            part1_sol = std::max(
                part1_sol,
                std::accumulate(bridge.begin(), bridge.end(), 0, strength_sum));
            if (bridge.size() > longest)
            {
                part2_sol = std::accumulate(bridge.begin(), bridge.end(), 0, strength_sum);
                longest = bridge.size();
            } else if (bridge.size() == longest)
            {
                part2_sol = std::max(part2_sol, std::accumulate(bridge.begin(), bridge.end(), 0, strength_sum));
            }
        }
    }
    std::cout << "Part 1 solution: " << part1_sol << std::endl;
    std::cout << "Part 2 solution: " << part2_sol << std::endl;
}

int main()
{
    auto started = std::chrono::high_resolution_clock::now();
    solve();
    auto done = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(done-started).count() << "ms\n";
}