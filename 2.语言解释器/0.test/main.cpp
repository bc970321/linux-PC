#include "testLexer.h"
#include "testParser.h"
#include <cassert>
#include <map>
#include <string>
#include <iostream>

using std::map;
using std::string;
using std::cout;

class testEvaluator {
    map<string, int> memory;
public:
    int run(pANTLR3_BASE_TREE);
};

pANTLR3_BASE_TREE getChild(pANTLR3_BASE_TREE, unsigned);
const char *getText(pANTLR3_BASE_TREE tree);

int main(int argc, char *argv[]) {
    pANTLR3_BASE_TREE input;
    
}







