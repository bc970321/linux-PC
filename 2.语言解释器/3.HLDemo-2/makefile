
.PHONY: clean

TARGET='./bin/test'

all: 
	cd ./thirdpart && make
	g++ -g -Wall *.cpp ./src/*.cc ./thirdpart/*.c ./thirdpart/libs/libantlr3c.a -o $(TARGET) -I./include -I ./thirdpart/include -I ./thirdpart/
	$(TARGET) ./input

clean:
	rm -rf $(TARGET)
