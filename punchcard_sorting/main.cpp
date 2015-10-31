#include <iostream>

#include <array>
#include <vector>

#include <algorithm>
#include <chrono>
#include <string>

#include <boost/sort/sort.hpp>

constexpr std::size_t maxLength = 63;

using Line = std::array<char, maxLength + 1>;

struct Timer {
    Timer(std::string message)
        : start(std::chrono::system_clock::now()),
          message(std::move(message)) {}

    ~Timer() {
        auto end = std::chrono::system_clock::now();
        std::chrono::duration<double> diff = end - start;
        std::cerr << message << " " << diff.count() << std::endl;
    }

    std::chrono::system_clock::time_point start;
    std::string message;
};

void printLines(const std::vector<Line>& lines) {
    Timer t("Time to print lines");
    for (const auto& line : lines) {
        std::cout << line.data() << '\n';
    }
}

void sortLines(std::vector<Line>& lines) {
    Timer t("Time to sort lines");
    boost::sort::spreadsort::string_sort(lines.begin(), lines.end(), '\0');
}

void readLine(Line& line) { std::cin >> line.data(); }

std::vector<Line> readLines(std::size_t numberOfLines) {
    std::vector<Line> lines;
    lines.resize(numberOfLines);

    Timer t("Time to read lines");

    for (std::size_t lineIndex = 0; lineIndex < numberOfLines; ++lineIndex) {
        readLine(lines[lineIndex]);
    }

    return lines;
}

int main() {
    std::ios::sync_with_stdio(false);

    std::size_t numberOfLines = 0;
    std::cin >> numberOfLines;

    auto lines = readLines(numberOfLines);

    sortLines(lines);
    printLines(lines);
}
