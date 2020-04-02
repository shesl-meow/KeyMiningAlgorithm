//
// Created by 佘崧林 on 2020/1/22.
//
#include <cmath>
#include "ProductTree.h"
#include "./BinTree/BinTreeMap.h"

ProductTree::ProductTree(const std::vector<mpz_class>& leafVector) : AbstractBinTree(mpz_class(0)){
    std::list<AbstractBinTree *> processQueue, bufferQueue1, bufferQueue2;
    for (const auto &leaf : leafVector) {
        bufferQueue1.push_back(new AbstractBinTree(leaf));
    }
    size_t processSize = 0, bufferSize1 = bufferQueue1.size();

    mpz_t productData;
    mpz_init(productData);
    // TODO: Optimize ME
    while (bufferSize1 > 1) {
        while (bufferSize1 > 0) {
            assert(processQueue.empty());

            processSize = pow(2u, floor( log2l(bufferSize1) ));
            auto endPosition = bufferQueue1.begin();
            std::advance(endPosition, processSize);
            processQueue.splice(processQueue.end(), bufferQueue1, bufferQueue1.begin(), endPosition);
            bufferSize1 -= processSize;

            for (; processSize > 1; processSize--) {
                AbstractBinTree *first = processQueue.front();
                processQueue.pop_front();
                AbstractBinTree *second = processQueue.front();
                processQueue.pop_front();
                mpz_mul(productData, first->getNodeData().get_mpz_t(), second->getNodeData().get_mpz_t());
                auto *parentTree = new AbstractBinTree(mpz_class(productData), first, second);
                processQueue.push_back(parentTree);
            }
            bufferQueue2.splice(bufferQueue2.end(), processQueue, processQueue.begin());
        }
        bufferQueue1.splice(bufferQueue1.begin(), bufferQueue2);
        bufferSize1 = bufferQueue1.size();
    }
    mpz_clear(productData);

    AbstractBinTree<mpz_class> *finalTree = bufferQueue1.front();
    *this = *finalTree;
    delete finalTree;
}

ProductTree &ProductTree::operator=(const AbstractBinTree<mpz_class> &copy) {
    this->nodeData = copy.getNodeData();
    if (copy.getLeftChild() != nullptr) {
        this->leftChild = new AbstractBinTree(*copy.getLeftChild());
        this->leftChild->setParent(this);
    }
    if (copy.getRightChild() != nullptr) {
        this->rightChild = new AbstractBinTree(*copy.getRightChild());
        this->rightChild->setParent(this);
    }
    return *this;
}

std::ostream& operator<<(std::ostream& out, const ProductTree& bt)
{
    return out << std::string(BinTreeMap<mpz_class>(&bt));
}
