//
// Created by 佘崧林 on 2020/1/22.
//

#ifndef KEYMININGALGORITHM_ABSTRACTBINTREE_H
#define KEYMININGALGORITHM_ABSTRACTBINTREE_H

#include <list>
#include <ostream>

template <typename DataType>
class AbstractBinTree {
protected:
    ~AbstractBinTree() {}
    DataType nodeData;
    AbstractBinTree *parentTree = nullptr;
    AbstractBinTree *leftChild = nullptr;
    AbstractBinTree *rightChild = nullptr;

public:
    void delete_node();
    void delete_tree();
    AbstractBinTree(const AbstractBinTree &copy);
    explicit AbstractBinTree(const DataType &data): nodeData(data) {}
    AbstractBinTree(const DataType &data, AbstractBinTree *lt, AbstractBinTree *rt);

    const DataType &getNodeData() const { return this->nodeData; }
    AbstractBinTree *getParent() const { return this->parentTree; }
    AbstractBinTree *getLeftChild() const { return this->leftChild; }
    AbstractBinTree *getRightChild() const { return this->rightChild; }
    unsigned int getNodeAmount() const;
    unsigned int getDepth() const;

    void setNodeData(const DataType &data) { this->nodeData = data; }
    void setParent(AbstractBinTree *data) { this->parentTree = data; }
    void preOrderForEach(const std::function<void(AbstractBinTree<DataType> *)> &exec);
    std::list<DataType> preOrderGetLeafList();
};

#import "./AbstractBinTree.tpp"

#endif //KEYMININGALGORITHM_ABSTRACTBINTREE_H
