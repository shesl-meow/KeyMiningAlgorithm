//
// Created by 佘崧林 on 2020/4/16.
//

#ifndef KEYMININGALGORITHM_RSAEFFIENTLYGCD_H
#define KEYMININGALGORITHM_RSAEFFIENTLYGCD_H

#include <vector>
#include <gmpxx.h>

#include "../src/ProductTree.h"
#include "../src/RemainderTree.h"

class RSAEffientlyGcd {
private:
    const std::vector<mpz_class>& rawNumbersVec;
    std::vector<mpz_class> finalGcdsVec;
    std::vector<mpz_class> bigNumbers;
    unsigned int step = 0;

    ProductTree *productTree = nullptr;
    RemainderTree *remainderTree = nullptr;

public:
    explicit RSAEffientlyGcd(const std::vector<mpz_class> &rnv) : rawNumbersVec(rnv) {}

    void S0_excludeUnexpectedNumbers();
    void S1_buildProductTree();
    void S2_buildRemainderTree();
    void S3_getGcdsFromRTree();

    const std::vector<mpz_class> *getGcdVector() const;
    ~RSAEffientlyGcd();
};


#endif //KEYMININGALGORITHM_RSAEFFIENTLYGCD_H
