#include <iostream>
#include <chrono>
#include <list>

void solve_pt1()
{
    const uint step_size = 349;
    std::list<uint> buffer{0};
    size_t cur_pos = 0;
    for (int i=1; i<=2017; i++)
    {
        cur_pos = (cur_pos + step_size) % buffer.size();
        auto p = buffer.begin();
        for (size_t _ = 0; _ <= cur_pos; _++)
        {
            p++;
        }
        buffer.insert(p, i);
        cur_pos++;
    }
    auto p = buffer.begin();
    for (size_t _ = 0; _ <= cur_pos; _++)
        p++;
 
    std::cout << "Part 1 solution: " << *p << std::endl;
}

void solve_pt2()
{
    const uint step_size = 349;
    size_t cur_pos = 0;
    size_t rounds = 50000000;
    size_t sol_pt2 = 0;
    for (size_t i=1; i<=rounds; i++)
    {
        cur_pos = (cur_pos + step_size) % i;
        if (cur_pos == 0)
            sol_pt2 = i;
        cur_pos++;
    }
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