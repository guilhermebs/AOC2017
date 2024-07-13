#include <iostream>
#include <chrono>
#include <fstream>
#include <string>

std::pair<int, int> score(const std::string & line)
{
    bool is_garbage = false;
    bool ignore_next = false;
    int result1 = 0;
    int result2 = 0;
    int level = 0;
    for (auto c: line)
    {
        if (is_garbage)
        {
            if (ignore_next) ignore_next = false;
            else if (c == '>') is_garbage = false;
            else if (c == '!') ignore_next = true;
            else result2++;
            continue;
        }
        switch (c)
        {
        case '{':
            if (!is_garbage)
                level++;
            break;
        case '}':
            if (!is_garbage)
            {
                result1 += level;
                level--;
            }
            break;
        case '<':
            is_garbage = true;
            break;
        default:
            break;
        }
    }
    return std::make_pair(result1, result2);
}


void solve()
{
    std::ifstream file("inputs/day09");
    std::string line;
    getline(file, line);
    //line = "{{<a!>},{<a!>},{<a!>},{<ab>}}";
    auto [part1_sol, part2_sol] = score(line);
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