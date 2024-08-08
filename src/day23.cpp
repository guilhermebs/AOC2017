#include <fstream>
#include <iostream>
#include <chrono>
#include <string>
#include <vector>
#include <variant>
#include <optional>
#include <unordered_map>

struct Instruction
{
    std::string op_name;
    char val1;
    std::variant<char, int64_t> val2;
    Instruction(const std::string &line)
    {

        op_name = line.substr(0,3);
        val1 = line[4];
        if (line.size() > 6)
        {
            if (isdigit(line[6]) || line[6] == '-')
                val2 = stoi(line.substr(6));
            else
                val2 = line[6];
        }
   }
    int64_t get_val2(std::unordered_map<char, int64_t> &registers) const
    {
        if (auto rb = std::get_if<char>(&val2))
            return registers[*rb];
        else
            return std::get<int64_t>(val2);
    }

    void print() const
    {
        
        std::cout << op_name << " " << val1 << " ";
        if (auto rb = std::get_if<char>(&val2))
            std::cout << rb;
        else
            std::cout << std::get<int64_t>(val2);
        std::cout << std::endl;
    }
};

void execute_intruction(std::vector<Instruction>::iterator &instruction_iter, std::unordered_map<char, int64_t> &registers)
{
    if (instruction_iter->op_name == "snd")
    {
        registers['@'] = registers[instruction_iter->val1];
        instruction_iter++;
    }
    else if (instruction_iter->op_name == "set")
    {
        registers[instruction_iter->val1] = instruction_iter->get_val2(registers);
        instruction_iter++;
    }
    else if (instruction_iter->op_name == "sub")
    {
        registers[instruction_iter->val1] -= instruction_iter->get_val2(registers);
        instruction_iter++;
    }
    else if (instruction_iter->op_name == "mul")
    {
        registers[instruction_iter->val1] *= instruction_iter->get_val2(registers);
        instruction_iter++;
    }
    else if (instruction_iter->op_name == "jnz")
    {
        if (registers[instruction_iter->val1] != 0)
            instruction_iter += instruction_iter->get_val2(registers);
        else
            instruction_iter++;
    }
    else
    {
        std::cerr << "Error!: " << instruction_iter->op_name << std::endl;
    }
}

void solve_pt1()
{
    std::ifstream file("inputs/day23");
    std::vector<Instruction> instructions;
    std::string line;
    while (getline(file, line))
    {
        instructions.emplace_back(line);
    }
    std::unordered_map<char, int64_t> registers{{'1', 1}};
    auto instruction_iter = instructions.begin();
    int sol_pt1 = 0;
    while (instruction_iter < instructions.end())
    {
        sol_pt1 += instruction_iter->op_name == "mul";
        execute_intruction(instruction_iter, registers);
    }
    std::cout << "Part 1 solution: " << sol_pt1 << std::endl;
}

void print_registers(const std::unordered_map<char, int64_t> &registers)
{
    for (char k='a'; k <= 'h'; k++)
        std::cout << k << ": " << registers.at(k) << " ";
    std::cout << std::endl;
}

bool is_prime(int n)
{
    if (n % 2 == 0) return true;
    for (int i = 3; i < (int) sqrt(n) + 2; i += 2)
    {
        if (n%i == 0) return true;
    }
    return false;
}

void solve_pt2()
{
    int start = 106500;
    int end = 123500;
    int part2_sol = 0;
    for (int n = start; n <= end; n += 17)
    {
        part2_sol += is_prime(n);
    }

    std::cout << "Part 2 solution: " << part2_sol << std::endl;
}

void _solve_pt2()
{
    std::ifstream file("inputs/day23");
    std::vector<Instruction> instructions;
    std::string line;
    while (getline(file, line))
    {
        if(!line.starts_with("//"))
            instructions.emplace_back(line);
    }
    std::unordered_map<char, int64_t> registers{{'1', 1}, {'a', 1}, {'b', 0}, {'c', 0}, {'d', 0}, {'e', 0}, {'f', 0}, {'g', 0}, {'h', 0}};
    auto instruction_iter = instructions.begin();
    auto prev_h = registers['h'];
    while (instruction_iter < instructions.end())
    {
        execute_intruction(instruction_iter, registers);
        if (registers['h'] != prev_h)
        {
            print_registers(registers);
            //instruction_iter->print();
            prev_h = registers['h'];
        }
        if(instruction_iter - instructions.begin() == 20)
        {
            std::cout << "Out of loop 1: " << std::endl;
            print_registers(registers);
        }
    }
    std::cout << "Part 2 solution: " << registers['h'] << std::endl;
    // Count of all prime numbers untill 106500
}


int main()
{
    auto started = std::chrono::high_resolution_clock::now();
    //solve_pt1();
    solve_pt2();
    auto done = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(done-started).count() << "ms\n";
}