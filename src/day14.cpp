#include <iostream>
#include <chrono>
#include <vector>
#include <array>
#include <deque>
#include <numeric>


const size_t LIST_LEN = 256;
const size_t BITS_LEN = 128;

void apply_flips(std::vector<int> &list, const std::vector<int> &lengths, int &current_pos, int &skip_size)
{
    for (auto l: lengths)
    {
        auto iter = list.begin() + current_pos;
        std::vector<int> sublist;
        for (int i = 0; i < l; i++)
        {
            sublist.push_back(*iter);
            iter++;
            if (iter == list.end())
                iter = list.begin();
        }
        std::reverse(sublist.begin(), sublist.end());
        iter = list.begin() + current_pos;
        for (int i = 0; i < l; i++)
        {
            *iter = sublist[i];
            iter++;
            if (iter == list.end())
                iter = list.begin();
        }
        current_pos += l + skip_size;
        current_pos %= list.size();
        skip_size++;
    }
}

std::bitset<BITS_LEN> knot_hash(const std::string &input)
{
    std::vector<int> lengths;
    std::transform(input.begin(), input.end(), std::back_inserter(lengths), [](char c) { return (int) c; });
    const std::vector<int> append = {17, 31, 73, 47, 23};
    lengths.insert(lengths.end(), append.begin(), append.end());
    std::vector<int> list(LIST_LEN);
    std::iota(list.begin(), list.end(), 0);
    int current_pos = 0;
    int skip_size = 0;
    for (int _ = 0; _ < 64; _++)
        apply_flips(list, lengths, current_pos, skip_size);
    std::bitset<BITS_LEN> result;
    for (int b = 0; b < 16; b++)
    {
        std::bitset<BITS_LEN> bv(0);
        for (int i=b*16; i<(b+1)*16; i++)
        {
            bv ^= list[i];
        }
        result |= bv << (15 - b) * 8 ;
    }
    return result;
}


inline std::pair<int, int> idx2coords(int idx)
{
    return std::make_pair(idx%BITS_LEN, idx/BITS_LEN);
}

inline int coords2idx(const std::pair<int, int> &coords)
{
    return coords.first + coords.second * BITS_LEN;
}

void find_region (std::bitset<BITS_LEN*BITS_LEN> &disk)
{

    if (!disk.any()) return;
    std::deque<int> queue;
    for (size_t i=0; i<disk.size(); i++)
    {
        if (disk[i])
        {
            queue.push_back(i);
            disk.flip(i);
            break;
        }
    }

    std::vector<int> neighbours;
    neighbours.reserve(4);
    while (queue.size())
    {
        int idx = queue.front();
        queue.pop_front();
        auto [x, y] = idx2coords(idx);
        neighbours.clear();
        if (x > 0)
            neighbours.push_back(coords2idx(std::make_pair(x-1, y)));
        if (x < BITS_LEN - 1)
            neighbours.push_back(coords2idx(std::make_pair(x+1, y)));
        if (y > 0)
            neighbours.push_back(coords2idx(std::make_pair(x, y-1)));
        if (y < BITS_LEN - 1)
            neighbours.push_back(coords2idx(std::make_pair(x, y+1)));
        for (auto n: neighbours)
        {
            if (disk[n])
            {
                disk.flip(n);
                queue.push_back(n);
            }
        }
    }
}


void solve()
{
    const std::string input = "ugkiagan";
    std::bitset<BITS_LEN*BITS_LEN> disk;
    for (int i=0; i<128; i++)
    {
        auto key = input + "-" + std::to_string(i);
        auto b = knot_hash(key);
        disk |= std::bitset<BITS_LEN*BITS_LEN>(b.to_string()) << ((BITS_LEN - 1) - i) * BITS_LEN;
    }
    std::cout << "Part 1 solution: " << disk.count() << std::endl;

    int part2_sol = 0;
    while (disk.any())
    {
       part2_sol++; 
       find_region(disk);
    }
    
    std::cout << "Part 2 solution: " << part2_sol << std::endl;
}

int main()
{
    auto started = std::chrono::high_resolution_clock::now();
    solve();
    auto done = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(done-started).count() << "ms\n";
}