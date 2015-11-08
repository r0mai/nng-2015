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
            if (others[a] + convict == others[b]) {
                return false;
            }
            if (others[b] + convict == others[a]) {
                return false;
            }
        }
    }
    return true;
}

std::size_t getBestRoundForConvict(
    Aggression aggression, const std::vector<std::vector<Aggression>>& rounds,
    const std::vector<std::size_t>& candidateRounds) {

    static std::random_device rd;
    static std::mt19937 gen{rd()};

    std::uniform_int_distribution<std::size_t> distribution(
        0, candidateRounds.size() - 1);

    std::size_t index = candidateRounds[distribution(gen)];

    for(auto roundIndex : candidateRounds) {
        if(std::find(rounds[roundIndex].begin(), rounds[roundIndex].end(),
                    aggression) != rounds[roundIndex].end()) {
            return roundIndex;
            // We have already assigned a convict with this particular
            // aggression to this round, so assigning a similar one is good.
        }
        if(rounds[roundIndex].size() > rounds[index].size()) {
            index = roundIndex;
        }
    }

    return index;
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

    std::random_device rd;
    std::mt19937 gen(rd());

    for (;;) {
        if (std::chrono::system_clock::now().time_since_epoch() >=
            endTime.time_since_epoch()) {
            break;
        }

        std::vector<std::vector<Aggression>> rounds;
        std::shuffle(aggressions.begin(), aggressions.end(), gen);
        for (const auto& convict : aggressions) {
            std::vector<std::size_t> candidateRounds;
            for (std::size_t roundIndex = 0; roundIndex < rounds.size();
                 ++roundIndex) {
                const auto& round = rounds[roundIndex];
                if (canWeAddConvict(round, convict)) {
                    candidateRounds.push_back(roundIndex);
                }
            }
            if (!candidateRounds.empty()) {

                const auto bestRound =
                    getBestRoundForConvict(convict, rounds, candidateRounds);

                rounds[bestRound].push_back(convict);
            } else {
                rounds.push_back({convict});
            }
        }

        if (rounds.size() < bestRounds.size() || bestRounds.empty()) {
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
