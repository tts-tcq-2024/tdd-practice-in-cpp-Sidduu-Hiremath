#include <string>
#include <stdexcept>
#include <sstream>
#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <functional>

std::vector<int> split(const std::string& str, const std::string& delimiters) {
    std::vector<int> numbers;
    size_t start = 0;
    size_t end;
    while ((end = str.find_first_of(delimiters, start)) != std::string::npos) {
        numbers.push_back(std::stoi(str.substr(start, end - start)));
        start = end + 1;
    }
    numbers.push_back(std::stoi(str.substr(start)));
    return numbers;
}

void validateNoNegatives(const std::vector<int>& numbers) {
    auto it = std::find_if(numbers.begin(), numbers.end(), [](int num) { return num < 0; });
    if (it != numbers.end()) {
        throw std::runtime_error("Negatives not allowed: " + std::to_string(*it));
    }
}

int sumIgnoringLargeNumbers(const std::vector<int>& numbers) {
    return std::accumulate(numbers.begin(), numbers.end(), 0, [](int sum, int num) {
        return num <= 1000 ? sum + num : sum;
    });
}

std::string parseCustomDelimiter(const std::string& input, std::string& delimiters) {
    if (input.rfind("//", 0) == 0) {
        size_t newline_pos = input.find('\n');
        delimiters = input.substr(2, newline_pos - 2);
        return input.substr(newline_pos + 1); 
    }
    return input; 
}

class StringCalculator {
public:
    int add(const std::string& input) {
        if (input.empty()) return 0;

        std::string delimiters = ",\n";
        std::string numbers = parseCustomDelimiter(input, delimiters);

        std::vector<int> parsedNumbers = split(numbers, delimiters);

        validateNoNegatives(parsedNumbers);
        return sumIgnoringLargeNumbers(parsedNumbers);
    }
};
