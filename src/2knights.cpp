#include <2knighs.hpp>

namespace TwoKnights {

    bool findCombinations(const std::vector<int>& numbers, int target, std::vector<int>& currentCombination, int index) {
            
        if (index == numbers.size()) {
            int total = 0;
            for (int num : currentCombination) {
                total += num;
            }
            return total == target;
        }

        // Рассмотрим текущий элемент с плюсом
        currentCombination.push_back(numbers[index]);
        if (findCombinations(numbers, target, currentCombination, index + 1)) {
            return true;
        }
        currentCombination.pop_back();

        // Рассмотрим текущий элемент с минусом
        currentCombination.push_back(-numbers[index]);
        if (findCombinations(numbers, target, currentCombination, index + 1)) {
            return true;
        }
        currentCombination.pop_back();

        return false; // Если ни один из вариантов не подошел
    }
}
