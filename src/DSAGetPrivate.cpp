//
// Created by 佘崧林 on 2020/5/5.
//

#include "DSAGetPrivate.h"

DSAGetPrivate::DSAGetPrivate(const std::vector<DSAPublicKey> &pv, const std::vector<DSASignature> &sv) : pubVec(pv), sigVec(sv) {
    vecSize = (sigVec.size() != pubVec.size()) ? 0 : sigVec.size();
}

void DSAGetPrivate::buildCrackMap() {
    for (unsigned int i = 0; i < vecSize; i++) {
        auto mapIt = crackMap.find(pubVec[i]);
        if (mapIt == crackMap.end()) {
            crackMap[pubVec[i]] = DSACracker(&(pubVec[i]));
            crackMap[pubVec[i]].setSignature1(&(sigVec[i]));
        } else if (mapIt->second.getPrivateKey() == nullptr) {
            mapIt->second.setSignature2(&(sigVec[i]));
            mapIt->second.crack();
        }
    }
}

std::vector<mpz_class> DSAGetPrivate::getPrivateVec() const {
    std::vector<mpz_class> prvVec;
    prvVec.reserve(vecSize);
    for (unsigned int i = 0; i < vecSize; i++) {
        prvVec.push_back(crackMap.find(pubVec[i])->second.getPrivateKey()->x);
    }
    return prvVec;
}

