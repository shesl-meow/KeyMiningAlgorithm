//
// Created by 佘崧林 on 2020/1/24.
//

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE EfficientlyGCDTestCases
#include <boost/test/included/unit_test.hpp>

#include <EffientlyGCD.hpp>

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



BOOST_AUTO_TEST_CASE ( egcd_test ) {
    for (const auto& testCase : egcdTestCases) {
        auto gcdVector = EffientlyGCD(testCase.bigNumbersVector);
        BOOST_REQUIRE_MESSAGE(gcdVector == testCase.expectedRemaindersVector, testCase.testMessage);
    }
}