#include "TestCaseContainer.h"


std::string TestCaseContainer::log(std::vector<std::string> extra_info) const {
    std::vector<std::string> res;

    res.push_back(std::to_string(alphabet_size));
    res.push_back(std::to_string(text_size));
    res.push_back(std::to_string(pattern.length()));
    res.push_back(std::to_string(universal_symbols_amount));

    for (const auto &extra_inf : extra_info) {
        res.push_back(extra_inf);
    }

    auto sep = std::string(",");
    return Utils::join(res, sep);
}

std::string TestCaseContainer::getPattern() const {
    return pattern;
}