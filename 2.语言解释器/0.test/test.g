grammar test;

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

expr: multExpr ((PLUS^ | MINUS^) multExpr)*
    ;

PLUS: '+';
MINUS: '-';

multExpr
    : atom (TIMES^ atom)*
    ;

TIMES: '*';

atom: INT
    | ID (ASSIGN^ expr)?
    | '('! expr ')'!
    ;

ASSIGN: '=';

stmt: expr (DOT^ expr)* NEWLINE! // tree rewrite syntax
    | NEWLINE -> // ignore
    | block
    ;

DOT : ',';

block: '{' block_body '}' NEWLINE -> ^(BLOCK block_body);

block_body: (stmt)*;

BLOCK: '.';

prog
    : (block 
       {
            #ifdef DEBUG
            pANTLR3_STRING s = $block.tree->toStringTree($block.tree);
            assert(s->chars);
            printf("haizei tree \%s\n", s->chars);
            #endif
       }
      )+
    ;

ID: ('a'..'z'|'A'..'Z')+ ;
INT: '~'? '0'..'9'+ ;
NEWLINE: '\r'? '\n' ;
WS : (' '|'\t')+ {$channel = HIDDEN;};
