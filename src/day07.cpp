#include <iostream>
#include <chrono>
#include <fstream>
#include <unordered_map>
#include <regex>
#include "helper.hpp"

struct Program
{
    std::string name;
    int weight;
    std::vector<std::string> holds;
    Program *held_by;
};

int weight(std::unordered_map<std::string, Program> &programs, std::string node)
{
    int result = programs[node].weight;
    for (auto n: programs[node].holds)
        result += weight(programs, n);
    return result;
}

int balance(std::unordered_map<std::string, Program> &programs, std::string node, int expected)
{
    if (programs[node].holds.size() == 0)
        return expected;

    std::vector<int> weights;
    for (auto n: programs[node].holds)
        weights.push_back(weight(programs, n));
    int new_expected = (weights[0] == weights[1])? weights[0] : (weights[1] == weights[2])? weights[1] : weights[2];
    for (size_t i = 0; i < weights.size(); i++)
    {
        if (weights[i] != new_expected)
            return balance(programs, programs[node].holds[i], new_expected);
    }
    return expected - new_expected * weights.size();
}

void solve()
{
    std::ifstream file("inputs/day07");
    std::string line;
    static std::regex pattern("(\\w+) \\((\\d+)\\)");
    std::smatch match;
    std::unordered_map<std::string, Program> programs;
    while (getline(file, line))
    {
        if (std::regex_search(line, match, pattern))
        {
            std::string name = match[1];
            int weight = stoi(match[2]);
            std::vector<std::string> holds;
            auto arrow_pos = line.find("->");
            if (arrow_pos != std::string::npos)
                holds = tokenize(line, ", ", arrow_pos + 3);
            programs[name] = Program{name, weight, holds, NULL};
        }
    }
    for (auto &[k, v] : programs)
    {
        for (auto &h: v.holds)
        {
            programs[h].held_by = &v;
        }
    }
    Program *p = &(programs["lfkqyf"]);
    while (p->held_by)
    {
        p = p->held_by;
    }
    std::cout << "Part 1 solution: " << p->name << std::endl;

    std::cout << "Part 2 solution: " << balance(programs, p->name, 137832) << std::endl;
    
}


int main()
{
    auto started = std::chrono::high_resolution_clock::now();
    solve();
    auto done = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(done-started).count() << "ms\n";
}