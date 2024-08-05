#include <iostream>
#include <optional>

std::optional<int> findEvenNumber(int number) {
    if (number % 2 == 0) {
        return number;
    }
    return std::nullopt;
}

int main() {
    int number = 10;
    std::optional<int> result = findEvenNumber(number);

    if (result) {
        std::cout << "Even number found: " << *result << std::endl;
    } else {
        std::cout << "No even number found." << std::endl;
    }

    return 0;
}
