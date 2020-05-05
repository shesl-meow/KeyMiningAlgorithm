//
// Created by 佘崧林 on 2020/1/22.
//
#include <cmath>
#include <queue>
#include "./ProductTree.h"
#include "../BinTree/BinTreeMap.h"

ProductTree::ProductTree(const std::vector<mpz_class>& leafVector) : AbstractBinTree(mpz_class(0)){
    auto *processQueue = new std::queue<AbstractBinTree *>(), *builtQueue = new std::queue<AbstractBinTree *>();
    for (const auto &leaf : leafVector) {
        processQueue->push(new AbstractBinTree(leaf));
    }

    mpz_t product;
    mpz_init(product);
    while (processQueue->size() > 1) {
        while (processQueue->size() > 1) {
            auto first = processQueue->front();
            processQueue->pop();
            auto second = processQueue->front();
            processQueue->pop();
            mpz_mul(product, first->getNodeData().get_mpz_t(), second->getNodeData().get_mpz_t());
            auto parent = new AbstractBinTree(mpz_class(product), first, second);
            builtQueue->push(parent);
        }
        if (!processQueue->empty()) {
            builtQueue->push(processQueue->front());
            processQueue->pop();
        }
        auto temp = processQueue;
        processQueue = builtQueue;
        builtQueue = temp;
    }
    mpz_clear(product);

    auto finalTree = processQueue->front();
    this->leftChild = finalTree->getLeftChild();
    this->rightChild = finalTree->getRightChild();
    this->nodeData = finalTree->getNodeData();
    finalTree->delete_node();
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
