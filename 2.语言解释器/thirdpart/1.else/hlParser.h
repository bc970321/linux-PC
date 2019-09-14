/** \file
 *  This C header file was generated by $ANTLR version 3.4
 *
 *     -  From the grammar source file : ./hl.g
 *     -                            On : 2019-08-11 19:53:19
 *     -                for the parser : hlParserParser
 *
 * Editing it, at least manually, is not wise.
 *
 * C language generator and runtime by Jim Idle, jimi|hereisanat|idle|dotgoeshere|ws.
 *
 *
 * The parser 
hlParser

has the callable functions (rules) shown below,
 * which will invoke the code for the associated rule in the source grammar
 * assuming that the input stream is pointing to a token/text stream that could begin
 * this rule.
 *
 * For instance if you call the first (topmost) rule in a parser grammar, you will
 * get the results of a full parse, but calling a rule half way through the grammar will
 * allow you to pass part of a full token stream to the parser, such as for syntax checking
 * in editors and so on.
 *
 * The parser entry points are called indirectly (by function pointer to function) via
 * a parser context typedef phlParser, which is returned from a call to hlParserNew().
 *
 * The methods in phlParser are  as follows:
 *
 *  - 
 hlParser_defid_return
      phlParser->defid(phlParser)
 *  - 
 hlParser_expr_return
      phlParser->expr(phlParser)
 *  - 
 hlParser_multExpr_return
      phlParser->multExpr(phlParser)
 *  - 
 hlParser_atom_return
      phlParser->atom(phlParser)
 *  - 
 hlParser_or_expr_return
      phlParser->or_expr(phlParser)
 *  - 
 hlParser_and_expr_return
      phlParser->and_expr(phlParser)
 *  - 
 hlParser_cond_expr_return
      phlParser->cond_expr(phlParser)
 *  - 
 hlParser_if_expr_return
      phlParser->if_expr(phlParser)
 *  - 
 hlParser_print_expr_return
      phlParser->print_expr(phlParser)
 *  - 
 hlParser_stmt_return
      phlParser->stmt(phlParser)
 *  - 
 hlParser_expr_stmt_return
      phlParser->expr_stmt(phlParser)
 *  - 
 hlParser_code_block_return
      phlParser->code_block(phlParser)
 *  - 
 hlParser_block_return
      phlParser->block(phlParser)
 *  - 
 hlParser_prog_return
      phlParser->prog(phlParser)
 *
 * The return type for any particular rule is of course determined by the source
 * grammar file.
 */
// [The "BSD license"]
// Copyright (c) 2005-2009 Jim Idle, Temporal Wave LLC
// http://www.temporal-wave.com
// http://www.linkedin.com/in/jimidle
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
// 1. Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
// 3. The name of the author may not be used to endorse or promote products
//    derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
// IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
// OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
// IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
// NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
// THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef	_hlParser_H
#define _hlParser_H
/* =============================================================================
 * Standard antlr3 C runtime definitions
 */
#include    <antlr3.h>

/* End of standard antlr 3 runtime definitions
 * =============================================================================
 */

#ifdef __cplusplus
extern "C" {
#endif

// Forward declare the context typedef so that we can use it before it is
// properly defined. Delegators and delegates (from import statements) are
// interdependent and their context structures contain pointers to each other
// C only allows such things to be declared if you pre-declare the typedef.
//
typedef struct hlParser_Ctx_struct hlParser, * phlParser;



    #include <assert.h>


#ifdef	ANTLR3_WINDOWS
// Disable: Unreferenced parameter,							- Rules with parameters that are not used
//          constant conditional,							- ANTLR realizes that a prediction is always true (synpred usually)
//          initialized but unused variable					- tree rewrite variables declared but not needed
//          Unreferenced local variable						- lexer rule declares but does not always use _type
//          potentially unitialized variable used			- retval always returned from a rule
//			unreferenced local function has been removed	- susually getTokenNames or freeScope, they can go without warnigns
//
// These are only really displayed at warning level /W4 but that is the code ideal I am aiming at
// and the codegen must generate some of these warnings by necessity, apart from 4100, which is
// usually generated when a parser rule is given a parameter that it does not use. Mostly though
// this is a matter of orthogonality hence I disable that one.
//
#pragma warning( disable : 4100 )
#pragma warning( disable : 4101 )
#pragma warning( disable : 4127 )
#pragma warning( disable : 4189 )
#pragma warning( disable : 4505 )
#pragma warning( disable : 4701 )
#endif
typedef struct hlParser_defid_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    hlParser_defid_return;



typedef struct hlParser_expr_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    hlParser_expr_return;



typedef struct hlParser_multExpr_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    hlParser_multExpr_return;



typedef struct hlParser_atom_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    hlParser_atom_return;



typedef struct hlParser_or_expr_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    hlParser_or_expr_return;



typedef struct hlParser_and_expr_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    hlParser_and_expr_return;



typedef struct hlParser_cond_expr_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    hlParser_cond_expr_return;



typedef struct hlParser_if_expr_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    hlParser_if_expr_return;



typedef struct hlParser_print_expr_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    hlParser_print_expr_return;



typedef struct hlParser_stmt_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    hlParser_stmt_return;



typedef struct hlParser_expr_stmt_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    hlParser_expr_stmt_return;



typedef struct hlParser_code_block_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    hlParser_code_block_return;



typedef struct hlParser_block_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    hlParser_block_return;



typedef struct hlParser_prog_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    hlParser_prog_return;




/** Context tracking structure for 
hlParser

 */
struct hlParser_Ctx_struct
{
    /** Built in ANTLR3 context tracker contains all the generic elements
     *  required for context tracking.
     */
    pANTLR3_PARSER   pParser;

     hlParser_defid_return
     (*defid)	(struct hlParser_Ctx_struct * ctx);

     hlParser_expr_return
     (*expr)	(struct hlParser_Ctx_struct * ctx);

     hlParser_multExpr_return
     (*multExpr)	(struct hlParser_Ctx_struct * ctx);

     hlParser_atom_return
     (*atom)	(struct hlParser_Ctx_struct * ctx);

     hlParser_or_expr_return
     (*or_expr)	(struct hlParser_Ctx_struct * ctx);

     hlParser_and_expr_return
     (*and_expr)	(struct hlParser_Ctx_struct * ctx);

     hlParser_cond_expr_return
     (*cond_expr)	(struct hlParser_Ctx_struct * ctx);

     hlParser_if_expr_return
     (*if_expr)	(struct hlParser_Ctx_struct * ctx);

     hlParser_print_expr_return
     (*print_expr)	(struct hlParser_Ctx_struct * ctx);

     hlParser_stmt_return
     (*stmt)	(struct hlParser_Ctx_struct * ctx);

     hlParser_expr_stmt_return
     (*expr_stmt)	(struct hlParser_Ctx_struct * ctx);

     hlParser_code_block_return
     (*code_block)	(struct hlParser_Ctx_struct * ctx);

     hlParser_block_return
     (*block)	(struct hlParser_Ctx_struct * ctx);

     hlParser_prog_return
     (*prog)	(struct hlParser_Ctx_struct * ctx);
    // Delegated rules

    const char * (*getGrammarFileName)();
    void            (*reset)  (struct hlParser_Ctx_struct * ctx);
    void	    (*free)   (struct hlParser_Ctx_struct * ctx);
/* @headerFile.members() */
pANTLR3_BASE_TREE_ADAPTOR	adaptor;
pANTLR3_VECTOR_FACTORY		vectors;
/* End @headerFile.members() */
};

// Function protoypes for the constructor functions that external translation units
// such as delegators and delegates may wish to call.
//
ANTLR3_API phlParser hlParserNew         (
pANTLR3_COMMON_TOKEN_STREAM
 instream);
ANTLR3_API phlParser hlParserNewSSD      (
pANTLR3_COMMON_TOKEN_STREAM
 instream, pANTLR3_RECOGNIZER_SHARED_STATE state);

/** Symbolic definitions of all the tokens that the 
parser
 will work with.
 * \{
 *
 * Antlr will define EOF, but we can't use that as it it is too common in
 * in C header files and that would be confusing. There is no way to filter this out at the moment
 * so we just undef it here for now. That isn't the value we get back from C recognizers
 * anyway. We are looking for ANTLR3_TOKEN_EOF.
 */
#ifdef	EOF
#undef	EOF
#endif
#ifdef	Tokens
#undef	Tokens
#endif
#define EOF      -1
#define T__27      27
#define T__28      28
#define T__29      29
#define T__30      30
#define T__31      31
#define AND      4
#define ASSIGN      5
#define BLOCK      6
#define DEF      7
#define DOT      8
#define EG      9
#define EL      10
#define EQ      11
#define GE      12
#define GT      13
#define ID      14
#define IF      15
#define INT      16
#define LE      17
#define LITTLE      18
#define MINUS      19
#define NE      20
#define NEWLINE      21
#define OR      22
#define PLUS      23
#define PRINT      24
#define TIMES      25
#define WS      26
#ifdef	EOF
#undef	EOF
#define	EOF	ANTLR3_TOKEN_EOF
#endif

#ifndef TOKENSOURCE
#define TOKENSOURCE(lxr) lxr->pLexer->rec->state->tokSource
#endif

/* End of token definitions for hlParser
 * =============================================================================
 */
/** } */

#ifdef __cplusplus
}
#endif

#endif

/* END - Note:Keep extra line feed to satisfy UNIX systems */
