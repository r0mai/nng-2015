#include <string>
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

    generate_decoder(dns);
}
