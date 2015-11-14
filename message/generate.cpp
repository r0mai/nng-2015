#include <set>
#include <map>
#include <array>
#include <tuple>
#include <string>
#include <vector>
#include <iomanip>
#include <cassert>
#include <sstream>
#include <iostream>

#include <boost/algorithm/string.hpp>

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

bool isSpecialChar(char ch) {
    switch (ch) {
        default: return false;
        case '\n': return true;
        case '\r': return true;
    }
}

std::string toStringLiteral(const std::string& str) {
    std::stringstream ss;
    if (std::any_of(str.begin(), str.end(), isSpecialChar)) {
        ss << "R\"(" << str << ")\"";
    } else {
        ss << std::quoted(str);
    }
    return ss.str();
}


struct SubString {
    std::string str;
    int repeat_count;

    // higher means more compression
    int cost() const {
        return
            str.size() * repeat_count // reduction
            -1 // comma
            -toStringLiteral(str).size()
        ;
    }
};

bool operator==(const SubString& lhs, const SubString& rhs) {
    return
        std::tie(lhs.str, lhs.repeat_count) ==
        std::tie(rhs.str, rhs.repeat_count);
}

// longest repeated strings <lrs, count>
std::vector<SubString> lrs(const std::string& s) {

    // form the N suffixes
    std::vector<std::string> suffixes(s.size());
    for (int i = 0; i < s.size(); i++) {
        suffixes[i] = s.substr(i);
    }

    // sort them
    std::sort(suffixes.begin(), suffixes.end());

    std::vector<SubString> repeated_strings;

    for (int i = 0; i < s.size() - 1; i++) {
        auto sub = lcp(suffixes[i], suffixes[i+1]);
        if (sub.size() <= 2) {
            continue;
        }
        repeated_strings.push_back({sub, count_substrings(s, sub)});
    }
    std::sort(repeated_strings.begin(), repeated_strings.end(),
        [](const auto& lhs, const auto& rhs) {
            if (lhs.cost() != rhs.cost()) {
                return lhs.cost() < rhs.cost();
            }
            return lhs.str < rhs.str;
        }
    );
    repeated_strings = decltype(repeated_strings)(
        repeated_strings.begin(),
        std::unique(repeated_strings.begin(), repeated_strings.end()));

    std::set<unsigned> marked_for_removal;
    for (unsigned i = 0; i < repeated_strings.size(); ++i) {
        if (marked_for_removal.count(i) > 0) {
            continue;
        }
        const std::string& istr = repeated_strings[i].str;
        int icost = repeated_strings[i].cost();
        for (unsigned j = 0; j < repeated_strings.size(); ++j) {
            if (marked_for_removal.count(j) > 0) {
                continue;
            }
            if (i == j) {
                continue;
            }
            const std::string& jstr = repeated_strings[j].str;
            int jcost = repeated_strings[j].cost();
            if (jstr.find(istr) != std::string::npos ||
                istr.find(jstr) != std::string::npos)
            {
                if (icost > jcost) {
                    marked_for_removal.insert(j);
                } else {
                    marked_for_removal.insert(i);
                }
                break;
            }
        }
    }
    for (auto it = marked_for_removal.rbegin(), end = marked_for_removal.rend();
            it != end; ++it)
    {
        repeated_strings.erase(repeated_strings.begin() + *it);
    }

    return repeated_strings;
}

struct StringReplaceResult {
    std::string compressed_string;
    std::map<char, std::string> decode_map;
};

StringReplaceResult repalce_strings_in_string(
    const std::string& text,
    const std::vector<SubString>& substrings,
    int start)
{
    StringReplaceResult result = {text, {}};

    int end = 255;
    int char_index = start;
    for (int i = substrings.size() - 1; i >= 0 && char_index <= end; --i, ++char_index) {
        if (result.compressed_string.find(char_index) != std::string::npos) {
            ++i;
            result.decode_map[char(char_index)] = std::string(1, char(char_index));
        } else {
            boost::replace_all(
                result.compressed_string,
                substrings[i].str,
                std::string(1, char(char_index)));

            result.decode_map[char(char_index)] = substrings[i].str;
        }
    }

    return result;
}


void analyze_chars(const std::string& text) {
    std::array<int, 256> chars = {{ 0 }};
    for (char ch : text) {
        ++chars[(unsigned char)(ch)];
    }
    int start = -1;
    int end = -1;
    for (unsigned i = 0; i < chars.size(); ++i) {
        if (chars[i] == 0) {
            if (start == -1) {
                start = i;
            }
            end = i;
        } else if (start != -1 && end != -1 && chars[start] == 0 && chars[end] == 0) {
            std::cerr << "Range [" << start << ", " << end << "] ("
                << end - start + 1 << ")" << std::endl;
            start = end = -1;
        }
    }
    if (start != -1) {
        end = 255;
        std::cerr << "Range [" << start << ", " << end << "] ("
            << end - start + 1 << ")" << std::endl;
    }
}

std::string replaceMapToSourceArray(const StringReplaceResult& srr) {
    std::stringstream ss;

    ss << "char*m[]={";
    bool first = true;
    for (const auto& e : srr.decode_map) {
        // TODO don't use raw literals if not needed
        if (first) {
            first = false;
        } else {
            ss << ",";
        }
        ss << toStringLiteral(e.second);
    }
    ss << "};";
    return ss.str();
}

std::string generate_decoder(const std::string& dns, int replace_start = 130) {
    std::stringstream ss;
    auto text = dnsToText(dns);

    auto repeated_strings = lrs(text);
    //analyze_chars(text);

    StringReplaceResult replaced_result =
        repalce_strings_in_string(text, repeated_strings, replace_start);

    // no attempt was made to make it shorter, yet
    ss << R"RAW(
#include <cstdio>
#include <string>
#include <sstream>
)RAW" << replaceMapToSourceArray(replaced_result) << R"RAW(
void textToDns(std::string text) {
    for (int i = 0; i < text.size()*4; ++i) {
        putchar("ACTG"[text[i/4] >> i%4*2 & 3]);
    }
}
std::string compressedToText(const std::string& compressed) {
    std::stringstream ss;
    for (char ch : compressed) {
        if ((unsigned char)ch > )RAW" << replace_start-1 << R"RAW() {
            ss << m[(unsigned char)ch - )RAW" << replace_start << R"RAW(];
        } else {
            ss << ch;
        }
    }
    return ss.str();
}
int main() {
    auto d=R"()RAW" << replaced_result.compressed_string << R"RAW()";
    textToDns(compressedToText(d));
}
)RAW";

    return ss.str();
}

int main() {
    std::string dns;
    std::getline(std::cin, dns);

    auto generated_source = generate_decoder(dns);
    std::cerr << "Generated source size = "
        << generated_source.size() << std::endl;
    std::cout << generated_source << std::flush;
}
