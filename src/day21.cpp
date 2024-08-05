#include <iostream>
#include <chrono>
#include <fstream>
#include <unordered_map>
#include <algorithm>
#include "helper.hpp"

std::string rotate(const std::string &pattern)
{
    // 0 1 2   6 3 0
    // 3 4 5   7 4 1
    // 6 7 8   8 5 2
    auto result = pattern;
    auto n = (pattern.length() == 4)? 2 : 3;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            result[i + n*j] = pattern[j + n * (n - i - 1)];
        }
    }
    return result;
}

std::string flipx(const std::string &pattern)
{
    auto result = pattern;
    auto n = (pattern.length() == 4)? 2 : 3;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            result[i + n * j] = pattern[n - i - 1 + n * j];
        }
    }
    return result;
}

std::string flipy(const std::string &pattern)
{
    auto result = pattern;
    auto n = (pattern.length() == 4)? 2 : 3;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            result[i + n * j] = pattern[i + n * (n - j - 1)];
        }
    }
    return result;
}


std::unordered_map<std::string, std::string> get_rules()
{
    std::ifstream file("inputs/day21");
    std::string line;
    std::unordered_map<std::string, std::string> result;
    while (getline(file, line))
    {
        auto parts = tokenize(line, " => ");
        auto origin = parts[0];
        auto target = parts[1];
        std::erase(origin, '/');
        std::erase(target, '/');
        for (int nrot = 0; nrot < 4; nrot++)
        {
            auto rotated = origin;
            for (int i = 0; i < nrot; i++)
                rotated = rotate(rotated);
            result[rotated] = target;    
            result[flipx(rotated)] = target;    
            result[flipy(rotated)] = target;    
            result[flipy(flipx(rotated))] = target;    
        }
    }
    return result;
}

void solve()
{
    auto rules = get_rules();
    std::string grid(".#...####");
    auto n = 3;
    for (int iter=0; iter<18; iter++)
    {
        auto tile_size = (n % 2 == 0)? 2 : 3;
        auto n_tiles = n / tile_size;
        std::string new_grid((n + n_tiles) * (n + n_tiles), 'X');
        for (int it=0; it<n_tiles; it++)
        {
            for (int jt=0; jt<n_tiles; jt++)
            {
                std::string tile("");
                for (int j=0; j<tile_size; j++)
                {
                    tile += grid.substr(it * tile_size + n * tile_size * jt + n *  j, tile_size);
                }
                auto new_pattern = rules.at(tile);
                for (int i=0; i<(tile_size + 1); i++)
                {
                    for (int j=0; j<(tile_size + 1); j++)
                        new_grid[it * (tile_size + 1) + i + (n + n_tiles) * (tile_size + 1) * jt + (n + n_tiles) * j] = new_pattern[i + (tile_size + 1) * j];
                }
            }
        }

        grid = new_grid;
        n += n_tiles;
    }
    std::cout << "Part 1 solution: " << std::count(grid.begin(), grid.end(), '#') << std::endl;
}

int main()
{
    auto started = std::chrono::high_resolution_clock::now();
    solve();
    auto done = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(done-started).count() << "ms\n";
}
