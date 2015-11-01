#include <iostream>

#include <cassert>
#include <iterator>
#include <map>
#include <vector>

using Aggression = int;

bool canWeAddConvict(const std::vector<Aggression>& others,
                     Aggression convict) {
    for (std::size_t a = 0; a < others.size() - 1; ++a) {
        for (std::size_t b = a + 1; b < others.size(); ++b) {
            if (others[a] + others[b] == convict) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    std::size_t numberOfConvicts = 0;
    std::cin >> numberOfConvicts;

    std::vector<Aggression> aggressions;

    for (std::size_t i = 0; i < numberOfConvicts; ++i) {
        Aggression aggresion;
        std::cin >> aggresion;
        aggressions.push_back(aggresion);
    }

    std::vector<std::vector<Aggression>> rounds;

    for (const auto& convict : aggressions) {
        for (auto& round : rounds) {
            if (canWeAddConvict(round, convict)) {
                std::cerr << "We can add convict: " << convict << std::endl;
                round.push_back(convict);
                goto nextConvict;
            }
        }
        std::cerr << "We had to add a new round for convict: " << convict
                  << std::endl;
        rounds.push_back({convict});
    nextConvict:
        continue;
    }

    std::cerr << "Did it in: " << rounds.size() << " rounds." << std::endl;

    for (const auto& round : rounds) {
        std::cerr << "{";
        std::copy(round.begin(), round.end(),
                  std::ostream_iterator<Aggression>(std::cerr, ", "));
        std::cerr << "}" << std::endl;
    }
}
