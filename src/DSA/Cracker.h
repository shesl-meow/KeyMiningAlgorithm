//
// Created by 佘崧林 on 2020/5/5.
//

#ifndef KEYMININGALGORITHM_CRACKER_H
#define KEYMININGALGORITHM_CRACKER_H

#include "CommonStruct.h"

class Cracker {
private:
    const DSAPublicKey *pubKey = nullptr;
    const DSASignature *signature1 = nullptr;
    const DSASignature *signature2 = nullptr;
    DSAPrivateKey *prvKey = nullptr;

public:
    explicit Cracker(const DSAPublicKey *pk): pubKey(pk) {}

    void setSignature1(const DSASignature *sig) { this->signature1 = sig; }
    void setSignature2(const DSASignature *sig) { this->signature2 = sig; }
    void crack();
    const DSAPrivateKey *getPrivateKey() const { return this->prvKey; }

    ~Cracker();
};


#endif //KEYMININGALGORITHM_CRACKER_H
