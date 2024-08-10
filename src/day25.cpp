#include <iostream>
#include <chrono>
#include <fstream>
#include <vector>
#include <unordered_map>
#include "helper.hpp"


struct RuleSet
{
    int write_0;
    int move_0;
    char state_0;
    int write_1;
    int move_1;
    char state_1;
    auto apply(std::vector<int>::iterator tape_iter)
    {
        switch (*tape_iter)
        {
        case 0:
            *tape_iter = write_0;
            return std::make_tuple(tape_iter + move_0, state_0);
        case 1:
            *tape_iter = write_1;
            return std::make_tuple(tape_iter + move_1, state_1);
        default:
            throw "Error!";
        }
    }
};

void solve()
{
    const int nsteps = 12964419;
    std::vector<int> tape(nsteps*2, 0);
    char state = 'A';
    auto tape_iter = tape.begin() + nsteps;
    std::unordered_map<char, RuleSet> rules{
        {'A', RuleSet{1, +1, 'B', 0, +1, 'F'}},
        {'B', RuleSet{0, -1, 'B', 1, -1, 'C'}},
        {'C', RuleSet{1, -1, 'D', 0, +1, 'C'}},
        {'D', RuleSet{1, -1, 'E', 1, +1, 'A'}},
        {'E', RuleSet{1, -1, 'F', 0, -1, 'D'}},
        {'F', RuleSet{1, +1, 'A', 0, -1, 'E'}},
    };
    for (size_t i = 0; i < nsteps; i++)
        std::tie(tape_iter, state) = rules[state].apply(tape_iter);
    
    std::cout << "Solution: " << std::count(tape.begin(), tape.end(), 1) << std::endl;
}

int main()
{
    auto started = std::chrono::high_resolution_clock::now();
    solve();
    auto done = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(done-started).count() << "ms\n";
}