#include <iostream>

#include <array>
#include <vector>

#include <algorithm>
#include <chrono>
#include <string>

#include <future>

#include <boost/sort/sort.hpp>
#include <boost/lexical_cast.hpp>

constexpr std::size_t maxLength = 64;

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

void sortRange(std::vector<Line>::iterator begin, std::vector<Line>::iterator end) {
    Timer t("Time to sort subrange of size " +
            boost::lexical_cast<std::string>(std::distance(begin, end)));
    boost::sort::spreadsort::string_sort(begin, end, '\0');
}

void sortLines(std::vector<Line>& lines) {
    Timer t("Time to sort lines");
    auto partition = lines.begin() + lines.size() / 2;

    auto firstHandle = std::async(std::launch::async, [&lines, partition]() {
        sortRange(lines.begin(), partition);
    });

    auto lastHandle = std::async(std::launch::async, [&lines, partition]() {
        sortRange(partition, lines.end());
    });

    std::vector<Line> output;
    output.reserve(lines.size());

    firstHandle.get();
    lastHandle.get();
    std::merge(lines.begin(), partition, partition, lines.end(),
               std::back_inserter(output));
    std::swap(output, lines);
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
