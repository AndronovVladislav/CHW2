#ifndef IHW2_TESTINGMANAGER_H
#define IHW2_TESTINGMANAGER_H

#define TESTS_AMOUNT 10
#define ALPHABET_SIZES { 2, 4 }
#define UNIVERSAL_SYMBOLS_AMOUNT { 0, 1, 2, 3, 4 }
#define TEXT_SIZES { 10000, 100000 }
#define PATTERN_SIZES { 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000,  \
                1100, 1200, 1300, 1400, 1500, 1600, 1700, 1800, 1900, 2000, \
                2100, 2200, 2300, 2400, 2500, 2600, 2700, 2800, 2900, 3000  \
}

//#define PATTERN_SIZES { 100 }

#include "../Containers/KMPTestContainer.h"
#include "../Containers/NaiveSearchTestContainer.h"
#include "../Containers/TestCaseContainer.h"

class TestingManager {
public:
    TestingManager() {
        prepareContext();
        prepareLoggers();
    }

    ~TestingManager() {
        deactivateLoggers();
    }

    void startTests();

private:
    std::vector<std::string> timeRecords;
    std::vector<std::string> operationsRecords;
    std::vector<std::unordered_map<std::string, std::vector<TestCaseContainer>>> origins;
    std::array<std::ofstream, 3> loggers;

    void printAnswer(std::vector<size_t> &vec);

    void badTest(const std::string &text, const std::string &pattern, std::vector<size_t> right_answer,
                 std::vector<size_t> wrong_answer);

    void prepareContext();

    void prepareLoggers();

    std::string startKMPTest(const std::string &text, const TestCaseContainer &test_case, int alphabet_size,
                             std::string &pi_func);

    std::string startNaiveSearchTest(const std::string &text, const TestCaseContainer &test_case);

    void deactivateLoggers();
};

#endif
