#include <string>
#include <vector>
#include <cassert>
#include <fstream>
#include <iostream>

std::string program =
R"(#include <cstdio>
int main(){auto x=R"()";


int main() {
    std::string dns;
    std::getline(std::cin, dns);

    std::vector<char> program;

    const char[] x = "abdsdasdasdasd";
    std::cout << sizeof(x) << std::endl;

    int bit = 0;
    char byte = 0;
    for (char ch : dns) {
        switch (ch) {
            case 'A': byte |= (0 << bit); break;
            case 'C': byte |= (1 << bit); break;
            case 'G': byte |= (2 << bit); break;
            case 'T': byte |= (3 << bit); break;
            default: assert(false);
        }
        bit += 2;
        if (bit == 8) {
            bit = 0;
            program.push_back(byte);
            byte = 0;
        }
    }

    std::ofstream out("main.cpp");
    out.write(program.data(), program.size());
}
