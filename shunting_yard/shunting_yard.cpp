#include <string>
#include <vector>
#include <cassert>
#include <iostream>
#include <algorithm>

struct Reverse {
    Reverse() = default;
    Reverse(int from, int to) : from(from), to(to) {}

    int from = 0;
    int to = 0;
};

using Reverses = std::vector<Reverse>;

std::string apply(std::string a, const Reverse& reverse) {
    std::reverse(a.begin() + reverse.from, a.begin() + reverse.to + 1);
    return a;
}

std::string apply(std::string a, const Reverses& reverses) {
    for (const auto& reverse : reverses) {
        a = apply(a, reverse);
    }
    return a;
}

int getDiffCount(const std::string& a, const std::string& b) {
    assert(a.size() == b.size());

    int c = 0;
    for (int i = 0, size = a.size(); i < size; ++i) {
        if (a[i] != b[i]) {
            ++c;
        }
    }
    return c;
}

Reverses swapSteps(int i, int j) {
    if (i == j) {
        std::cerr << "Swap with itself" << std::endl;
        return {};
    }

    int low = std::min(i, j);
    int high = std::max(i, j);

    if (low + 1 == high || low + 2 == high) {
        return {{i, j}};
    }

    return {
        {low, high},
        {low + 1, high - 1}
    };
}

Reverse getGreedyCandidate(
    const std::string& original, const std::string& expected)
{
    assert(original.size() == expected.size());

    int size = original.size();
    int beforeDiff = getDiffCount(original, expected);

    int bestDiff = 0;
    Reverse bestReverse;
    for (int i = 0; i < size; ++i) {
        for (int j = i + 1; j < size; ++j) {
            std::string new_original = apply(original, {i, j});
            int afterDiff = getDiffCount(new_original, expected);
            if (beforeDiff - afterDiff > bestDiff) {
                bestDiff = beforeDiff - afterDiff;
                bestReverse = {i, j};
            }
        }
    }
    if (bestDiff > 0) {
        return bestReverse;
    }
    return Reverse{};
}

Reverses getSwapCandidate(
    const std::string& original, const std::string& expected)
{
    assert(original.size() == expected.size());

    int size = original.size();

    // 2-way
    for (int i = 0; i < size; ++i) {
        if (original[i] != expected[i]) {
            for (int j = i+1; j < size; ++j) {
                if (original[j] == expected[i] && original[i] == expected[j]) {
                    return swapSteps(i, j);
                }
            }
        }
    }
    // N-way
    for (int i = 0; i < size; ++i) {
        if (original[i] != expected[i]) {
            for (int j = i+1; j < size; ++j) {
                if (original[j] != expected[j] && original[i] == expected[j]) {
                    return swapSteps(i, j);
                }
            }
        }
    }
    return {};
}

int main() {
    std::string original;
    std::string expected;

    std::getline(std::cin, original);
    std::getline(std::cin, expected);

    std::vector<Reverse> reverses;

    int step = 0;
    while (original != expected) {
        std::cerr << "At step " << step++
            << " diff = " << getDiffCount(original, expected) << std::endl;
        Reverse r = getGreedyCandidate(original, expected);
        if (r.from == r.to) {
            std::cerr << "Empty reverse after greed: diffCount = "
                << getDiffCount(original, expected) << std::endl;
            break;
        }
        original = apply(original, r);
        reverses.push_back(r);
    }

    while (original != expected) {
        Reverses rs = getSwapCandidate(original, expected);
        if (rs.empty()) {
            std::cerr << "Empty candidate after swaps: diffCount = "
                << getDiffCount(original, expected) << std::endl;
            break;
        }
        original = apply(original, rs);
        reverses.insert(reverses.end(), rs.begin(), rs.end());
    }

    std::cout << reverses.size() << std::endl;
    for (auto r : reverses) {
        std::cout << r.from << " " << r.to << std::endl;
    }
}
