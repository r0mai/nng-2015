#include <iostream>

#include <map>
#include <vector>

using Aggression = int;

bool canAFightBreakOut(const std::vector<Aggression>& aggressions) {
    for(std::size_t i=0; i<aggressions.size(); ++i) {
        for (std::size_t j = 0; j < aggressions.size(); ++j) {
            if(i == j) {
                continue;
            }

            for(std::size_t k=0; k<aggressions.size(); ++k) {
                if(i == k) {
                    continue;
                }
                if(j == k) {
                    continue;
                }

                if(aggressions[i] + aggressions[j] == aggressions[k]) {
                    return true;
                }

            }
        }
    }

    return false;
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

    std::cerr
        << "If we all put all convicts in one go a fight will break out: ";
    std::cerr << std::boolalpha << canAFightBreakOut(aggressions) << std::endl;
}
