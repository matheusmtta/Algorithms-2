CC=g++
CFLAGS=-Wall -Wextra -fsanitize=address,undefined -fno-omit-frame-pointer -g
EXEC=./main
LIBS=`pkg-config --cflags --libs gumbo`
BIN = bin

$(EXEC): src/main.cpp $(BIN)/trie.o
	$(CC) $(CFLAGS) src/main.cpp $(BIN)/trie.o $(LIBS) -o $(EXEC)

$(BIN)/trie.o: src/trie.cpp
	$(CC) $(CFLAGS) -c src/trie.cpp $(LIBS) -o $(BIN)/trie.o$ 

clean:
	rm -rf $(BIN)/trie.o main 