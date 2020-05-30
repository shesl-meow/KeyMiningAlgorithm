//
// Created by 佘崧林 on 2020/5/27.
//

#ifndef KEYMININGALGORITHM_SIGNATURE_H
#define KEYMININGALGORITHM_SIGNATURE_H

#import "CommonStruct.h"

class Signature {
public:
    static DSAKeyPair *randomKey(uint64_t p_size);
    static DSASignature *signMessage(DSAKeyPair *dsaKey, mpz_class message);
};


#endif //KEYMININGALGORITHM_SIGNATURE_H
