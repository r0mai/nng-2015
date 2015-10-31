#include <iostream>

#include <array>
#include <vector>

#include <algorithm>
#include <chrono>
#include <iterator>
#include <string>

#include <future>

#include <boost/sort/sort.hpp>

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

void sortRange(std::vector<Line>::iterator begin,
               std::vector<Line>::iterator end) {
    Timer t("Time to sort subrange of size " +
            std::to_string(std::distance(begin, end)));
    boost::sort::spreadsort::string_sort(begin, end, '\0');
}

struct LineFacade {
    void operator=(const Line& line) { std::cout << line.data() << '\n'; }
};

struct DataPrintIterator
    : public std::iterator<std::output_iterator_tag, LineFacade> {
    DataPrintIterator& operator++() { return *this; }
    DataPrintIterator& operator++(int) { return *this; }

    LineFacade operator*() { return LineFacade{}; }
};

template <typename OutputIterator, typename Iterator>
OutputIterator threeWayMerge(OutputIterator outputIterator, Iterator begin1,
                             Iterator end1, Iterator begin2, Iterator end2,
                             Iterator begin3, Iterator end3) {
    for (; begin1 != end1; ++outputIterator) {
        if (begin2 == end2) {
            return std::merge(begin1, end1, begin3, end3, outputIterator);
        }

        if (begin3 == end3) {
            return std::merge(begin1, end1, begin2, end2, outputIterator);
        }

        const auto& one = *begin1;
        const auto& two = *begin2;
        const auto& three = *begin3;

        if (one <= two && one <= three) {
            *outputIterator = one;
            ++begin1;
        } else if (two <= one && two <= three) {
            *outputIterator = two;
            ++begin2;
        } else {
            *outputIterator = three;
            ++begin3;
        }
    }
    return std::merge(begin2, end2, begin3, end3, outputIterator);
}

template <typename OutputIterator, typename Iterator>
OutputIterator fourWayMerge(OutputIterator outputIterator, Iterator begin1,
                            Iterator end1, Iterator begin2, Iterator end2,
                            Iterator begin3, Iterator end3, Iterator begin4,
                            Iterator end4) {
    for (; begin1 != end1; ++outputIterator) {
        if (begin2 == end2) {
            return threeWayMerge(outputIterator, begin1, end1, begin3, end3,
                                 begin4, end4);
        }

        if (begin3 == end3) {
            return threeWayMerge(outputIterator, begin1, end1, begin2, end2,
                                 begin4, end4);
        }

        if (begin4 == end4) {
            return threeWayMerge(outputIterator, begin1, end1, begin2, end2,
                                 begin3, end3);
        }

        const auto& one = *begin1;
        const auto& two = *begin2;
        const auto& three = *begin3;
        const auto& four = *begin4;

        if (one <= two && one <= three && one <= four) {
            *outputIterator = one;
            ++begin1;
        } else if ( two <= one && two <= three && two <= four ) {
            *outputIterator = two;
            ++begin2;
        } else if (three <= one && three <= two && three <= four) {
            *outputIterator = three;
            ++begin3;
        } else {
            *outputIterator = four;
            ++begin4;
        }
    }
    return threeWayMerge(outputIterator, begin2, end2, begin3, end3, begin4,
                         end4);
}

void sortAndPrintLines(std::vector<Line>& lines) {
    Timer t("Time to sort and print lines");
    auto firstPartition = lines.begin() + lines.size() / 4;
    auto secondPartition = firstPartition + lines.size() / 4;
    auto thirdPartition = secondPartition + lines.size() / 4;

    auto firstHandle =
        std::async(std::launch::async, [&lines, firstPartition]() {
            sortRange(lines.begin(), firstPartition);
        });

    auto secondHandle = std::async(std::launch::async,
                                   [&lines, firstPartition, secondPartition]() {
        sortRange(firstPartition, secondPartition);
    });

    auto thirdHandle = std::async(std::launch::async,
                                  [&lines, secondPartition, thirdPartition]() {
        sortRange(secondPartition, thirdPartition);
    });

    auto forthHandle = std::async(
        std::launch::async,
        [&lines, thirdPartition]() { sortRange(thirdPartition, lines.end()); });

    DataPrintIterator outIterator;

    std::vector<Line> firstMerge;
    firstMerge.reserve(lines.size()/2+1);

    auto firstMergeHandle = std::async(
        std::launch::async, [&firstHandle, &secondHandle, &lines, &firstMerge,
                             firstPartition, secondPartition]() {
            firstHandle.get();
            secondHandle.get();
            std::merge(lines.begin(), firstPartition, firstPartition,
                       secondPartition, std::back_inserter(firstMerge));
        });

    std::vector<Line> secondMerge;
    secondMerge.reserve(lines.size()/2+1);

    auto secondMergeHandle = std::async(
        std::launch::async, [&thirdHandle, &forthHandle, &lines, &secondMerge,
                             secondPartition, thirdPartition]() {
            thirdHandle.get();
            forthHandle.get();
            std::merge(secondPartition, thirdPartition, thirdPartition,
                       lines.end(), std::back_inserter(secondMerge));
        });

    firstMergeHandle.get();
    secondMergeHandle.get();

    std::merge(firstMerge.begin(), firstMerge.end(), secondMerge.begin(),
               secondMerge.end(), outIterator);
}

void readLine(Line& line) { std::cin.getline(line.data(), maxLength+1); }

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

    std::array<char, 16> numberOfLinesAsString;
    std::cin.getline(numberOfLinesAsString.data(), 16);

    numberOfLines = std::atoi(numberOfLinesAsString.data());

    auto lines = readLines(numberOfLines);

    sortAndPrintLines(lines);
}
