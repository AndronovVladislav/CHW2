#include "NaiveSearchTestContainer.h"

NaiveSearchTestContainer::NaiveSearchTestContainer() {
    time = 0;
    operations = 0;
}

void NaiveSearchTestContainer::test(const std::string &text, const std::string &pattern) {
    auto start = std::chrono::high_resolution_clock::now();
    NaiveSearchTestContainer::naiveSearch(text, pattern);
    time += std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start).count();
}

int64_t NaiveSearchTestContainer::getOperations() const {
    return operations;
}

std::vector<size_t> NaiveSearchTestContainer::naiveSearch(const std::string &text, const std::string &pattern) {
    std::vector<size_t> res;

    for (int i = 0; i < text.length() - pattern.length() + 1; ++i) {
        for (int j = 0; j < pattern.length(); ++j) {
            // такое разделение на ветки нужно, чтобы корректно посчитать количество операций
            if (text[i + j] == pattern[j]) {
                operations += 1;
                if (j == pattern.length() - 1) {
                    res.push_back(i);
                }
            } else if (pattern[j] == '?') {
                operations += 2;
                if (j == pattern.length() - 1) {
                    res.push_back(i);
                }
            } else {
                operations += 2;
                break;
            }
        }
    }

    return res;
}

int64_t NaiveSearchTestContainer::getTime() const {
    return time;
}