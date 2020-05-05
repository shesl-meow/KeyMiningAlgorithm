//
// Created by 佘崧林 on 2020/1/24.
//

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE EfficientlyGCDTestCases
#include <boost/test/included/unit_test.hpp>
#include <boost/timer/timer.hpp>

#include <RSAEffientlyGcd.h>

#include "EfficientlyGCDTestCases.h"

mpz_class generatePrime(size_t nbits) {
    static time_t seed;
    static gmp_randstate_t random_state;
    if (!seed) {
        seed = time(nullptr);
        gmp_randinit_mt(random_state);
        gmp_randseed_ui(random_state, seed);
    }

    mpz_t prime; mpz_init(prime);
    mpz_urandomb(prime, random_state, nbits);
    mpz_nextprime(prime, prime);

    mpz_class result = mpz_class(prime);
    mpz_clear(prime);
    return mpz_class(prime);
}

void testEfficientlyGcd(const std::vector<mpz_class> &productVec, const std::vector<mpz_class> &gcdVec, const std::string &msg = "Correctness")
{
    boost::timer::cpu_timer timer;
    auto *effientlyGcd = new RSAEffientlyGcd(productVec);
    BOOST_TEST_MESSAGE("Init : " << timer.format());
    effientlyGcd->S0_excludeUnexpectedNumbers();
    BOOST_TEST_MESSAGE("STEP0: " << timer.format());
    effientlyGcd->S1_buildProductTree();
//    std::cout << *(effientlyGcd->getProductTree()) << std::endl;
    BOOST_TEST_MESSAGE("STEP1: " << timer.format());
    effientlyGcd->S2_buildRemainderTree();
    BOOST_TEST_MESSAGE("STEP2: " << timer.format());
    effientlyGcd->S3_getGcdsFromRTree();
    BOOST_TEST_MESSAGE("STEP3: " << timer.format());
    auto remainderLeaf = effientlyGcd->getGcdVector();
//    for (uint i = 0; i < gcdVec.size(); i++) {
//        std::cout << remainderLeaf->at(i).get_str(16) << "\t" << gcdVec[i].get_str(16) << std::endl;
//    }
    BOOST_REQUIRE_MESSAGE(*remainderLeaf == gcdVec, msg);
    BOOST_TEST_MESSAGE("Test time" << timer.format());
    delete effientlyGcd;
}


BOOST_AUTO_TEST_CASE ( egcd_test )
{
    for (const auto& testCase : egcdTestCases) {
        testEfficientlyGcd(testCase.bigNumbersVector, testCase.expectedRemaindersVector, testCase.testMessage);
    }
}

BOOST_AUTO_TEST_CASE( tgcd_test )
{
    mpz_t product;
    mpz_init(product);
    for (const auto& testCase : tgcdTestCases) {
        std::vector<mpz_class> primeVec, productVec, gcdVec(testCase.primeCount / 2, 1);
        primeVec.reserve(testCase.primeCount);
        productVec.reserve(testCase.primeCount / 2 + testCase.prodPairsVec.size());
        gcdVec.reserve(testCase.primeCount / 2 + testCase.prodPairsVec.size());

        for (uint i = 0u; i < testCase.primeCount; ++i) {
            primeVec.emplace_back(generatePrime(testCase.primeBits));
        }
        for (uint i = 0u; i < testCase.primeCount / 2; i++) {
            mpz_mul(product, primeVec[2*i].get_mpz_t(), primeVec[2*i + 1].get_mpz_t());
            productVec.emplace_back(product);
        }
        for (auto ppv : testCase.prodPairsVec) {
            mpz_ptr first = primeVec[ppv.first].get_mpz_t(), second = primeVec[ppv.second].get_mpz_t();
            mpz_mul(product, first, second);
            productVec.emplace_back(product);
            gcdVec.emplace_back(product);
            gcdVec[ppv.first / 2] *= primeVec[ppv.first];
            gcdVec[ppv.second / 2] *= primeVec[ppv.second];
        }
        testEfficientlyGcd(productVec, gcdVec);
    }
    mpz_clear(product);
}

BOOST_AUTO_TEST_CASE( time_cost_test_1024 )
{
    mpz_t product;
    mpz_init(product);
    boost::timer::cpu_timer timer;
    uint32_t PRCOUNT = 2046, PRBITS = 1024;
    std::vector<mpz_class> primeVec;
    primeVec.reserve(PRCOUNT);
    for (uint i = 0u; i < PRCOUNT; i++) primeVec.emplace_back(generatePrime(PRBITS));
    BOOST_TEST_MESSAGE("Init random prime time : " << timer.format());

    uint32_t PDCOUNT = 1024;
    std::vector<mpz_class> productVec, gcdVec(PDCOUNT, 1);
    productVec.reserve(PDCOUNT);
    for (uint i = 0; i < PDCOUNT - 1; i++) {
        mpz_mul(product, primeVec[2*i].get_mpz_t(), primeVec[2*i+1].get_mpz_t());
        productVec.emplace_back(product);
    }
    mpz_mul(product, primeVec[0].get_mpz_t(), primeVec[PRCOUNT - 1].get_mpz_t());
    productVec.emplace_back(product);
    gcdVec[0] = primeVec[0];
    gcdVec[PDCOUNT - 1] = mpz_class(product);
    gcdVec[PDCOUNT - 2] = primeVec[PRCOUNT - 1];
    BOOST_TEST_MESSAGE("Init prime product time: " << timer.format());
    mpz_clear(product);
    testEfficientlyGcd(productVec, gcdVec);
}


BOOST_AUTO_TEST_CASE ( time_cost_graph_with_amount )
{
    boost::timer::cpu_timer timer;
    uint32_t PRCOUNT = 2u << 13u, PRBITS = 1024;
    std::vector<mpz_class> primeVec;
    primeVec.reserve(PRCOUNT);
    for (uint i = 0u; i < PRCOUNT; i++) primeVec.emplace_back(generatePrime(PRBITS));
    BOOST_TEST_MESSAGE("Init random prime time : " << timer.format());

    std::vector<mpz_class> productVec;
    mpz_t product;
    mpz_init(product);
    productVec.reserve(PRCOUNT / 2);
    for (uint i = 0; i < PRCOUNT / 2; i++) {
        mpz_mul(product, primeVec[2*i].get_mpz_t(), primeVec[2*i+1].get_mpz_t());
        productVec.emplace_back(product);
    }
    mpz_clear(product);

    uint32_t PDUNIT = 512;
    for (uint i = 1u; PDUNIT * i <= PRCOUNT / 2; i++) {
        std::vector<mpz_class> pdv(productVec.begin(), productVec.begin() + PDUNIT * i);
        boost::timer::cpu_timer timer1, timer2;
        auto *effientlyGcd = new RSAEffientlyGcd(pdv);
        effientlyGcd->S0_excludeUnexpectedNumbers();
        effientlyGcd->S1_buildProductTree();
        timer2.start();
        effientlyGcd->S2_buildRemainderTree();
        timer2.stop();
        effientlyGcd->S3_getGcdsFromRTree();
        timer1.stop();
        delete effientlyGcd;
        BOOST_TEST_MESSAGE(PDUNIT * i << ", " << timer1.elapsed().user / 1000000000.0 << ", " << timer2.elapsed().user / 1000000000.0);
    }
}

BOOST_AUTO_TEST_CASE ( time_cost_graph_with_bitlength )
{
    uint32_t PRCOUNT = 1024, PRBITS = 2048, PRBUNIT = 256;
    std::vector<mpz_class> primeVec, productVec;
    mpz_t product;
    mpz_init(product);

    for (uint i = 1u; PRBUNIT * i <= PRBITS; i++) {
        primeVec.clear();
        primeVec.reserve(PRCOUNT);
        for (uint j = 0u; j < PRCOUNT; j++) primeVec.emplace_back(generatePrime(PRBUNIT * i));

        productVec.clear();
        productVec.reserve(PRCOUNT / 2);
        for (uint j = 0; j < PRCOUNT / 2; j++) {
            mpz_mul(product, primeVec[2*j].get_mpz_t(), primeVec[2*j+1].get_mpz_t());
            productVec.emplace_back(product);
        }

        boost::timer::cpu_timer timer1, timer2;
        auto *effientlyGcd = new RSAEffientlyGcd(productVec);
        effientlyGcd->S0_excludeUnexpectedNumbers();
        effientlyGcd->S1_buildProductTree();
        timer2.start();
        effientlyGcd->S2_buildRemainderTree();
        timer2.stop();
        effientlyGcd->S3_getGcdsFromRTree();
        timer1.stop();
        delete effientlyGcd;
        BOOST_TEST_MESSAGE(PRBUNIT * i << ", " << timer1.elapsed().user / 1000000000.0 << ", " << timer2.elapsed().user / 1000000000.0);
    }
    mpz_clear(product);
}