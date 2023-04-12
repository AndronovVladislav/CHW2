#ifndef IHW2_TESTCASECONTAINER_H
#define IHW2_TESTCASECONTAINER_H

#include "../Testing/Utils.h"

class TestCaseContainer {
public:
    TestCaseContainer(size_t alphabet_size, size_t text_size, std::string pattern, size_t universal_symbols_amount);

    std::string log(std::vector<std::string> &extra_info) const;

    std::string getPattern() const;

private:
    size_t alphabet_size;
    size_t text_size;
    std::string pattern;
    size_t universal_symbols_amount;
};


#endif
