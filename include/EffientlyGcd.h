//
// Created by 佘崧林 on 2020/4/16.
//

#ifndef KEYMININGALGORITHM_EFFIENTLYGCD_H
#define KEYMININGALGORITHM_EFFIENTLYGCD_H

#include <vector>
#include <gmpxx.h>

#include "../src/ProductTree.h"
#include "../src/RemainderTree.h"

class EffientlyGcd {
private:
    const std::vector<mpz_class>& rawNumbersVec;
    std::vector<mpz_class> finalGcdsVec;
    std::vector<mpz_class> bigNumbers;
    unsigned int step = 0;

    ProductTree *productTree = nullptr;
    RemainderTree *remainderTree = nullptr;

public:
    explicit EffientlyGcd(const std::vector<mpz_class> &rnv) : rawNumbersVec(rnv) {}

    void S0_excludeUnexpectedNumbers();
    void S1_buildProductTree();
    void S2_buildRemainderTree();
    void S3_getGcdsFromRTree();

    const std::vector<mpz_class> *getGcdVector() const;
    unsigned long long computeSpaceSize() const;
    ~EffientlyGcd();
};


#endif //KEYMININGALGORITHM_EFFIENTLYGCD_H
