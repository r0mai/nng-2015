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

template <typename Handle, typename Partition>
void sortAndPrintLines(std::vector<Line>& lines, Handle firstHandle,
                       Handle secondHandle, Handle thirdHandle,
                       Handle forthHandle, Partition firstPartition,
                       Partition secondPartition, Partition thirdPartition) {
    Timer t("Time to sort and print lines");
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

std::vector<Line> readLines(std::size_t numberOfLines,
                            std::future<void>& firstHandle,
                            std::future<void>& secondHandle,
                            std::future<void>& thirdHandle,
                            std::future<void>& forthHandle,
                            std::vector<Line>::iterator& firstPartition,
                            std::vector<Line>::iterator& secondPartition,
                            std::vector<Line>::iterator& thirdPartition) {
    std::vector<Line> lines;
    lines.resize(numberOfLines);

    Timer t("Time to read lines");

    char* buffer = new char[numberOfLines * (maxLength + 1)];

    std::size_t length =
        std::fread(buffer, 1, numberOfLines * (maxLength + 1), stdin);

    std::size_t currentLineBegin = 0;

    long linesRead = 0;

    firstPartition = lines.begin() + numberOfLines / 4;
    secondPartition = firstPartition + numberOfLines / 4;
    thirdPartition = secondPartition + numberOfLines / 4;

    for (std::size_t c_ = 0; c_ < length; ++c_) {
        if (buffer[c_] != '\n') {
            continue;
        }

        auto& line = lines[linesRead];

        buffer[c_] = '\0';

        std::memcpy(line.data(), buffer + currentLineBegin,
                    c_ - currentLineBegin);
        currentLineBegin = c_ + 1;
        ++linesRead;

        if (linesRead == std::distance(lines.begin(), firstPartition)) {
            firstHandle =
                std::async(std::launch::async, [&lines, firstPartition]() {
                    sortRange(lines.begin(), firstPartition);
                });
        } else if (linesRead == std::distance(lines.begin(), secondPartition)) {
            secondHandle = std::async(
                std::launch::async, [firstPartition, secondPartition]() {
                    sortRange(firstPartition, secondPartition);
                });
        } else if (linesRead == std::distance(lines.begin(), thirdPartition)) {
            thirdHandle = std::async(std::launch::async,
                                     [secondPartition, thirdPartition]() {
                sortRange(secondPartition, thirdPartition);
            });
        }
    }

    forthHandle = std::async(std::launch::async, [&lines, thirdPartition]() {
        sortRange(thirdPartition, lines.end());
    });

    return lines;
}

int main() {
    std::size_t numberOfLines = 0;

    std::array<char, 16> numberOfLinesAsString;
    std::cin.getline(numberOfLinesAsString.data(), 16);

    numberOfLines = std::atoi(numberOfLinesAsString.data());
    std::future<void> firstHandle;
    std::future<void> secondHandle;
    std::future<void> thirdHandle;
    std::future<void> forthHandle;

    std::vector<Line>::iterator firstPartition;
    std::vector<Line>::iterator secondPartition;
    std::vector<Line>::iterator thirdPartition;

    auto lines =
        readLines(numberOfLines, firstHandle, secondHandle, thirdHandle,
                  forthHandle, firstPartition, secondPartition, thirdPartition);

    sortAndPrintLines(lines, std::move(firstHandle), std::move(secondHandle),
                      std::move(thirdHandle), std::move(forthHandle),
                      lines.begin() + numberOfLines / 4,
                      lines.begin() + numberOfLines / 2,
                      lines.begin() + numberOfLines / 2 + numberOfLines / 4);
}
