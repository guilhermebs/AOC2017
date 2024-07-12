#include <vector>
#include <iostream>
#include <chrono>

void solve_pt1()
{
    const int input = 277678;
    int x = 0;
    int y = 1;
    int start = 1;
    int end = 1;
    int size = 1;
    while (end <= input)
    {
        size += 2;
        start = end + 1;
        end = size * size;
        x++;
        y--;
    }
    int dist2corner = size;
    for (int i = 1; i <= 4; i++) 
    {
        auto c = start - 1 + (size - 1) * i;
        dist2corner = std::min(dist2corner, abs(input - c));
    }
    std::cout << "Part 1 solution: " << size - 1 - dist2corner << std::endl;
}

std::pair<int, int> nextxy(const std::pair<int, int> &xy)
{
    auto &[x, y] = xy;
    if (x > 0 && y == -x) return std::make_pair(x + 1, y);
    if (x > 0 && abs(x) > abs(y)) return std::make_pair(x, y + 1);
    if (y > 0 && (y == x || abs(y) > abs(x))) return std::make_pair(x - 1, y);
    if (x < 0 && (x == -y || abs(x) > abs(y))) return std::make_pair(x, y - 1);
    if (y < 0 && (x == y || abs(y) > abs(x))) return std::make_pair(x + 1, y);
    std::cout << "Error!" << std::endl;
};

size_t xy2idx(const std::pair<int, int> &xy)
{
    const auto &[x, y] = xy;
    if (x == 0 && y == 0) return 1;
    auto l0 = std::max(std::abs(x), std::abs(y));
    auto size = l0 * 2 + 1;
    auto idx = (size - 2) * (size - 2) + 1;
    std::pair<int, int> xyi{l0, 1-l0};
    while (xyi != xy)
    {
        xyi = nextxy(xyi);
        idx++;
    }
    return idx;
};

void solve_pt2()
{
    const int input = 277678;
    std::vector<int> values{1, 1};
    std::pair<int, int> xy{1, 0};
    auto idx = 2;
    while (values.back() < input)
    {
        xy = nextxy(xy);
        auto &[x, y] = xy;
        idx++;
        int val = 0;
        for (int xx = x-1; xx <= x+1; xx++)
        {
            for (int yy = y-1; yy <= y+1; yy++)
            {
                auto i = xy2idx({xx, yy}) - 1;
                if (i < values.size()) val += values[i];
            }
        }
        values.push_back(val);
    }
    std::cout << "Part 2 solution: "  << values.back() << std::endl;

}
 
int main()
{
    auto started = std::chrono::high_resolution_clock::now();
    solve_pt1();
    solve_pt2();
    auto done = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(done-started).count() << "ms\n";
}