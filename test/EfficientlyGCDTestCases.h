//
// Created by 佘崧林 on 2020/4/2.
//

#ifndef KEYMININGALGORITHM_EFFICIENTLYGCDTESTCASES_H
#define KEYMININGALGORITHM_EFFICIENTLYGCDTESTCASES_H
#include <vector>
#include <string>
#include <gmpxx.h>

typedef struct {
    std::string testMessage;
    std::vector<mpz_class> bigNumbersVector;
    std::vector<mpz_class> expectedRemaindersVector;
} EgcdTestCaseType;

EgcdTestCaseType __CASE1 = {
        .testMessage = "Normal test case",
        .bigNumbersVector = {15, 77, 221, 57},
        .expectedRemaindersVector = {3, 1, 1, 3}
};

EgcdTestCaseType __CASE2 = {
        .testMessage = "Case1: Amount isnot equal to 2^k",
        .bigNumbersVector = {15, 77, 221, 57, 667},
        .expectedRemaindersVector = {3, 1, 1, 3, 1}
};

EgcdTestCaseType __CASE3 = {
        .testMessage = "Case2: Amount isnot equal to 2^k",
        .bigNumbersVector = {15, 77, 221, 57, 667, 217},
        .expectedRemaindersVector = {3, 7, 1, 3, 1, 7}
};

EgcdTestCaseType __CASE4 = {
        .testMessage = "Case3: Amount isnot equal to 2^k",
        .bigNumbersVector = {221, 57, 15, 667, 217, 1763, 77,},
        .expectedRemaindersVector = {1, 3, 3, 1, 7, 1, 7,}
};

EgcdTestCaseType __CASE5 = {
        .testMessage = "Numbers contain 0",
        .bigNumbersVector = {0, 57, 15, 667, 217, 1763, 77,},
        .expectedRemaindersVector = {1, 3, 3, 1, 7, 1, 7,}};

std::vector<EgcdTestCaseType> egcdTestCases = {
        __CASE1, __CASE2, __CASE3, __CASE4, __CASE5
};

#endif //KEYMININGALGORITHM_EFFICIENTLYGCDTESTCASES_H
