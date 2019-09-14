grammar hl;

options {
    language = C;
    output = AST;
    ASTLabelType=pANTLR3_BASE_TREE;
}

@header {
    #include <assert.h>
}

// The suffix '^' means make it a root.
// The suffix '!' means ignore it.

defid
    : DEF! ID (','! ID)* ';'!
    ;

expr: multExpr ((PLUS^ | MINUS^) multExpr)*
    ;

multExpr
    : atom (TIMES^ atom)*
    ;

atom: INT
    | ID
    | '('! expr ')'!
    ;

or_expr: and_expr (OR^ and_expr)*;
and_expr: cond_expr (AND^ cond_expr)*;
cond_expr: expr ((EQ^ | NE^ | LITTLE^ | GT^ | LE^ | EL^ | GE^ | EG^) expr)*;

if_expr: IF^ '('! or_expr ')'! expr_stmt;
print_expr: PRINT^ or_expr ';'! ;

for_expr: FOR^ '('! init_expr ';'! condition_expr ';'! for_do_expr ')'! stmt;
while_expr: WHILE^ '('! condition_expr ')'! stmt 
    | Do '{' expr_stmt '}' WHILE '(' condition_expr ')' ';' -> ^(DOWHILE condition_expr expr_stmt);

init_expr: defid -> ^(DEF defid) 
    |ID ASSIGN expr_stmt -> ^(ASSIGN ID expr_stmt);

for_do_expr: ID ASSIGN expr_stmt -> ^(ASSIGN ID expr_stmt);

condition_expr: and_expr(OR^ and_expr)*;


stmt: expr_stmt
    | NEWLINE ->   // ignore
    ;

expr_stmt: 
      or_expr ';' NEWLINE -> or_expr // tree rewrite syntax
    | defid NEWLINE -> ^(DEF defid)
    | ID ASSIGN expr ';' NEWLINE -> ^(ASSIGN ID expr) // tree notation
    | if_expr
    | block
    | print_expr
    ;

code_block:
    '{'! (stmt)* '}'!
    ;

block:
    code_block -> ^(BLOCK code_block)
    ;

prog
    : (block {
            pANTLR3_STRING s = $block.tree->toStringTree($block.tree);
            assert(s->chars);
            printf("tree \%s\n", s->chars);
    })+
    ;

PRINT: 'print';
EQ : '==';
NE : '!=';
LITTLE : '<';
GT : '>';
LE : '<=';
EL : '=<';
GE : '>=';
EG : '=>';
OR : '||';
AND: '&&';
IF : 'if';
WHILE: 'while';
FOR: 'for';
DO : 'do';
DOWHILE : 'dowhile';
PLUS: '+';
MINUS: '-';
TIMES: '*';
DOT : ',';
ASSIGN: '=';
BLOCK: '{}';
DEF: 'd' 'e' 'f';
ID: ('a'..'z'|'A'..'Z'|'_') ('a'..'z'|'0'..'9'|'A'..'Z'|'_')*;
INT: '~'? '0'..'9'+ ;
NEWLINE: '\r'? '\n' ;
WS : (' '|'\t')+ {$channel = HIDDEN;};
