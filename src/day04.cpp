#include <iostream>
#include <chrono>
#include <fstream>
#include "helper.hpp"

void solve()
{
    std::ifstream file("inputs/day04");
    std::string line;
    int sol_pt1 = 0;
    while (getline(file, line))
    {
        auto words = tokenize(line, " ");
        for (auto &w: words)
            std::sort(w.begin(), w.end());
        bool is_valid = true;
        for (size_t i = 0; i < words.size(); i++)
        {
            for (size_t j = i + 1; j < words.size(); j++)
            {
                if (words[i] == words[j])
                {
                    is_valid = false;
                    std::cout << words[i] << " " << words[j] << std::endl;
                    break;
                }
            }
            if (!is_valid) break;
        }
        sol_pt1 += is_valid;
    }
    std::cout << "Part 1 solution: " << sol_pt1 << std::endl;
}
 

int main()
{
    auto started = std::chrono::high_resolution_clock::now();
    solve();
    auto done = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(done-started).count() << "ms\n";
}