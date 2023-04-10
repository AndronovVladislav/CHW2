#ifndef IHW2_UTILS_H
#define IHW2_UTILS_H

#include <algorithm>
#include <array>
#include <functional>
#include <iostream>
#include <set>
#include <vector>
#include <random>
#include <utility>
#include <chrono>
#include <fstream>
#include <unordered_map>

class Utils {

public:
    static std::vector<size_t> naiveSearch(const std::string &text, const std::string &pattern);

    static std::vector<size_t> basePi(std::string &str, int64_t &operations);

    static std::vector<size_t> coolPi(std::string &str, int64_t &operations);

    static bool checker(std::vector<size_t> &res, const std::string &text, const std::string &pattern);

    static std::string generateText(int len, int alphabet_size);

    static std::string generatePattern(std::string &text, int step, size_t universal_symbol_amount, size_t offset);

    static size_t generateOffset(unsigned long size);

    static std::string join(const std::vector<std::string> &sequence, const std::string &separator);

    static std::vector<std::string> split(std::string s, std::string delimiter);
};

#endif //IHW2_UTILS_H
