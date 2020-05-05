//
// Created by 佘崧林 on 2020/1/22.
//

#ifndef KEYMININGALGORITHM_PRODUCTTREE_H
#define KEYMININGALGORITHM_PRODUCTTREE_H

#include <gmpxx.h>
#include <vector>

#include "../BinTree/AbstractBinTree.h"

class ProductTree : public AbstractBinTree<mpz_class>{
public:
    explicit ProductTree(const std::vector<mpz_class>& leafList);

    ProductTree &operator=(const AbstractBinTree<mpz_class> &copy);
};

std::ostream& operator<<(std::ostream& out, const ProductTree& bt);

#endif //KEYMININGALGORITHM_PRODUCTTREE_H
