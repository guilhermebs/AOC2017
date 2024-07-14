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

std::optional<int64_t> execute_intruction(std::vector<Instruction>::iterator &instruction_iter, std::unordered_map<char, int64_t> &registers)
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
    else if (instruction_iter->op_name == "add")
    {
        registers[instruction_iter->val1] += instruction_iter->get_val2(registers);
        instruction_iter++;
    }
    else if (instruction_iter->op_name == "mul")
    {
        registers[instruction_iter->val1] *= instruction_iter->get_val2(registers);
        instruction_iter++;
    }
    else if (instruction_iter->op_name == "mod")
    {
        registers[instruction_iter->val1] %= instruction_iter->get_val2(registers);
        instruction_iter++;
    }
    else if (instruction_iter->op_name == "rcv")
    {
        if (registers[instruction_iter->val1] != 0)
        {
            //instruction_iter++;
            return registers['@'];
        }
        instruction_iter++;
    }
    else if (instruction_iter->op_name == "jgz")
    {
        if (registers[instruction_iter->val1] > 0)
            instruction_iter += instruction_iter->get_val2(registers);
        else
            instruction_iter++;
    }
    else
    {
        std::cerr << "Error!" << std::endl;
    }
    return {};
}

void solve_pt1()
{
    std::ifstream file("inputs/day18");
    std::vector<Instruction> instructions;
    std::string line;
    while (getline(file, line))
    {
        instructions.emplace_back(line);
    }
    std::unordered_map<char, int64_t> registers;
    auto instruction_iter = instructions.begin();
    while (true)
    {
        if(auto part1_result = execute_intruction(instruction_iter, registers))
        {
            std::cout << "Part 1 result: " << *part1_result << std::endl;
            break;
        }
    }
}

void execute_pt2(
    std::vector<Instruction>::iterator &instruction_iter, std::unordered_map<char, int64_t> &registers,
    std::deque<int64_t> &queue_in, std::deque<int64_t> &queue_out)
{
    while (true)
    {
        if (instruction_iter->op_name == "snd")
        {
            queue_out.push_back(registers[instruction_iter->val1]);
            instruction_iter++;
        }
        else if (instruction_iter->op_name == "set")
        {
            registers[instruction_iter->val1] = instruction_iter->get_val2(registers);
            instruction_iter++;
        }
        else if (instruction_iter->op_name == "add")
        {
            registers[instruction_iter->val1] += instruction_iter->get_val2(registers);
            instruction_iter++;
        }
        else if (instruction_iter->op_name == "mul")
        {
            registers[instruction_iter->val1] *= instruction_iter->get_val2(registers);
            instruction_iter++;
        }
        else if (instruction_iter->op_name == "mod")
        {
            registers[instruction_iter->val1] %= instruction_iter->get_val2(registers);
            instruction_iter++;
        }
        else if (instruction_iter->op_name == "rcv")
        {
            if (queue_in.size())
            {
                registers[instruction_iter->val1] = queue_in.front();
                queue_in.pop_front();
            }
            else
                return;
            instruction_iter++;
        }
        else if (instruction_iter->op_name == "jgz")
        {
            if (registers[instruction_iter->val1] > 0)
                instruction_iter += instruction_iter->get_val2(registers);
            else
                instruction_iter++;
        }
        else
        {
            throw std::runtime_error("Invalid state!");
            return;
        }
    }
}

void solve_pt2()
{
    std::ifstream file("inputs/day18");
    std::vector<Instruction> instructions;
    std::string line;
    while (getline(file, line))
        instructions.emplace_back(line);

    std::unordered_map<char, int64_t> registers_p0{{'p', 0}, {'1', 1}}, registers_p1{{'p', 1}, {'1', 1}};
    std::deque<int64_t> queue_01, queue_10;
    auto instruction_iter_p0 = instructions.begin();
    auto instruction_iter_p1 = instructions.begin();
    int sol_pt2 = 0;
    do
    {
        execute_pt2(instruction_iter_p0, registers_p0, queue_10, queue_01);
        execute_pt2(instruction_iter_p1, registers_p1, queue_01, queue_10);
        sol_pt2 += queue_10.size();
    } while (queue_01.size() || queue_10.size());
    std::cout << "Part 2 solution: " << sol_pt2 << std::endl;
    
}
int main()
{
    auto started = std::chrono::high_resolution_clock::now();
    solve_pt1();
    solve_pt2();
    auto done = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(done-started).count() << "ms\n";
}