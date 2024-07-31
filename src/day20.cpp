#include <iostream>
#include <chrono>
#include <fstream>
#include <array>
#include <unordered_set>
#include "helper.hpp"

inline int mdist(std::array<int, 3> x, std::array<int, 3> y)
{
    return abs(x[0] - y[0]) + abs(x[1] - y[1]) + abs(x[2] - y[2]);
}
inline int norm1(std::array<int, 3> x)
{
    return abs(x[0]) + abs(x[1]) + abs(x[2]);
}


struct Particle
{
    std::array<int, 3> p;
    std::array<int, 3> v;
    std::array<int, 3> a;

    bool operator< (const Particle &other) const
    {
        if (norm1(a) < norm1(other.a)) return true;
        if (norm1(a) > norm1(other.a)) return false;
        if (norm1(v) < norm1(other.v)) return true;
        if (norm1(v) > norm1(other.v)) return false;
        if (norm1(p) < norm1(other.p)) return true;
        if (norm1(p) > norm1(other.p)) return false;
        return false;
    }

    Particle time_step() const
    {
        auto new_v = v;
        auto new_p = p;
        for (size_t i = 0; i < 3; i++)
        {
            new_v[i] += a[i];
            new_p[i] += new_v[i];
        }
        return Particle{new_p, new_v, a};
    }

    bool collides(const Particle &other) const
    {
        auto p1 = time_step();
        auto p2 = other.time_step();
        for (int i = 0; i < 1000; i++)
        {
            if (mdist(p1.p, p2.p) == 0) return true;
            p1 = p1.time_step();
            p2 = p2.time_step();
        }
        return false;
    }
};


void solve()
{
    std::ifstream file("inputs/day20");
    std::string line;
    std::vector<Particle> particles;
    while (getline(file, line))
    {
        auto pva = tokenize(line, ", ");
        auto pstr = tokenize(pva[0].substr(3, pva[0].length() - 4), ",");
        auto vstr = tokenize(pva[1].substr(3, pva[1].length() - 4), ",");
        auto astr = tokenize(pva[2].substr(3, pva[2].length() - 4), ",");

        particles.push_back({
            {stoi(pstr[0]), stoi(pstr[1]), stoi(pstr[2])},
            {stoi(vstr[0]), stoi(vstr[1]), stoi(vstr[2])},
            {stoi(astr[0]), stoi(astr[1]), stoi(astr[2])},
        });
    }

    auto min_ptr = std::min_element(particles.begin(), particles.end());
    std::cout << "Part 1 solution: " << (min_ptr - particles.begin()) << std::endl;


    //Particle collision:
    std::unordered_set<int> collides{};
    for (size_t i = 0; i < particles.size(); i++)
    {
        auto pi = particles[i];
        for (size_t j = i + 1; j < particles.size(); j++)
        {
            auto pj = particles[j];
            if (pi.collides(pj))
            {
                collides.insert(i);
                collides.insert(j);
            }
        }
    }
    
    std::cout << "Part 2 solution: " << (particles.size() - collides.size()) << std::endl;
    
}


int main()
{
    auto started = std::chrono::high_resolution_clock::now();
    solve();
    auto done = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(done-started).count() << "ms\n";
}