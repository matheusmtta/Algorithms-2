#ifndef COMPRESSED_TRIE
#define COMPRESSED_TRIE

#include <bits/stdc++.h>

using namespace std;

class Trie{
	public:
		struct Node {
			vector <int> id;
			string word;
			int parent;

			unordered_map <char, int> child;

			Node(vector <int> id, string word, int parent) : id(id), word(word), parent(parent) {

			};
		};

		int trie_id;

		vector <Node> trie;
		vector <pair<int, char>> compression_tuple;

		Trie();

		bool add_string(string str, bool is_last);
		void search(string str);

		void add_compression_tuple(int parent, char ch);
};

#endif