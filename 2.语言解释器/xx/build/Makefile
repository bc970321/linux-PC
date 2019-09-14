CC 		= g++
CFLAGS 	= -g -I include 
VPATH 	= ../:../src/:../include/:../lib/

RELY = \
	main.o \
	CC_SynTree.o \
	CC_Types.o \
	CC_VarStore.o \
	CC_ResponChain.o \
	ExprCppTreeLexer.o \
	ExprCppTreeParser.o \
	$(shell ls ../lib/1.Need_file/*.o 2> /dev/null | tr -s '\n' ' ') 

kscc : ${RELY}
	@echo "[CC] [Link] *.o"
	@${CC} ${CFLAGS} -Wall ${RELY} -o kscc

main.o : main.cpp
	@echo "[CC] [Build] main.cpp"
	@${CC} -c ${CFLAGS} -Wall $<

CC_ResponChain.o : CC_ResponChain.cpp CC_ResponChain.h
	@echo "[CC] [Build] CC_ResponChain.cpp"
	@${CC} -c ${CFLAGS} -Wall $< 

CC_SynTree.o : CC_SynTree.cpp CC_SynTree.h
	@echo "[CC] [Build] CC_SynTree.cpp"
	@${CC} -c ${CFLAGS} -Wall $< 

CC_Types.o : CC_Types.cpp CC_Types.h
	@echo "[CC] [Build] CC_Types.cpp"
	@${CC} -c ${CFLAGS} -Wall $<

CC_VarStore.o : CC_VarStore.cpp CC_VarStore.h
	@echo "[CC] [Build] CC_VarStore.cpp"
	@${CC} -c ${CFLAGS} -Wall $<

ExprCppTreeLexer.o : ExprCppTreeLexer.c ExprCppTreeLexer.h
	@echo "[CC] [Build] ExprCppTreeLexer.c"
	@${CC} -c ${CFLAGS} $<


ExprCppTreeParser.o : ExprCppTreeParser.c ExprCppTreeParser.h
	@echo "[CC] [Build] ExprCppTreeParser.c"
	@${CC} -c ${CFLAGS} $<


.PHONY : genTree install remove clean 

genTree : 
	@echo "[JAVA] Build Syntax Tree"
	@java -jar ../lib/1.Need_file/1.Antlr_3.4/antlr-3.4-complete.jar ../lib/ExprCppTree.g

install : 
	@echo "[Install] Install 'kscc' to system"
	@sudo cp kscc /usr/bin/

uninstall : 
	@echo "[Uninstall] Uninstall 'kscc' from system"
	@sudo rm -rf /usr/bin/kscc

clean : 
	@echo "[Clean] clean 'kscc' and '*.o'"
	@rm -rf kscc *.o
