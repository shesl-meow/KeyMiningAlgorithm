//
// Created by 佘崧林 on 2020/4/2.
//

#ifndef KEYMININGALGORITHM_BINTREEMAP_H
#define KEYMININGALGORITHM_BINTREEMAP_H

#include "./DisplayMap.h"
#include "./AbstractBinTree.h"

template<class T>
class BinTreeMap: public DisplayMap{
protected:
    uint root_row = 0;
    const AbstractBinTree<T> * bind_tree = nullptr;
public:
    BinTreeMap(const AbstractBinTree<T> *tree, std::string default_string = "  ");
    ~BinTreeMap(){}
    uint get_map_width()const{ return this->bind_tree->count_node_number(); }
    uint get_map_depth()const{ return this->bind_tree->depth()*2 - 1; }
    void draw();
};

#include "./BinTreeMap.tpp"

#endif //KEYMININGALGORITHM_BINTREEMAP_H
