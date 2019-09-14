/*************************************************************************
	> File Name:    CC_ResponChain.cpp
	> Author:       candy7 
	> Mail:         bc970321@163.com
	> Created Time: 2019年08月15日 星期四 11时04分14秒
 ************************************************************************/
#include <iostream>

#include "CC_ResponChain.h"


SKL::ResponChain::ResponChain () {
    this->headMaster = new OperaMaster(
        new ScopeMaster(
            new VariableMaster(
                new CirculateMaster(nullptr)
            )
        )
    );
    this->store = new VarStore(nullptr);
}

SKL::Types SKL::ResponChain::Accountability (SKL::SynTree& STree) {
    Master *run = this->headMaster;
    while (run && !run->IsMyRespon(STree)) {
        run = run->getNextMaster();
    }
    if (!run) throw runtime_error("No Master Handle");
    return run->Parsing(STree);
}

SKL::Types SKL::OperaMaster::Parsing (SynTree& STree) {
    std::cout << "SKL::Types& SKL::OperaMaster::Parsing (SynTree& STree)" << std::endl;
    Types _temp;
    return _temp;
}

SKL::OperaMaster::OperaMaster (Master* Initnext) {
    this->nextMaster = Initnext;
}

SKL::Master* SKL::OperaMaster::getNextMaster () {
    return this->nextMaster;
}

bool SKL::OperaMaster::IsMyRespon (SynTree& STree) {
    if (!STree.tokEmpty()) {
        switch (STree.getTokType()) {
            case PLUS:
            case MINUS:
            case ASSIGN: 
            case MOD:
            case TIMES:
            
            /* compare  */
            case NE:
            case EQ:
            case GE: //大于等于
            case GT: //大于
            case LE: //小于等于
            case LITTLE://小于
            case OR:
            case AND: return true;
        }
    }
    return false;
}

SKL::Types SKL::ScopeMaster::Parsing (SynTree& STree) {
    std::cout << "SKL::Types SKL::ScopeMaster::Parsing (SynTree& STree)" << std::endl;
    Types _temp;
    return _temp;
}

SKL::ScopeMaster::ScopeMaster (Master* Initnext) {
    this->nextMaster = Initnext;
}

SKL::Master* SKL::ScopeMaster::getNextMaster () {
    return this->nextMaster;
}

bool SKL::ScopeMaster::IsMyRespon (SynTree& STree) {
    if (!STree.tokEmpty()) {
        switch (STree.getTokType()) {
            case BLOCK:
            case DEF:
            case IF: return true;
        }
    }
    return false;
}

SKL::Types SKL::VariableMaster::Parsing (SynTree& STree) {
    std::cout << "SKL::Types SKL::VariableMaster::Parsing (SynTree& STree)" << std::endl;
    Types _temp;
    return _temp;
}

SKL::VariableMaster::VariableMaster (Master* Initnext) {
    this->nextMaster = Initnext;
}

SKL::Master* SKL::VariableMaster::getNextMaster () {
    return this->nextMaster;
}

bool SKL::VariableMaster::IsMyRespon (SynTree& STree) {
    if (!STree.tokEmpty()) {
        switch (STree.getTokType()) {
            case INT:
            case ID:
            case PRINT: return true;
        }
    }
    return false;
}

SKL::Types SKL::CirculateMaster::Parsing (SynTree& STree) {
    std::cout << "SKL::Types SKL::CirculateMaster::Parsing (SynTree& STree)" << std::endl;
    Types _temp;
    return _temp;
}

SKL::CirculateMaster::CirculateMaster (Master* Initnext) {
    this->nextMaster = Initnext;
}

SKL::Master* SKL::CirculateMaster::getNextMaster () {
    return this->nextMaster;
}

bool SKL::CirculateMaster::IsMyRespon (SynTree& STree) {
    if (!STree.tokEmpty()) {
        switch (STree.getTokType()) {
            case FOR: return true;
        }
    }
    return false;
}
