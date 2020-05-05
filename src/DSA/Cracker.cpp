//
// Created by 佘崧林 on 2020/5/5.
//

#include "Cracker.h"

void Cracker::crack() {
    if (signature1 == nullptr || signature2 == nullptr) return;
    mpz_t t0, t1, t2, k;
    mpz_inits(t0, t1, t2, k, NULL);

    mpz_sub_ui(t0, pubKey->p.get_mpz_t(), 1u);
    mpz_sub(t1, signature1->hash_m.get_mpz_t(), signature2->hash_m.get_mpz_t());
    mpz_sub(t2, signature1->s.get_mpz_t(), signature2->s.get_mpz_t());
    mpz_invert(t2, t2, t0);
    mpz_mul(t1, t1, t2);
    mpz_mod(k, t1, t0);

    mpz_mul(t1, k, signature1->s.get_mpz_t());
    mpz_sub(t1, signature1->hash_m.get_mpz_t(), t1);
    mpz_invert(t2, signature1->r.get_mpz_t(), t0);
    mpz_mul(t1, t1, t2);
    mpz_mod(t1, t1, t0);
    delete prvKey;
    prvKey = new DSAPrivateKey(t1);

    mpz_clears(t0, t1, t2, k, NULL);
}

Cracker::~Cracker() {
    delete this->prvKey;
}
