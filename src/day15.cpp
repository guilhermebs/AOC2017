#include <iostream>
#include <chrono>

typedef unsigned long long ull;

inline ull next_value(const ull factor, const ull value)
{
    return (value * factor) % 2147483647ULL;
}

const ull MASK = (1 << 16) - 1;

inline bool bit_match(const ull valA, const ull valB)
{
    return (valA & MASK) == (valB & MASK);
}

ull next_value_pt2(const ull factor, const ull value, const ull multiple)
{
    ull result = value;
    while (true)
    {
        result = (result * factor) % 2147483647ULL;
        if ((result % multiple) == 0)
            return  result;
    }
}

void solve()
{
    const ull factorA = 16807;
    const ull factorB = 48271;
    ull valueA = 516;//65;
    ull valueB = 190;//8921;
    const ull nr_rep = 40000000;
    int sol_part1 = 0;
    for (ull i=0; i<=nr_rep; i++)
    {
        valueA = next_value(factorA, valueA);
        valueB = next_value(factorB, valueB);
        sol_part1 += bit_match(valueA, valueB);
    }
    std::cout << "Part 1 solution: " << sol_part1 << std::endl;

    const ull multipleA = 4;
    const ull multipleB = 8;
    valueA = 516;
    valueB = 190;
    const ull nr_rep2 = 5000000;
    int sol_part2 = 0;
    for (ull i=0; i<=nr_rep2; i++)
    {
        valueA = next_value_pt2(factorA, valueA, multipleA);
        valueB = next_value_pt2(factorB, valueB, multipleB);
        sol_part2 += bit_match(valueA, valueB);
        //std::cout << valueA << " " << valueB << std::endl;
    }
    std::cout << "Part 2 solution: " << sol_part2 << std::endl;



}


int main()
{
    auto started = std::chrono::high_resolution_clock::now();
    solve();
    auto done = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(done-started).count() << "ms\n";
}