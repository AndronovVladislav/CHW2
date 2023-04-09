#include "KMPTestContainer.h"

std::vector<size_t>
KMPTestContainer::kmp(const std::string &text, const std::string &pattern, int alphabet_size, std::string &pi_func) {
    std::vector<size_t> res;

    auto new_pattern = pattern + "@" + text;
    auto br = pis[pi_func == "base" ? 0 : 1](new_pattern, alphabet_size, operations);
    for (int i = 0; i < br.size(); ++i) {
        for (int j = 0; j < br[i].size(); ++j) {
            operations += 1;
            if (br[i][j] == pattern.length()) {
                res.push_back(j - 2 * br[i][j]);
            }
        }
    }

    return res;
}

bool
KMPTestContainer::test(const std::string &text, const std::string &pattern, int alphabet_size, std::string pi_func) {
    auto start = std::chrono::high_resolution_clock::now();

    auto res = kmp(text, pattern, alphabet_size, pi_func);
//    return Utils::checker(res, text, pattern);
    time += std::chrono::duration_cast<std::chrono::nanoseconds>(
            std::chrono::high_resolution_clock::now() - start).count();
    return true;
}

int64_t KMPTestContainer::getOperations() const {
    return operations;
}

int64_t KMPTestContainer::getTime() const {
    return time;
}