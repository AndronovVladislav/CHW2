#ifndef IHW2_KMPTESTCONTAINER_H
#define IHW2_KMPTESTCONTAINER_H

#include "../Testing/Utils.h"

class KMPTestContainer {
public:
    KMPTestContainer() {
        operations = 0;
        time = 0;
        pis = {Utils::basePi, Utils::coolPi};
    }

    bool test(const std::string &text, const std::string &pattern, int alphabet_size, std::string pi_func);

    std::vector<size_t> kmp(const std::string &text, const std::string &pattern, int alphabet_size, std::string &pi_func);

    int64_t getOperations() const;

    int64_t getTime() const;

private:
    int64_t operations;
    int64_t time;
    std::array<std::function<std::vector<std::vector<size_t>>(std::string &, int, int64_t &)>, 2> pis;
};


#endif
