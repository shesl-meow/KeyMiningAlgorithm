//
// Created by 佘崧林 on 2020/4/16.
//

#include "EffientlyGcd.h"

void EffientlyGcd::S0_excludeUnexpectedNumbers() {
    if (step != 0) return;
    auto size = rawNumbersVec.size();
    this->bigNumbers.reserve(size);
    this->finalGcdsVec.reserve(size);
    for (const auto& bnum : rawNumbersVec) {
        if (bnum < 0) finalGcdsVec.push_back(bnum);
        else if (bnum == 0) finalGcdsVec.emplace_back(1);
        else {
            finalGcdsVec.emplace_back(0);
            bigNumbers.push_back(bnum);
        }
    }
    step += 1;
}

void EffientlyGcd::S1_buildProductTree() {
    if (step != 1) return;
    delete this->productTree;
    this->productTree = new ProductTree(this->bigNumbers);
    step += 1;
}

void EffientlyGcd::S2_buildRemainderTree() {
    if (step != 2) return;
    delete this->remainderTree;
    this->remainderTree = new RemainderTree(productTree);
    step += 1;
}

void EffientlyGcd::S3_getGcdsFromRTree() {
    if (step != 3) return;
    mpz_t quotientNumber, gcdNumber;
    mpz_inits(quotientNumber, gcdNumber, NULL);

    auto productLeaf = this->productTree->preOrderGetLeafList();
    auto remainderLeaf = this->remainderTree->preOrderGetLeafList();
    auto N = productLeaf.begin(), z = remainderLeaf.begin();
    for (auto& gcd: this->finalGcdsVec) {
        if (gcd != 0) continue;
        mpz_div(quotientNumber, z->get_mpz_t(), N->get_mpz_t());
        mpz_gcd(gcdNumber, quotientNumber, N->get_mpz_t());
        gcd = mpz_class(gcdNumber);
        N++, z++;
    }
    mpz_clears(quotientNumber, gcdNumber, NULL);
    step += 1;
}

const std::vector<mpz_class> *EffientlyGcd::getGcdVector() const {
    if (step != 4) return nullptr;
    return &(this->finalGcdsVec);
}

EffientlyGcd::~EffientlyGcd() {
    this->productTree->delete_tree();
    this->remainderTree->delete_tree();
}

