//
// Created by 佘崧林 on 2020/5/27.
//

#ifndef KEYMININGALGORITHM_COMMONMETHOD_H
#define KEYMININGALGORITHM_COMMONMETHOD_H

#include <gmpxx.h>
#include <vector>

mpz_class randomPrimeWithBits(size_t nbits)
{
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

mpz_class randomPrimeWithMax(mpz_class maxn)
{
    static time_t seed;
    static gmp_randstate_t random_state;
    if (!seed) {
        seed = time(nullptr);
        gmp_randinit_mt(random_state);
        gmp_randseed_ui(random_state, seed);
    }

    mpz_t prime; mpz_init(prime);
    mpz_set_d(prime, 0);
    while (mpz_class(prime) < 2 || mpz_class(prime) > maxn) {
        mpz_urandomm(prime, random_state, maxn.get_mpz_t());
        mpz_nextprime(prime, prime);
    }
    mpz_class result = mpz_class(prime);
    mpz_clear(prime);
    return mpz_class(prime);
}

std::vector<mpz_class> continousPrimes(const mpz_class& first, size_t size)
{
    std::vector<mpz_class> pv = {first};
    pv.reserve(size);

    mpz_t prime; mpz_init(prime);
    mpz_set(prime, first.get_mpz_t());
    for (size_t i = 0; i < size - 1; i++) {
        mpz_nextprime(prime, prime);
        pv.emplace_back(prime);
    }
    return pv;
}

#endif //KEYMININGALGORITHM_COMMONMETHOD_H
