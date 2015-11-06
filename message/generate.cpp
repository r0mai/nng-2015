#include <string>
#include <cassert>
#include <iostream>

char to_other_format(char ch) {
    switch (ch) {
        case 'A': return 0;
        case 'C': return 1;
        case 'T': return 2;
        case 'G': return 3;
        default: assert(false); return 5;
    }
}

int main() {
    std::string dns;
    std::getline(std::cin, dns);

    assert(!dns.empty());
    assert(dns.size() % 4 == 0);
    for (unsigned i = 0; i < dns.size(); i += 4) {
        char out = 0;
        for (unsigned j = 0; j < 4; ++j) {
            out |= to_other_format(dns[i + j]) << 2*j;
        }
        std::cout << out;
    }
}
