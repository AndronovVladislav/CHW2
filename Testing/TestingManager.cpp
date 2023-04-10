#include "TestingManager.h"

void TestingManager::printAnswer(std::vector<size_t> &vec) {
    for (auto &item: vec) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
}

void TestingManager::badTest(const std::string &text, const std::string &pattern, std::vector<size_t> right_answer,
                             std::vector<size_t> wrong_answer) {
    std::cout << "Bad test!" << '\n' << text << '\n' << pattern << std::endl;

    printAnswer(right_answer);
    printAnswer(wrong_answer);

    throw std::runtime_error("Ooops!");
}

void TestingManager::prepareContext() {
    for (const auto &text_size: TEXT_SIZES) {
        for (const auto &alphabet_size: ALPHABET_SIZES) {
            std::unordered_map<std::string, std::vector<TestCaseContainer>> text_patterns_pack;
            auto current_text = Utils::generateText(text_size, alphabet_size);
            text_patterns_pack[current_text] = std::vector<TestCaseContainer>();

            for (const auto &pattern_size: PATTERN_SIZES) {
                auto offset = Utils::generateOffset(text_size);
                for (const auto &universal_symbols_amount: UNIVERSAL_SYMBOLS_AMOUNT) {
                    text_patterns_pack[current_text].push_back(
                            TestCaseContainer(alphabet_size,
                                              current_text.length(),
                                              Utils::generatePattern(current_text, pattern_size,
                                                                     universal_symbols_amount,
                                                                     offset),
                                              universal_symbols_amount)
                    );
                }
            }

            origins.push_back(text_patterns_pack);
        }
    }
}

void TestingManager::startTests() {
    auto base_mode = std::string("base");
    auto cool_mode = std::string("cool");

    for (int i = 0; i < origins.size(); ++i) {
        for (const auto &[text, patterns]: origins[i]) {
            for (int j = 0; j < patterns.size(); ++j) {
                loggers[0] << startKMPTest(text, patterns[j], base_mode);
                loggers[1] << startKMPTest(text, patterns[j], cool_mode);
                loggers[2] << startNaiveSearchTest(text, patterns[j]);
                std::cout << "Test " << i << " " << j << " completed\n";
            }
        }

        if (i != origins.size() - 1) {
            std::cout << "Completed " << 25 * ((i + 1) % origins.size()) << "%" << std::endl;
        }
    }
    std::cout << "Completed 100%" << std::endl;
}

void TestingManager::prepareLoggers() {
    loggers[0].open("../Logs/BaseKMP_Results.csv");
    loggers[1].open("../Logs/CoolKMP_Results.csv");
    loggers[2].open("../Logs/NaiveSearch_Results.csv");

    for (int i = 0; i < loggers.size(); ++i) {
        loggers[i] << "AlphabetSize,TextSize,PatternSize,UniversalSymbolsAmount,Comparisons,TimeNs\n";
    }
}

std::string
TestingManager::startKMPTest(const std::string &text, const TestCaseContainer &test_case, std::string &pi_func) {
    auto kmp_suite = KMPTestContainer();

    for (int i = 0; i < TESTS_AMOUNT; ++i) {
        if (!kmp_suite.test(text, test_case.getPattern(), pi_func)) {
            badTest(text, test_case.getPattern(), Utils::naiveSearch(text, test_case.getPattern()),
                    kmp_suite.kmp_high_level(text, test_case.getPattern(), pi_func));
        }
    }
    std::vector<std::string> result = {std::to_string(kmp_suite.getOperations() / TESTS_AMOUNT),
                                       std::to_string(kmp_suite.getTime() / TESTS_AMOUNT) + "\n"};
    return test_case.log(result);
}

std::string TestingManager::startNaiveSearchTest(const std::string &text, const TestCaseContainer &test_case) {
    auto naive_search_suite = NaiveSearchTestContainer();

    for (int i = 0; i < TESTS_AMOUNT; ++i) {
        naive_search_suite.test(text, test_case.getPattern());
    }

    std::vector<std::string> result = {std::to_string(naive_search_suite.getOperations() / TESTS_AMOUNT),
                                       std::to_string(naive_search_suite.getTime() / TESTS_AMOUNT) + "\n"};

    return test_case.log(result);
}

void TestingManager::deactivateLoggers() {
    for (int i = 0; i < loggers.size(); ++i) {
        if (loggers[i].is_open()) {
            std::cout << "Logger " << i << " closed!\n";
            loggers[i].close();
        }
    }
}