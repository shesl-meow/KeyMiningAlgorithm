//
// Created by 佘崧林 on 2020/5/5.
//

#ifndef KEYMININGALGORITHM_DSAGETPRIVATE_H
#define KEYMININGALGORITHM_DSAGETPRIVATE_H

#include <vector>
#include <unordered_map>
#include "DSACommonStruct.h"
#include "DSACracker.h"

class DSAGetPrivate {
private:
    unsigned int vecSize;
    const std::vector<DSAPublicKey>& pubVec;
    const std::vector<DSASignature>& sigVec;
    std::unordered_map<DSAPublicKey, DSACracker, DSAPublicKey::Hasher> crackMap;

public:
    DSAGetPrivate(const std::vector<DSAPublicKey>& pv, const std::vector<DSASignature>& sv);
    void buildCrackMap();
    std::vector<mpz_class> getPrivateVec() const;
};


#endif //KEYMININGALGORITHM_DSAGETPRIVATE_H
