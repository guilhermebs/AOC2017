#include <vector>
#include <iostream>
#include <chrono>
#include <fstream>

void solve()
{
    std::ifstream file("inputs/day01");
    std::string line;
    getline(file, line);
    int pt1_result = 0;
    for (size_t i = 0; i < line.size(); i++)
    {
        if (line[i] == line[(i+1)%line.size()])
            pt1_result += line[i] - '0';
    }
    std::cout << "Part 1 solution: " << pt1_result << std::endl;
    int pt2_result = 0;
    int step = line.size() / 2; 
    for (size_t i = 0; i < line.size(); i++)
    {
        if (line[i] == line[(i+step)%line.size()])
            pt2_result += line[i] - '0';
    }
    std::cout << "Part 2 solution: " << pt2_result << std::endl;

}

int main()
{
    auto started = std::chrono::high_resolution_clock::now();
    solve();
    auto done = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(done-started).count() << "ms\n";

}