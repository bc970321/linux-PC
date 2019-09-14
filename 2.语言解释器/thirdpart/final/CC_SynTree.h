/*************************************************************************
	> File Name:    CC_SynTree.h
	> Author:       candy7 
	> Mail:         bc970321@163.com
	> Created Time: 2019年08月15日 星期四 10时59分58秒
 ************************************************************************/

#ifndef _CC_SYNTREE_H
#define _CC_SYNTREE_H

#include "../ExprCppTreeLexer.h"
#include "../ExprCppTreeParser.h"

namespace SKL {
    class SynTree {
    private : 
        pANTLR3_BASE_TREE tree;
        pANTLR3_COMMON_TOKEN tok;
    public : 
        SynTree (pANTLR3_BASE_TREE new_tree) :  
            tree (new_tree) 
        {
            tok = this->tree->getToken(this->tree);
        }
        
        SynTree getChild (unsigned childNum);
        const char* getText();
        int getChildNum();
        int getTokType();
        bool tokEmpty();
    };
}

#endif
