//
// Created by 佘崧林 on 2020/5/5.
//

#ifndef KEYMININGALGORITHM_DSACRACKER_H
#define KEYMININGALGORITHM_DSACRACKER_H

#include "DSACommonStruct.h"

class DSACracker {
private:
    const DSAPublicKey *pubKey = nullptr;
    const DSASignature *signature1 = nullptr;
    const DSASignature *signature2 = nullptr;
    DSAPrivateKey *prvKey = nullptr;

public:
    explicit DSACracker(const DSAPublicKey *pk): pubKey(pk) {}

    void setSignature1(const DSASignature *sig) { this->signature1 = sig; }
    void setSignature2(const DSASignature *sig) { this->signature2 = sig; }
    void crack();
    const DSAPrivateKey *getPrivateKey() const { return this->prvKey; }

    ~DSACracker();
};


#endif //KEYMININGALGORITHM_DSACRACKER_H
