//
// Created by 佘崧林 on 2020/5/5.
//

#ifndef KEYMININGALGORITHM_GETPRIVATE_H
#define KEYMININGALGORITHM_GETPRIVATE_H

#include <vector>
#include <unordered_map>
#include "CommonStruct.h"
#include "Cracker.h"

class GetPrivate {
private:
    unsigned int vecSize;
    const std::vector<DSAPublicKey>& pubVec;
    const std::vector<DSASignature>& sigVec;
    std::unordered_map<DSAPublicKey, Cracker, DSAPublicKey::Hasher> crackMap;

public:
    GetPrivate(const std::vector<DSAPublicKey>& pv, const std::vector<DSASignature>& sv);
    void buildCrackMap();
    std::vector<mpz_class> getPrivateVec() const;
};


#endif //KEYMININGALGORITHM_GETPRIVATE_H
