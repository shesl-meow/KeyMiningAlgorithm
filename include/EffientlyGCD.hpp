//
// Created by 佘崧林 on 2020/1/22.
//
#ifndef KEYMININGALGORITHM_EFFIENTLYGCD_HPP
#define KEYMININGALGORITHM_EFFIENTLYGCD_HPP

#include <gmpxx.h>
#include <list>
#if BOOST_TEST_MODULE == EfficientlyGCDTestCases
#include <boost/test/included/unit_test.hpp>
#endif

#include "../src/ProductTree.h"
#include "../src/RemainderTree.h"

std::vector<mpz_class> EffientlyGCD(const std::vector<mpz_class>& bigNumbers) {
    // TODO: exclude unexpected numbers
    auto size = bigNumbers.size();
    std::vector<mpz_class> cpBigNumbers, gcdVector;
    cpBigNumbers.reserve(size), gcdVector.reserve(size);
    for (const auto& bnum : bigNumbers) {
        if (bnum < 0) gcdVector.push_back(bnum);
        else if (bnum == 0) gcdVector.emplace_back(1);
        else {
            gcdVector.emplace_back(0);
            cpBigNumbers.push_back(bnum);
        }
    }

    // TODO: STEP1 - build product tree from RSA moduli
    auto *productTree = new ProductTree(cpBigNumbers);
    std::list<mpz_class> productLeaf = productTree->preOrderGetLeafList();
#if BOOST_TEST_MODULE == EfficientlyGCDTestCases
    {
        BOOST_REQUIRE_MESSAGE(productLeaf.size() == cpBigNumbers.size(), "Product tree leaf number");
        bool testFlag = true;
        auto p = productLeaf.begin();
        auto b = cpBigNumbers.begin();
        for (; p != productLeaf.end() && b != cpBigNumbers.end(); p++, b++) {
            if (*p != *b) testFlag = false;
        }
        BOOST_REQUIRE_MESSAGE(testFlag, "Product tree leaf order");
        BOOST_TEST_MESSAGE("Product tree:\n" << *productTree);
    }
#endif


    // TODO: STEP2 - compute remainder tree with `P mod N^2`
    auto *remainderTree = new RemainderTree((const ProductTree *&)productTree);
    std::list<mpz_class> remainderLeaf = remainderTree->preOrderGetLeafList();

    // TODO: STEP3 - compute `gcd(N, z/N)`
    mpz_t quotientNumber, gcdNumber;
    mpz_inits(quotientNumber, gcdNumber, NULL);
    auto N = productLeaf.begin(), z = remainderLeaf.begin();
    for (auto& gcd: gcdVector) {
        if (gcd != 0) continue;
        mpz_div(quotientNumber, z->get_mpz_t(), N->get_mpz_t());
        mpz_gcd(gcdNumber, quotientNumber, N->get_mpz_t());
        gcd = mpz_class(gcdNumber);
        N++, z++;
    }
    mpz_clears(quotientNumber, gcdNumber, NULL);
    delete productTree;
    delete remainderTree;
    return gcdVector;
}

#endif