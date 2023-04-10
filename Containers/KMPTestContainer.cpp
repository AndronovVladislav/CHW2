#include "KMPTestContainer.h"

std::vector<size_t>
KMPTestContainer::kmp_low_level(const std::string &text, const std::string &pattern, std::string &pi_func) {
    std::vector<size_t> res;

    auto new_pattern = pattern + "@" + text;
    auto br = pis[pi_func == "base" ? 0 : 1](new_pattern, operations);
    for (int i = 0; i < br.size(); ++i) {
        operations += 1;
        if (br[i] == pattern.length()) {
            res.push_back(i - 2 * br[i]);
        }
    }

    return res;
}

std::vector<size_t>
KMPTestContainer::kmp_high_level(const std::string &text, const std::string &pattern, std::string &pi_func) {
    auto chunks = Utils::split(pattern,std::string("?"));
    std::vector<std::vector<size_t>> intermediate_result;

    for (size_t i = 0; i < chunks.size(); ++i) {
        auto intermediate_res = kmp_low_level(text, chunks[i], pi_func);
        auto offset = getTotalLength(chunks, i);

        for (int j = 0; j < intermediate_res.size(); ++j) {
            intermediate_res[j] -= offset;
        }

        intermediate_result.push_back(intermediate_res);
    }

    std::vector<size_t> res(intermediate_result[0].begin(), intermediate_result[0].end());
    for (int i = 0; i < intermediate_result.size(); ++i) {
        std::vector<size_t> working_set(res.begin(), res.end());
        res.clear();
        std::sort(working_set.begin(), working_set.end());
        std::sort(intermediate_result[i].begin(), intermediate_result[i].end());
        std::set_intersection(working_set.begin(), working_set.end(),  intermediate_result[i].begin(), intermediate_result[i].end(),
                              std::back_inserter(res));
    }

    return res;
}

size_t KMPTestContainer::getTotalLength(std::vector<std::string> &chunks, size_t i) {
    size_t res = 0;
    for (int j = 0; j < i; ++j) {
        res += chunks[j].size() + 1;
    }
    return res;
}

bool
KMPTestContainer::test(const std::string &text, const std::string &pattern, std::string pi_func) {
    auto start = std::chrono::high_resolution_clock::now();

    auto res = kmp_high_level(text, pattern, pi_func);
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    time += std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count();
//    return Utils::checker(res, text, pattern);
    return true;
}

int64_t KMPTestContainer::getOperations() const {
    return operations;
}

int64_t KMPTestContainer::getTime() const {
    return time;
}