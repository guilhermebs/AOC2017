#include <iostream>
#include <chrono>
#include <fstream>
#include <string>
#include <vector>

void solve()
{
    std::ifstream file("inputs/day11");
    std::string line;
    std::pair<int, int> coords(0, 0);
    int max_dist = 0;
    while (getline(file, line, ','))
    {
        if (line == "n")
        {
            coords.second += 2;
        }
        else if (line == "ne")
        {
            coords.first += 1;
            coords.second += 1;
        }
        else if (line == "se")
        {
            coords.first += 1;
            coords.second -= 1;
        }
         else if (line == "s")
        {
            coords.second -= 2;
        }       
        else if (line == "sw")
        {
            coords.first -= 1;
            coords.second -= 1;
        }
        else if (line == "nw")
        {
            coords.first -= 1;
            coords.second += 1;
        }
        else
        {
            std::cout << line << std::endl;
        }
        int diag_steps = abs(coords.first);
        int vert_steps = std::max(abs(coords.second) - diag_steps, 0) / 2;
        max_dist = std::max(max_dist, diag_steps + vert_steps);
    }
    
    std::cout << coords.first << ", " << coords.second << std::endl;
    int diag_steps = abs(coords.first);
    int vert_steps = std::max(abs(coords.second) - diag_steps, 0) / 2;
    std::cout << diag_steps << " " << vert_steps << std::endl;
    std::cout << "Part 1 solution: " << diag_steps + vert_steps << std::endl;
    std::cout << "Part 2 solution: " << max_dist << std::endl;
}

int main()
{
    auto started = std::chrono::high_resolution_clock::now();
    solve();
    auto done = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(done-started).count() << "ms\n";
}

