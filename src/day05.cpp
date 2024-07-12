#include <iostream>
#include <chrono>
#include <fstream>
#include <vector>

void solve()
{
    std::ifstream file("inputs/day05");
    std::string line;
    std::vector<int> jump;
    while (getline(file, line))
        jump.push_back(stoi(line));
    
    int pos = 0;
    int part1_sol = 0;
    while (pos >= 0 && pos < (int) jump.size())
    {
        pos += jump[pos]++;
        part1_sol++;
    }

    std::cout << "Part 1 solution: " << part1_sol << std::endl;
}

void solve_pt2()
{
    std::ifstream file("inputs/day05");
    std::string line;
    std::vector<int> jump;
    while (getline(file, line))
        jump.push_back(stoi(line));
    
    int pos = 0;
    int part2_sol = 0;
    while (pos >= 0 && pos < (int) jump.size())
    {
        int next_pos = pos + jump[pos];
        jump[pos] += (jump[pos] >= 3)? -1: 1;
        pos = next_pos;
        part2_sol++;
    }

    std::cout << "Part 2 solution: " << part2_sol << std::endl;
}

int main()
{
    auto started = std::chrono::high_resolution_clock::now();
    solve();
    solve_pt2();
    auto done = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(done-started).count() << "ms\n";
}