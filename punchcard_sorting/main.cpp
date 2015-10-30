#include <iostream>

#include <array>
#include <vector>

#include <algorithm>

constexpr std::size_t maxLength = 64;

using Line = std::array<char, maxLength + 1>;

void printLines(const std::vector<Line>& lines) {
    for (const auto& line : lines) {
        std::cout << line.data() << '\n';
	}
}

void sortLines(std::vector<Line>& lines) {

	std::sort(lines.begin(), lines.end(), [](const Line& lhs, const Line& rhs) {
            return std::lexicographical_compare(
			        lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
			});

}

void readLine(Line& line) {
    for(char& c: line) {
        c = 0;
    }
    std::cin >> line.data();
}

int main() {
    std::ios::sync_with_stdio(false);

    std::size_t numberOfLines = 0;
    std::cin >> numberOfLines;

    std::vector<Line> lines;
    lines.resize(numberOfLines);

	for(std::size_t lineIndex = 0; lineIndex < numberOfLines; ++lineIndex) {
		readLine(lines[lineIndex]);
	}

	sortLines(lines);
	printLines(lines);
}
