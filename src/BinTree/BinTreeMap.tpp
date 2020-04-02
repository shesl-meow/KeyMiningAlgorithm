//
// Created by 佘崧林 on 2020/4/2.
//

#pragma once

typedef unsigned int uint;

template<class T>
BinTreeMap<T>::BinTreeMap(const AbstractBinTree<T> *tree, std::string default_string):
        bind_tree(tree),
        DisplayMap(
                tree->getNodeAmount(),
                tree->getDepth()*2 - 1,
                default_string
        ){ this->draw(); }

template<class T>
void BinTreeMap<T>::draw(){
    BinTreeMap<T> *lft_map = nullptr, *rgt_map = nullptr;
    if(this->bind_tree->getLeftChild() != nullptr){
        lft_map = new BinTreeMap<T>(this->bind_tree->getLeftChild());
        this->set_sub_area(0, 2, lft_map);
    }
    if(this->bind_tree->getRightChild() != nullptr){
        rgt_map = new BinTreeMap<T>(this->bind_tree->getRightChild());
        this->set_sub_area(lft_map->row + 1, 2, rgt_map);
    }
    this->root_row = (lft_map == nullptr) ? 0 : lft_map->row;
    std::stringstream ss;
    // FIXME
    ss << this->bind_tree->getNodeData().get_str();

    // begin to draw the tree branch
    if(lft_map != nullptr)
    {
        this->string_map[lft_map->root_row][1] = "--";
        this->string_map[lft_map->root_row][0] = ".-";
        for(uint i = lft_map->root_row + 1; i < this->root_row; ++i)
            this->string_map[i][0] = std::string("| ");
        delete lft_map;
    }
    this->string_map[this->root_row][0] = ss.str();
    if(rgt_map != nullptr)
    {
        for(uint i = this->root_row + 1; i < rgt_map->root_row + this->root_row + 1; ++i)
            this->string_map[i][0] = std::string("| ");
        this->string_map[this->root_row + rgt_map->root_row + 1][0] = "'-";
        this->string_map[this->root_row + rgt_map->root_row + 1][1] = "--";
        delete rgt_map;
    }
}

template<class T>
std::ostream& operator<<(std::ostream& out, BinTreeMap<T> dm)
{
    return out << std::string(dm);
}
//
//template<class T>
//std::ostream& operator<<(std::ostream& out, const AbstractBinTree<T>& bt)
//{
//    return out << BinTreeMap<T>(&bt);
//}