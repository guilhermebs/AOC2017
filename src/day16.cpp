#include <fstream>
#include <iostream>
#include <chrono>
#include <string>
#include <vector>

void spin (std::string &seq, int x)
{
    auto substr = seq.substr(seq.size() - x);
    seq.erase(seq.size() - x);
    seq.insert(0, substr);
}

void exchange (std::string &seq, int a, int b)
{
    auto tmp = seq[a];
    seq[a] = seq[b];
    seq[b] = tmp;
}

void pair_(std::string &seq, char a, char b)
{
    auto ia = seq.find(a);
    auto ib = seq.find(b);
    seq[ib] = a;
    seq[ia] = b;
}

void dance(std::string &seq)
{
    std::ifstream file("inputs/day16");
    std::string command;
    while (getline(file, command, ','))
    {
        auto d = command.find('/');
        switch (command[0])
        {
        case 's':
            spin(seq, stoi(command.substr(1)));
            break;

        case 'x':
            exchange(seq, stoi(command.substr(1, d - 1)), stoi(command.substr(d+1)));
            break;
        
        case 'p':
            pair_(seq, command[1], command[3]);
               
        default:
            break;
        }
    }
}


void solve_pt1()
{
    std::string seq = "abcdefghijklmnop";
    dance(seq);
    std::cout << "Part 1 solution: " << seq << std::endl;
}

void solve_pt2()
{
    std::string seq = "abcdefghijklmnop";
    uint target_reps = 1000000000;
    uint warmup_reps = 100;
    for (size_t i = 0; i < warmup_reps; i++)
    {
        dance(seq);
    }
    std::cout << seq << std::endl;
    std::vector<std::string> cycle;
    do
    {
        cycle.push_back(seq);
        dance(seq);
        
    } while (seq != cycle.front());
    auto i_last = (target_reps - warmup_reps) % cycle.size();
    std::cout << "Part 2 solution: " << cycle[i_last] << std::endl;
}

int main()
{
    auto started = std::chrono::high_resolution_clock::now();
    solve_pt1();
    solve_pt2();
    auto done = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(done-started).count() << "ms\n";
}