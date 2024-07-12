#include <vector>
#include <iostream>
#include <chrono>
#include <fstream>
#include <algorithm>
#include "helper.hpp"

void solve()
{
    std::ifstream file("inputs/day02");
    std::string line;
    int sol_pt1 = 0;
    int sol_pt2 = 0;
    while (getline(file, line))
    {
        std::replace(line.begin(), line.end(), '\t', ' ');
        auto numbers_str = tokenize(line, " ");
        std::vector<int> numbers;
        std::transform(numbers_str.begin(), numbers_str.end(), std::back_inserter(numbers), [](std::string n) { return stoi(n); });
        auto max = *std::max_element(numbers.begin(), numbers.end());
        auto min = *std::min_element(numbers.begin(), numbers.end());
        sol_pt1 += max - min; 
        for (size_t i = 0; i < numbers.size(); i++)
        {
            for (size_t j = 0; j < numbers.size(); j++)
            {
                if (i == j) continue;
                if (numbers[i] % numbers[j] == 0)
                {
                    sol_pt2 += numbers[i] / numbers[j];
                    break;
                }
            }
        }
    }
    
    std::cout << "Part 1 solution: " << sol_pt1 << std::endl;
    std::cout << "Part 2 solution: " << sol_pt2 << std::endl;

}

int main()
{
    auto started = std::chrono::high_resolution_clock::now();
    solve();
    auto done = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(done-started).count() << "ms\n";
}