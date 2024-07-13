#include <iostream>
#include <chrono>
#include <fstream>
#include <unordered_map>
#include <functional>
#include "helper.hpp"

using Registry = std::unordered_map<std::string, int>;

class Instruction
{
    public:
        Instruction(const std::string &line)
        {
            auto tokens = tokenize(line, " ");
            target = tokens[0];
            if (tokens[1] == "inc") operation = *([](int a, int b){ return a+b; });
            else if (tokens[1] == "dec") operation = *([](int a, int b){ return a-b; });
            ammount = stoi(tokens[2]);
            condition_reg = tokens[4];
            if (tokens[5] == ">") condition_op = *([](int a, int b) { return a > b; });
            else if (tokens[5] == ">=") condition_op = *([](int a, int b) { return a >= b; });
            else if (tokens[5] == "<") condition_op = *([](int a, int b) { return a < b; });
            else if (tokens[5] == "<=") condition_op = *([](int a, int b) { return a <= b; });
            else if (tokens[5] == "==") condition_op = *([](int a, int b) { return a == b; });
            else if (tokens[5] == "!=") condition_op = *([](int a, int b) { return a != b; });
            condition_val = stoi(tokens[6]);
        }

        void apply(Registry &registry) const
        {
            if (condition_op(registry[condition_reg], condition_val))
                registry[target] = operation(registry[target], ammount);
        }

    
    private:
        std::string target;
        int (*operation) (int, int);
        int ammount;
        std::string condition_reg;
        bool (*condition_op) (int, int);
        int condition_val;
};

void solve()
{
    std::ifstream file("inputs/day08");
    std::string line;
    Registry registry;
    int part2_sol = INT_MIN;
    while (getline(file, line))
    {
        Instruction inst(line);
        inst.apply(registry);
        for (auto &[_, v]: registry)
            part2_sol = std::max(part2_sol, v);


    }
    int max_value = INT_MIN;
    for (auto &[_, v]: registry)
        max_value = std::max(max_value, v);

    std::cout << "Part 1 solution: " << max_value << std::endl;
    std::cout << "Part 2 solution: " << part2_sol << std::endl;
}

int main()
{
    auto started = std::chrono::high_resolution_clock::now();
    solve();
    auto done = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(done-started).count() << "ms\n";
}