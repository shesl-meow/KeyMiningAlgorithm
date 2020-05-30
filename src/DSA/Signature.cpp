//
// Created by 佘崧林 on 2020/5/27.
//

#include "Signature.h"
#include "../../include/CommonMethod.h"

DSAKeyPair *Signature::randomKey(uint64_t p_size)
{
    mpz_t y_t; mpz_init(y_t);
    mpz_class p = randomPrimeWithBits(p_size), g = 1, x = 1;
    while (g == mpz_class(1) || g == mpz_class(0)) {
        g = randomPrimeWithMax(p);
    }
    while (x == mpz_class(1) || x == mpz_class(0)) {
        x = randomPrimeWithMax(p);
    }
    mpz_powm(y_t, g.get_mpz_t(), x.get_mpz_t(), p.get_mpz_t());
    auto *pubk = new DSAPublicKey{.g = g, .p = p, .y = mpz_class(y_t)};
    auto *prvk = new DSAPrivateKey(x.get_mpz_t());
    mpz_clear(y_t);

    auto *dsaKey = new DSAKeyPair();
    dsaKey->pubkey = pubk; dsaKey->prvkey = prvk;
    return dsaKey;
}

DSASignature *Signature::signMessage(DSAKeyPair *dsaKey, mpz_class hash_m)
{
    mpz_class k = 1;
    mpz_t revk, p_1, tmp, r, s;
    mpz_inits(revk, p_1, tmp, r, s, NULL);
    mpz_sub_ui(p_1, dsaKey->pubkey->p.get_mpz_t(), 1);
    mpz_set_d(tmp, 0);
    mpz_set_d(s, 0);
    while (mpz_class(s) != mpz_class(0)) {
        while (
                k == mpz_class(1) ||
                k == mpz_class(0) ||
                mpz_class(tmp) != mpz_class(1)
                ) {
            k = randomPrimeWithMax(mpz_class(p_1));
            mpz_gcd(tmp, p_1, k.get_mpz_t());
        }
        mpz_powm(r, dsaKey->pubkey->g.get_mpz_t(), k.get_mpz_t(), dsaKey->pubkey->g.get_mpz_t());
        mpz_mul(tmp, dsaKey->prvkey->x.get_mpz_t(), r);
        mpz_sub(tmp, hash_m.get_mpz_t(), tmp);
        mpz_invert(revk, k.get_mpz_t(), p_1);
        mpz_mul(tmp, tmp, revk);
        mpz_mod(s, tmp, p_1);
    }
    auto *signature = new DSASignature{.r = mpz_class(r), .s = mpz_class(s)};
    mpz_clears(revk, p_1, tmp, r, s, NULL);
    return signature;
}
