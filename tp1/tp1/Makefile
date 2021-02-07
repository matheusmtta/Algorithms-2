CC=g++
CFLAGS=-Wall -Wextra -fsanitize=address,undefined -fno-omit-frame-pointer -g
EXEC=./main
LIBS=`pkg-config --cflags`
BIN = bin

$(EXEC): src/main.cpp $(BIN)/trie.o $(BIN)/file_compressor.o
	$(CC) $(CFLAGS) src/main.cpp $(BIN)/trie.o $(BIN)/file_compressor.o $(LIBS) -o $(EXEC)

$(BIN)/trie.o: src/trie.cpp
	$(CC) $(CFLAGS) -c src/trie.cpp $(LIBS) -o $(BIN)/trie.o$ 

$(BIN)/file_compressor.o: src/file_compressor.cpp
	$(CC) $(CFLAGS) -c src/file_compressor.cpp $(LIBS) -o $(BIN)/file_compressor.o$ 

clean:
	rm -rf $(BIN)/trie.o $(BIN)/file_compressor.o main 