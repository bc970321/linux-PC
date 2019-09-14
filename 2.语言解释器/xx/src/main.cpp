/*************************************************************************
	> File Name:    main.cpp
	> Author:       candy7 
	> Mail:         bc970321@163.com
	> Created Time: 2019年08月15日 星期四 11时06分18秒
 ************************************************************************/
#include <iostream>
#include <cassert>

#include "../include/CC_SynTree.h"
#include "../include/CC_ResponChain.h"

#include "../lib/ExprCppTreeLexer.h"
#include "../lib/ExprCppTreeParser.h"



void Analysis_Start(int argc, char **argv) {
    pANTLR3_INPUT_STREAM input;
    pExprCppTreeLexer lex;
    pANTLR3_COMMON_TOKEN_STREAM tokens;
    pExprCppTreeParser parser;

    assert(argc > 1);
    input = antlr3FileStreamNew((pANTLR3_UINT8)argv[1],ANTLR3_ENC_8BIT);
    lex = ExprCppTreeLexerNew(input);
    tokens = antlr3CommonTokenStreamSourceNew(ANTLR3_SIZE_HINT,
                                              TOKENSOURCE(lex));
    parser = ExprCppTreeParserNew(tokens);
    
    ExprCppTreeParser_prog_return r = parser->prog(parser);
    pANTLR3_BASE_TREE tree = r.tree;
    SKL::SynTree mainSTree(tree);
    SKL::ResponChain mainChain;
    mainChain.Accountability(mainSTree);
    
    // ExprTreeEvaluator eval(NULL);
    // int res = eval.run(tree);
    // cout << "Evaluator result: " << res << '\n';
    
    parser->free(parser);
    tokens->free(tokens);
    lex->free(lex);
    input->close(input);
    
    return ;
}

int main (int argc, char* argv[]) {
    Analysis_Start(argc, argv);
    return 0;
}
