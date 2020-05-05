//
// Created by 佘崧林 on 2020/5/5.
//

#ifndef KEYMININGALGORITHM_DSACOMMONSTRUCT_H
#define KEYMININGALGORITHM_DSACOMMONSTRUCT_H

#include <gmpxx.h>
#include <string>
#include <utility>
/*
 *  Public Parameter: `p` is prime, `g` < p
 *  Private Key: Any `x`: 1 < x < p-1
 *  Public Key: `y` = g^{x} mod p
 *  Signature:
 *      Any k, `r` = g^{k} mod p
 *      H(m) = xr + k`s` \pmod{p-1}
 */

struct DSAPublicKey {
    mpz_class g;
    mpz_class p;
    mpz_class y;
    bool operator==(const DSAPublicKey& op) const {
        return (g == op.g) && (p == op.p) && (y == op.y);
    }
    struct Hasher
    {
        std::size_t operator()(const DSAPublicKey& pk) const
        {
            auto hasher = std::hash<std::string>();
            return hasher(pk.g.get_str(16)) ^ hasher(pk.p.get_str(16)) ^ hasher(pk.y.get_str(16));
        }
    };
};

struct DSAPrivateKey{
    mpz_class x;
    explicit DSAPrivateKey(mpz_t i): x(mpz_class(i)) {}
} ;

struct DSASignature{
    mpz_class hash_m;
    mpz_class r;
    mpz_class s;
};

#endif //KEYMININGALGORITHM_DSACOMMONSTRUCT_H
