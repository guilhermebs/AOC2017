#include <iostream>
#include <chrono>
#include <fstream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include "helper.hpp"

void solve_pt1()
{
    std::ifstream file("inputs/day22");
    std::string line;
    std::unordered_set<std::tuple<int, int>> infected;
    int y = 0;
    while (getline(file, line))
    {
        for (int x=0; x< (int) line.size(); x++)
        {
            if (line[x] == '#')
                infected.insert(std::make_tuple(x, y));
        }
        y++;
    }
    std::vector<std::tuple<int, int>> directions({
        {0, -1}, {1, 0}, {0, 1}, {-1, 0}
    });
    auto position = std::make_tuple(12, 12);
    auto direction = 0;
    auto turn_left = [](int direction){ return (direction == 0)? 3 : direction - 1; };
    auto turn_right = [](int direction){ return (direction == 3)? 0 : direction + 1; };
    int part1_solution = 0;
    for (size_t iter = 0; iter < 10000; iter++)
    {
        if (infected.contains(position))
        {
            direction = turn_right(direction);
            infected.erase(position);
        }
        else
        {
            direction = turn_left(direction);
            infected.insert(position);
            part1_solution++;
        }
        std::get<0>(position) += std::get<0>(directions[direction]);
        std::get<1>(position) += std::get<1>(directions[direction]);
    }
    std::cout << "Part 1 solution: " << part1_solution << std::endl;
    
}

enum NodeState
{
    CLEAN,
    WEAKENED,
    INFECTED,
    FLAGGED
};


void solve_pt2()
{
    std::ifstream file("inputs/day22");
    std::string line;
    std::unordered_map<std::tuple<int, int>, NodeState> node_state;
    int y = 0;
    while (getline(file, line))
    {
        for (int x=0; x< (int) line.size(); x++)
        {
            if (line[x] == '#')
                node_state[std::make_tuple(x, y)] = NodeState::INFECTED;
        }
        y++;
    }
    std::vector<std::tuple<int, int>> directions({
        {0, -1}, {1, 0}, {0, 1}, {-1, 0}
    });
    auto position = std::make_tuple(12, 12);
    auto direction = 0;
    auto turn_left = [](int direction){ return (direction == 0)? 3 : direction - 1; };
    auto turn_right = [](int direction){ return (direction == 3)? 0 : direction + 1; };
    auto reverse_dir = [](int direction){  return (direction < 2)? direction + 2 : direction - 2; };
    int part2_solution = 0;
    for (size_t iter = 0; iter < 10000000; iter++)
    {
        if (!node_state.contains(position)) node_state[position] = NodeState::CLEAN;
        switch (node_state[position])
        {
        case NodeState::CLEAN:
            direction = turn_left(direction);
            node_state[position] = NodeState::WEAKENED;
            break;
        case NodeState::WEAKENED:
            node_state[position] = NodeState::INFECTED;
            part2_solution++;
            break;
        case NodeState::INFECTED:
            direction = turn_right(direction);
            node_state[position] = NodeState::FLAGGED;
            break;
        case NodeState::FLAGGED:
            direction = reverse_dir(direction);
            node_state[position] = NodeState::CLEAN;
            break;
        default:
            break;
        }
        std::get<0>(position) += std::get<0>(directions[direction]);
        std::get<1>(position) += std::get<1>(directions[direction]);
    }
    std::cout << "Part 2 solution: " << part2_solution << std::endl;
    
}


int main()
{
    auto started = std::chrono::high_resolution_clock::now();
    solve_pt1();
    solve_pt2();
    auto done = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(done-started).count() << "ms\n";
}

