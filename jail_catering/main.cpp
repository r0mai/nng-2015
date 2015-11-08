#include <iostream>

#include <algorithm>
#include <cassert>
#include <chrono>
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

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Please add a timeout for how long to work" << std::endl;
        std::exit(1);
    }

    auto duration = std::chrono::seconds{std::atoi(argv[1])};
    auto startTime = std::chrono::system_clock::now();

    auto endTime = startTime + duration;

    std::size_t numberOfConvicts = 0;
    std::cin >> numberOfConvicts;

    std::vector<Aggression> aggressions;

    for (std::size_t i = 0; i < numberOfConvicts; ++i) {
        Aggression aggresion;
        std::cin >> aggresion;
        aggressions.push_back(aggresion);
    }

    std::vector<std::vector<Aggression>> bestRounds;

    for (;;) {
        if (std::chrono::system_clock::now().time_since_epoch() >=
            endTime.time_since_epoch()) {
            break;
        }

        std::vector<std::vector<Aggression>> rounds;
        std::random_shuffle(aggressions.begin(), aggressions.end());
        for (const auto& convict : aggressions) {
            for (auto& round : rounds) {
                if (canWeAddConvict(round, convict)) {
                    round.push_back(convict);
                    goto nextConvict;
                }
            }
            rounds.push_back({convict});
        nextConvict:
            continue;
        }

        if (rounds.size() > bestRounds.size()) {
            std::swap(bestRounds, rounds);
        }
    }

    std::cout << bestRounds.size() << std::endl;

    for (const auto& round : bestRounds) {
        std::copy(round.begin(), round.end(),
                  std::ostream_iterator<Aggression>(std::cout, " "));
        std::cout << std::endl;
    }
}
