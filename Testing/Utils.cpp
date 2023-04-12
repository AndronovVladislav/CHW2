#include "Utils.h"

std::vector<size_t> Utils::naiveSearch(const std::string &text, const std::string &pattern) {
    std::vector<size_t> res;

    for (int i = 0; i < text.length() - pattern.length() + 1; ++i) {
        for (int j = 0; j < pattern.length(); ++j) {
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

std::vector<size_t> Utils::basePi(std::string &str, int64_t &operations) {
    std::vector<size_t> res(str.length());

    for (int i = 1; i < str.length(); ++i) {
        size_t l = res[i - 1];

        operations += 1;
        while (l > 0 && str[i] != str[l]) {
            l = res[l - 1];
            operations += 1;
        }

        operations += 1;
        if (str[i] == str[l]) {
            ++l;
        }
        res[i] = l;
    }

    return res;
}

std::vector<size_t> Utils::coolPi(std::string &str, int64_t &operations) {
    std::vector<size_t> br = basePi(str, operations);
    std::vector<size_t> brs(br.size());

    for (int i = 1; i < br.size(); ++i) {
        operations += 1;
        if (str[br[i]] != str[i + 1]) {
            brs[i] = br[i];
        } else {
            brs[i] = brs[br[i] - 1];
        }
    }

    return brs;
}

bool Utils::checker(std::vector<size_t> &res, const std::string &text, const std::string &pattern) {
    return res == Utils::naiveSearch(text, pattern);
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
    for (int i = 0; i < sequence.size(); ++i) {
        result += sequence[i] + ((i != sequence.size() - 1 && !sequence[i].empty()) ? separator : "");
    }
    return result;
}

std::vector<std::string> Utils::split(std::string s, std::string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}
