/*************************************************************************
	> File Name:    CC_SynTree.cpp
	> Author:       candy7 
	> Mail:         bc970321@163.com
	> Created Time: 2019年08月15日 星期四 11时04分55秒
 ************************************************************************/
#include "CC_SynTree.h"

SKL::SynTree SKL::SynTree::getChild (unsigned childNum) {
    assert(childNum < this->tree->getChildCount(this->tree));
    SynTree _tempST((pANTLR3_BASE_TREE)this->tree->getChild(this->tree, childNum));
    return _tempST;
}

const char* SKL::SynTree::getText () {
    return ((const char*)this->tree->getText(this->tree)->chars);
}

int SKL::SynTree::getChildNum () {
    return this->tree->getChildCount(this->tree);
}

int SKL::SynTree::getTokType () {
    return this->tok->type;
}

bool SKL::SynTree::tokEmpty() {
    return (this->tok ? false : true);
}

