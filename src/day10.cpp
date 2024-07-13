#include <iostream>
#include <chrono>
#include <vector>
#include <array>
#include <numeric>
#include <iomanip>

const size_t LIST_LEN = 256;

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

void solve_pt1()
{
    const std::vector<int> lengths = {70,66,255,2,48,0,54,48,80,141,244,254,160,108,1,41};
    std::vector<int> list(LIST_LEN);
    std::iota(list.begin(), list.end(), 0);
    int current_pos = 0;
    int skip_size = 0;
    apply_flips(list, lengths, current_pos, skip_size);
    std::cout << "Part 1 solution: " << list[0] * list[1] << std::endl;
}

void solve_pt2()
{
    const std::string lengths_str = "70,66,255,2,48,0,54,48,80,141,244,254,160,108,1,41";
    //const std::string lengths_str = "";
    std::vector<int> lengths;
    std::transform(lengths_str.begin(), lengths_str.end(), std::back_inserter(lengths), [](char c) { return (int) c; });
    const std::vector<int> append = {17, 31, 73, 47, 23};
    lengths.insert(lengths.end(), append.begin(), append.end());
    std::vector<int> list(LIST_LEN);
    std::iota(list.begin(), list.end(), 0);
    int current_pos = 0;
    int skip_size = 0;
    for (int _ = 0; _ < 64; _++)
        apply_flips(list, lengths, current_pos, skip_size);
    for (auto l: list)
        std::cout <<  l << ", ";
    std::cout << std::endl;
    for (int b = 0; b < 16; b++)
    {
        int bv = 0;
        //std::cout << "Here!" << std::endl;
        for (int i=b*16; i<(b+1)*16; i++)
        {
            bv ^= list[i];
        }
        std::cout << std::hex << std::setw(2) << std::setfill('0') << bv;
    }
    std::cout << std::endl;
}


int main()
{
    auto started = std::chrono::high_resolution_clock::now();
    solve_pt1();
    solve_pt2();
    auto done = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(done-started).count() << "ms\n";
}