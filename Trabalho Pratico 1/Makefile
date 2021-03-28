CC=g++
CFLAGS=-Wall -Wextra -fsanitize=address,undefined -fno-omit-frame-pointer -g
EXEC=./main
LIBS=`pkg-config --cflags`

$(EXEC): main.cpp trie.o file_compressor.o
	$(CC) $(CFLAGS) main.cpp trie.o file_compressor.o $(LIBS) -o $(EXEC)

trie.o: trie.cpp
	$(CC) $(CFLAGS) -c trie.cpp $(LIBS) -o trie.o$ 

file_compressor.o: file_compressor.cpp
	$(CC) $(CFLAGS) -c file_compressor.cpp $(LIBS) -o file_compressor.o$ 

clean:
	rm -rf trie.o file_compressor.o main 