#include <array>
#include <tuple>
#include <string>
#include <vector>
#include <cassert>
#include <sstream>
#include <iostream>

char dnsCharToBits(char ch) {
    switch (ch) {
        case 'A': return 0;
        case 'C': return 1;
        case 'T': return 2;
        case 'G': return 3;
        default: assert(false); return 5;
    }
}

char bitsToDnsChar(char ch) {
    switch (ch) {
        case 0: return 'A';
        case 1: return 'C';
        case 2: return 'T';
        case 3: return 'G';
        default: assert(false); return 'X';
    }
}

std::string charToDnsSequence(char ch) {
    std::string s(4, '\0');
    for (unsigned j = 0; j < 4; ++j) {
        s[j] = bitsToDnsChar((ch >> 2*j) & 0x03);
    }
    return s;
}

std::string dnsToText(const std::string& dns) {
    std::stringstream ss;
    assert(!dns.empty());
    assert(dns.size() % 4 == 0);
    for (unsigned i = 0; i < dns.size(); i += 4) {
        char out = 0;
        for (unsigned j = 0; j < 4; ++j) {
            out |= dnsCharToBits(dns[i + j]) << 2*j;
        }
        ss << out;
    }
    return ss.str();
}

std::string textToDns(const std::string& text) {
    std::stringstream ss;
    for (char ch : text) {
        ss << charToDnsSequence(ch);
    }
    return ss.str();
}

int count_substrings(const std::string& corpus, const std::string& needle) {
    int count = 0;
    // Based on the KICS principle (Keep It Complicated Smart)
    for (size_t offset = 0; (offset = corpus.find(needle, offset)) < corpus.size(); ++count, ++offset) {}
    return count;
}

// Based on: http://stackoverflow.com/questions/10355103/finding-the-longest-repeated-substring
// return the longest common prefix of s and t
std::string lcp(const std::string& s, const std::string& t) {
    int n = std::min(s.size(), t.size());
    for (int i = 0; i < n; i++) {
        if (s[i] != t[i])
            return s.substr(0, i);
    }
    return s.substr(0, n);
}


// longest repeated strings <lrs, count>
std::vector<std::tuple<std::string, int>> lrs(const std::string& s) {

    // form the N suffixes
    std::vector<std::string> suffixes(s.size());
    for (int i = 0; i < s.size(); i++) {
        suffixes[i] = s.substr(i);
    }

    // sort them
    std::sort(suffixes.begin(), suffixes.end());

    std::vector<std::tuple<std::string, int>> repeated_strings;

    for (int i = 0; i < s.size() - 1; i++) {
        auto sub = lcp(suffixes[i], suffixes[i+1]);
        if (sub.size() <= 2) {
            continue;
        }
        repeated_strings.push_back({sub, count_substrings(s, sub)});
    }
    std::sort(repeated_strings.begin(), repeated_strings.end(),
        [](const auto& lhs, const auto& rhs) {
            auto lhs_cost = std::get<0>(lhs).size() * std::get<1>(lhs);
            auto rhs_cost = std::get<0>(rhs).size() * std::get<1>(rhs);
            if (lhs_cost != rhs_cost) {
                return lhs_cost < rhs_cost;
            }
            return std::get<0>(lhs) < std::get<0>(rhs);
        }
    );
    return decltype(repeated_strings)(
        repeated_strings.begin(),
        std::unique(repeated_strings.begin(), repeated_strings.end()));
}

void analyze_chars(const std::string& text) {
    std::array<int, 256> chars = {{ 0 }};
    for (char ch : text) {
        ++chars[(unsigned char)(ch)];
    }
    for (unsigned i = 0; i < chars.size(); ++i) {
        if (chars[i] != 0) {
            std::cerr << i << " = " << chars[i] << std::endl;
        }
    }
}

void generate_decoder(const std::string& dns) {
    auto text = dnsToText(dns);

    // no attempt was made to make it shorter, yet
    std::cout << R"RAW(
#include <iostream>
#include <string>
#include <sstream>
char bitsToDnsChar(char ch) {
    switch (ch) {
        case 0: return 'A';
        case 1: return 'C';
        case 2: return 'T';
        case 3: return 'G';
    }
}
std::string charToDnsSequence(char ch) {
    std::string s(4, '\0');
    for (unsigned j = 0; j < 4; ++j) {
        s[j] = bitsToDnsChar((ch >> 2*j) & 0x03);
    }
    return s;
}
std::string textToDns(const std::string& text) {
    std::stringstream ss;
    for (char ch : text) {
        ss << charToDnsSequence(ch);
    }
    return ss.str();
}
int main() {
    auto d=R"()RAW" << text << R"RAW()";
    std::cout << textToDns(d);
}
)RAW";
}

int main() {
    std::string dns;
    std::getline(std::cin, dns);

    auto text = dnsToText(dns);
    auto dns_back = textToDns(text);
    assert(dns == dns_back);

    auto repeated_strings = lrs(text);
    for (const auto& s : repeated_strings) {
        std::cerr << "(" << std::get<1>(s) << ") \"" << std::get<0>(s) << '"' << std::endl;
    }

    generate_decoder(dns);
}
