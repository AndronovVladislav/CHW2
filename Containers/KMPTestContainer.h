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

    bool test(const std::string &text, const std::string &pattern, std::string pi_func);

    std::vector<size_t>
    kmp_low_level(const std::string &text, const std::string &pattern, std::string &pi_func);

    std::vector<size_t>
    kmp_high_level(const std::string &text, const std::string &pattern, std::string &pi_func);

    size_t getTotalLength(std::vector<std::string> &chunks, size_t i);

    int64_t getOperations() const;

    int64_t getTime() const;

private:
    int64_t operations;
    int64_t time;
    std::array<std::function<std::vector<size_t>(std::string&, int64_t&)>, 2> pis;
};


#endif
