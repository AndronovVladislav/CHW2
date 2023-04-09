#include "Utils.h"

std::vector<size_t> Utils::naiveSearch(const std::string &text, const std::string &pattern) {
    std::vector<size_t> res;

    for (int i = 0; i < text.length() - pattern.length() + 1; ++i) {
        for (int j = 0; j < pattern.length(); ++j) {
            // такое разделение на ветки нужно, чтобы корректно посчитать количество операций
            if (text[i + j] == pattern[j] || pattern[j] == '?') {
                if (j == pattern.length() - 1) {
                    res.push_back(i);
                }
            } else {
                break;
            }
        }
    }

    return res;
}


std::vector<std::vector<size_t>> Utils::basePi(std::string &str, int alphabet_size, int64_t &operations) {
    auto all_strings = getAllStrings(str, alphabet_size);
    std::vector<std::vector<size_t>> res(all_strings.size(), std::vector<size_t>(str.length()));

    int i = 0;
    for (auto &str_final: all_strings) {
        for (int k = 1; k < str_final.length(); ++k) {
            size_t l = res[i][k - 1];

            operations += 1;
            while (l > 0 && str_final[k] != str_final[l]) {
                l = res[i][l - 1];
                operations += 1;
            }

            operations += 1;
            if (str_final[k] == str_final[l]) {
                ++l;
            }
            res[i][k] = l;
        }
        ++i;
    }

    return res;
}

std::vector<std::vector<size_t>> Utils::coolPi(std::string &str, int alphabet_size, int64_t &operations) {
    std::vector<std::vector<size_t>> br = basePi(str, alphabet_size, operations);
    std::vector<std::vector<size_t>> brs(br.size(), std::vector<size_t>(str.length()));

    for (int i = 0; i < brs.size(); ++i) {
        for (int j = 1; j < br[i].size(); ++j) {
            operations += 1;
            if (str[br[i][j]] != str[i + 1]) {
                brs[i][j] = br[i][j];
            } else {
                brs[i][j] = brs[i][br[i][j] - 1];
            }
        }

    }

    return brs;
}

bool Utils::checker(std::vector<size_t> &res, const std::string &text, const std::string &pattern) {
    return res == naiveSearch(text, pattern);
}

std::set<std::string> Utils::getAllStrings(std::string &universal_str, int alphabet_size) {
    std::set < std::string > res;
    size_t universal_symbol_amount = std::count_if(universal_str.begin(), universal_str.end(),
                                                   [](auto &symb) { return symb == '?'; });
    std::vector<size_t> places = getUniversalPlaces(universal_str);

    for (size_t i = 0; i < alphabet_size; ++i) {
        for (size_t j = 0; j < alphabet_size; ++j) {
            for (size_t k = 0; k < alphabet_size; ++k) {
                for (size_t l = 0; l < alphabet_size; ++l) {
                    std::string replacement;
                    std::copy(universal_str.begin(), universal_str.end(), std::back_inserter(replacement));

                    std::vector<size_t> replacements = std::vector({i, j, k, l});
                    for (int m = 0; m < universal_symbol_amount; ++m) {
                        replacement[places[m]] = replacements[m] + 'a';
                    }

                    res.insert(replacement);
                }
            }
        }
    }

    return res;
}

std::vector<size_t> Utils::getUniversalPlaces(std::string &universal_str) {
    std::vector<size_t> res;
    for (size_t i = 0; i < universal_str.length(); ++i) {
        if (universal_str[i] == '?') {
            res.push_back(i);
        }
    }
    return res;
}


std::string Utils::generateText(int len, int alphabet_size) {
    static std::mt19937 generator(time(nullptr));
    std::uniform_int_distribution<> randsymb(0, alphabet_size - 1);
    std::string result;

    for (size_t i = 0; i < len; ++i) {
        result += randsymb(generator) + 'a';
    }

    return result;
}

std::string Utils::generatePattern(std::string &text, int step, size_t universal_symbol_amount, size_t offset) {
    static std::mt19937 generator(time(nullptr));
    std::uniform_int_distribution<> randoffset(0, text.length() - step);

    std::string result;
    std::copy(text.begin() + offset, text.begin() + offset + step, std::back_inserter(result));

    std::uniform_int_distribution<> randplace(0, result.length() - 1);
    std::set<int> used_places;
    for (int i = 0; used_places.size() < std::min(universal_symbol_amount, result.length()); ++i) {
        int place = randplace(generator);
        if (!used_places.count(place)) {
            result[place] = '?';
            used_places.insert(place);
        }
    }

    return result;
}

size_t Utils::generateOffset(size_t size) {
    static std::mt19937 generator(time(nullptr));
    std::uniform_int_distribution<> randoffset(0, size);
    return randoffset(generator);
}

std::string Utils::join(const std::vector<std::string> &sequence, const std::string &separator) {
    std::string result;
    for (int i = 0; i < sequence.size(); ++i)
        result += sequence[i] + ((i != sequence.size() - 1 && !sequence[i].empty()) ? separator : "");
    return result;
}