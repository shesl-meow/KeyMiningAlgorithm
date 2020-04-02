//
// Created by 佘崧林 on 2020/1/22.
//
#pragma once
#include "./AbstractBinTree.h"

template<typename DataType>
AbstractBinTree<DataType>::~AbstractBinTree() {
    if (this->leftChild != nullptr) {
        delete this->leftChild;
        this->leftChild = nullptr;
    }
    if (this->rightChild != nullptr) {
        delete this->rightChild;
        this->rightChild = nullptr;
    }
}

template<typename DataType>
AbstractBinTree<DataType>::AbstractBinTree(const AbstractBinTree &copy) {
    this->nodeData = copy.getNodeData();
    if (copy.getLeftChild() != nullptr) {
        this->leftChild = new AbstractBinTree(*copy.getLeftChild());
        this->leftChild->setParent(this);
    }
    if (copy.getRightChild() != nullptr) {
        this->rightChild = new AbstractBinTree(*copy.getRightChild());
        this->rightChild->setParent(this);
    }
}

template<typename DataType>
AbstractBinTree<DataType>::AbstractBinTree(const DataType &data, AbstractBinTree *lt, AbstractBinTree *rt)
    : nodeData(data), leftChild(lt), rightChild(rt) {
    assert(lt->parentTree == nullptr && rt->parentTree == nullptr);
    lt->parentTree = this;
    rt->parentTree = this;
}

template<typename DataType>
unsigned int AbstractBinTree<DataType>::getNodeAmount() const {
    unsigned int count = 1;
    if (this->leftChild != nullptr) count += this->leftChild->getNodeAmount();
    if (this->rightChild != nullptr) count += this->rightChild->getNodeAmount();
    return count;
}

template<typename DataType>
unsigned int AbstractBinTree<DataType>::getDepth() const {
    unsigned int ld = (this->leftChild == nullptr) ? 0 : this->leftChild->getDepth();
    unsigned int rd = (this->rightChild == nullptr) ? 0 : this->rightChild->getDepth();
    return (ld > rd) ? ld+1 : rd+1;
}

template<typename DataType>
void AbstractBinTree<DataType>::preOrderForEach(const std::function<void(AbstractBinTree<mpz_class> *)> &exec) {
    exec(this);
    if (this->leftChild != nullptr) this->leftChild->preOrderForEach(exec);
    if (this->rightChild != nullptr) this->rightChild->preOrderForEach(exec);
}

template<typename DataType>
std::list<DataType> AbstractBinTree<DataType>::preOrderGetLeafList(){
    std::list<DataType> leafList;
    this->preOrderForEach([&leafList](AbstractBinTree *root) {
        if (root->leftChild == nullptr && root->rightChild == nullptr) leafList.push_back(root->getNodeData());
    });
    return leafList;
}