//
// Created by 佘崧林 on 2020/1/24.
//

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE EfficientlyGCDTestCases
#include <boost/test/included/unit_test.hpp>
#include <boost/timer/timer.hpp>
#include <utility>

#include <RSA/EffientlyGcd.h>
#include <CommonMethod.h>

#include "EfficientlyGCDTestCases.h"

void testEfficientlyGcd(const std::vector<mpz_class> &productVec, const std::vector<mpz_class> &gcdVec, const std::string &msg = "Correctness")
{
    boost::timer::cpu_timer timer;
    auto *effientlyGcd = new EffientlyGcd(productVec);
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
            primeVec.emplace_back(randomPrimeWithBits(testCase.primeBits));
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
    std::vector<mpz_class> primeVec = continousPrimes(randomPrimeWithBits(PRBITS), PRCOUNT);
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
    uint32_t PRCOUNT = 2u << 14u, PRBITS = 1024;
    std::vector<mpz_class> primesVec = continousPrimes(randomPrimeWithBits(PRBITS), PRCOUNT);
    BOOST_TEST_MESSAGE("Init random prime time : " << timer.format());

    std::vector<mpz_class> productVec;
    mpz_t product;
    mpz_init(product);
    productVec.reserve(PRCOUNT / 2);
    for (uint i = 0; i < PRCOUNT / 2; i++) {
        mpz_mul(product, primesVec[2 * i].get_mpz_t(), primesVec[2 * i + 1].get_mpz_t());
        productVec.emplace_back(product);
    }
    mpz_clear(product);

    uint32_t PDUNIT = 512;
    for (uint i = 1u; PDUNIT * i <= PRCOUNT / 2; i++) {
        std::vector<mpz_class> pdv(productVec.begin(), productVec.begin() + PDUNIT * i);
        boost::timer::cpu_timer timer1, timer2;
        auto *effientlyGcd = new EffientlyGcd(pdv);
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
        for (uint j = 0u; j < PRCOUNT; j++) primeVec.emplace_back(randomPrimeWithBits(PRBUNIT * i));

        productVec.clear();
        productVec.reserve(PRCOUNT / 2);
        for (uint j = 0; j < PRCOUNT / 2; j++) {
            mpz_mul(product, primeVec[2*j].get_mpz_t(), primeVec[2*j+1].get_mpz_t());
            productVec.emplace_back(product);
        }

        boost::timer::cpu_timer timer1, timer2;
        auto *effientlyGcd = new EffientlyGcd(productVec);
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

BOOST_AUTO_TEST_CASE( write_prime_to_file )
{
    std::vector<mpz_class> productsVec, gcdsVec;
    mpz_t prod1, prod2, delta, p1, p2;
    mpz_inits(prod1, prod2, delta, p1, p2, NULL);
    std::ofstream pfo("../test/products.txt", std::ofstream::out), gfo("../test/gcds.txt", std::ofstream::out);
    const unsigned int PRMCOUNT = 1u << 18u;

    mpz_set(p1, randomPrimeWithBits(1024).get_mpz_t());
    mpz_nextprime(p2, p1);
    mpz_mul(prod2, p1, p2);
    pfo << PRMCOUNT << std::endl << mpz_class(prod2).get_str(16) << std::endl;
    gfo << PRMCOUNT << std::endl << 1 << std::endl;

    for (unsigned int i = 1u; i < PRMCOUNT; i++) {
        mpz_set(prod1, prod2);
        mpz_nextprime(p1, p2);
        mpz_nextprime(p2, p1);
        mpz_mul(prod2, p1, p2);
        mpz_sub(delta, prod2, prod1);
        pfo << mpz_class(delta).get_str(16) << std::endl;
        gfo << 0 << std::endl;
    }

    pfo.close();
    gfo.close();
    productsVec.clear();
    gcdsVec.clear();
    mpz_clears(prod1, prod2, delta, p1, p2, NULL);
}

BOOST_AUTO_TEST_CASE ( read_prime_from_file )
{
    std::vector<mpz_class> productsVec, gcdsVec;
    std::string pline, gline;
    mpz_t product, pdelta, gcd, gdelta;
    mpz_inits(product, pdelta, gcd, gdelta, NULL);
    std::ifstream pfi("../test/products.txt"), gfi("../test/gcds.txt");
    size_t size;

    std::getline(pfi, pline);
    size = std::stoi(pline);
    productsVec.reserve(size);
    pfi >> pline;
    mpz_set_str(product, pline.c_str(), 16);
    productsVec.emplace_back(product);
    while (pfi >> pline) {
        mpz_set_str(pdelta, pline.c_str(), 16);
        mpz_add(product, product, pdelta);
        productsVec.emplace_back(product);
    }

    std::getline(gfi, gline);
    size = std::stoi(gline);
    gcdsVec.reserve(size);
    gfi >> gline;
    mpz_set_str(gcd, gline.c_str(), 16);
    productsVec.emplace_back(gcd);
    while (gfi >> gline) {
        mpz_set_str(gdelta, gline.c_str(), 16);
        mpz_add(gcd, gcd, gdelta);
        gcdsVec.emplace_back(gcd);
    }

    pfi.close();
    gfi.close();
    mpz_clears(product, pdelta, gcd, gdelta, NULL);
    testEfficientlyGcd(productsVec, gcdsVec);
}