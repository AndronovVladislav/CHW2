#ifndef IHW2_NAIVESEARCHTESTCONTAINER_H
#define IHW2_NAIVESEARCHTESTCONTAINER_H

#include "../Testing/Utils.h"

class NaiveSearchTestContainer {
public:
    NaiveSearchTestContainer();

    void test(const std::string &text, const std::string &pattern);

    std::vector<size_t> naiveSearch(const std::string &text, const std::string &pattern);

    int64_t getOperations() const;

    int64_t getTime() const;

private:
    int64_t operations;
    int64_t time;
};


#endif
