#include "TestCaseContainer.h"

TestCaseContainer::TestCaseContainer(size_t alphabet_size, size_t text_size, std::string pattern,
                                     size_t universal_symbols_amount) {
    this->alphabet_size = alphabet_size;
    this->text_size = text_size;
    this->pattern = pattern;
    this->universal_symbols_amount = universal_symbols_amount;
}

std::string TestCaseContainer::log(std::vector<std::string> &extra_info) const {
    std::vector<std::string> res;

    res.push_back(std::to_string(alphabet_size));
    res.push_back(std::to_string(text_size));
    res.push_back(std::to_string(pattern.length()));
    res.push_back(std::to_string(universal_symbols_amount));

    for (const auto &extra_inf: extra_info) {
        res.push_back(extra_inf);
    }

    auto sep = std::string(",");
    return Utils::join(res, sep);
}

std::string TestCaseContainer::getPattern() const {
    return pattern;
}