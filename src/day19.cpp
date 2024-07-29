#include <fstream>
#include <iostream>
#include <chrono>
#include <string>
#include <sstream>
#include <vector>
#include <optional>

const int NCOL = 202;

struct State
{
    int pos;
    int origin;
    int preference;
    std::string letters; 
};


bool next_state(State &state, const std::string &tubes)
{
    auto prev_origin = state.origin;
    state.origin = state.pos;
    if (isalpha(tubes[state.pos]))
        state.letters += tubes[state.pos];
    if (tubes[state.preference] != ' ')
        state.pos = state.preference;
    else
    {
        for (auto nx: {state.pos - NCOL, state.pos - 1, state.pos + NCOL, state.pos + 1})
        {
            if (nx != prev_origin && tubes[nx] != ' ')
            {
                state.pos = nx;
                break;
            }
        }
    }
    state.preference = state.pos + (state.pos - state.origin);
    return (state.origin != state.pos);
}

void solve_pt1()
{
    std::ifstream file("inputs/day19");
    std::stringstream buffer;
    buffer << file.rdbuf();
    auto tubes = buffer.str();
    int start_x = 113;
    State init_state{
        start_x,
        start_x,
        start_x + NCOL,
        ""
    };
    auto s = init_state;
    int count = 1;
    while (next_state(s, tubes))
        count++;
    std::cout << "Part 1 solution: " << s.letters << std::endl;
    std::cout << "Part 2 solution: " << count << std::endl;
    
}

int main()
{
    auto started = std::chrono::high_resolution_clock::now();
    solve_pt1();
    //solve_pt2();
    auto done = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(done-started).count() << "ms\n";
}