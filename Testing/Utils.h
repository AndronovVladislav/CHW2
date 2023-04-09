#ifndef IHW2_UTILS_H
#define IHW2_UTILS_H

#include <array>
#include <functional>
#include <iostream>
#include <string>
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

    static std::vector<std::vector<size_t>> basePi(std::string &str, int alphabet_size, int64_t &operations);

    static std::vector<std::vector<size_t>> coolPi(std::string &str, int alphabet_size, int64_t &operations);

    static bool checker(std::vector<size_t> &res, const std::string &text, const std::string &pattern);

    static std::set<std::string> getAllStrings(std::string &universal_str, int alphabet_size);

    static std::vector<size_t> getUniversalPlaces(std::string &universal_str);

    static std::string generateText(int len, int alphabet_size);

    static std::string generatePattern(std::string &text, int step, size_t universal_symbol_amount, size_t offset);

    static size_t generateOffset(unsigned long size);

    static std::string join(const std::vector<std::string> &sequence, const std::string &separator);
};

#endif //IHW2_UTILS_H
