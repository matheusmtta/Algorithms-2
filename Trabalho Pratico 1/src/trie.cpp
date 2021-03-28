#include "trie.h"

using namespace std;

Trie::Trie(){
	trie_id = 0;
	Node root_node({trie_id++}, "", -1);
	trie.emplace_back(root_node);
}

void Trie::add_compression_tuple(int parent, char ch){
	compression_tuple.emplace_back(parent, ch);
}

bool Trie::add_string(string str, bool is_last){
	int v = 0;
	int last_id = trie[v].id[0];

	for (int i = 0; i < (int)str.size();){
		int j = 0;
		
		bool isPrefix = true;
		while (isPrefix && i < (int)str.size() && j < (int)trie[v].word.size()){
			if (str[i] == trie[v].word[j]){
 				last_id = trie[v].id[j];
				i++, j++;
			}
			else isPrefix = false;
		}

		if (i < (int)str.size() && isPrefix){
			if (trie[v].child.count(str[i])){
				v = trie[v].child[str[i]];
			}
			else if ((int)trie[v].child.size() > 0 || v == 0){
				trie[v].child[str[i]] = trie.size();

				Node tmp_node({trie_id++}, string(1, str[i]), v);

				trie.emplace_back(tmp_node);
				add_compression_tuple(last_id, str[i]);

				return false;
			}
			else{
				trie[v].word += str[i];
				trie[v].id.push_back(trie_id++); 

				add_compression_tuple(last_id, str[i]);

				return false;
			}
		}
		else if (!isPrefix) {
			int len = (int)trie[v].word.size();
			string prefix = trie[v].word.substr(0, j);
			string suffix = trie[v].word.substr(j, len);
		
			vector <int> prefix_ids, suffix_ids;

			for (int k = 0;  k <= j; k++) prefix_ids.push_back(trie[v].id[k]);
			for (int k = j; k < len; k++) suffix_ids.push_back(trie[v].id[k]);

			Node suffix_node(suffix_ids, suffix, v);
			suffix_node.child = trie[v].child;
			trie[v].child.clear();

			trie[v].child[suffix[0]] = trie.size();
			trie.emplace_back(suffix_node);

			trie[v].word = prefix;
			trie[v].id = prefix_ids;

			Node new_node({trie_id++}, string(1, str[i]), v);
			trie[v].child[str[i]] = trie.size();
			trie.emplace_back(new_node);

			add_compression_tuple(last_id, str[i]);

			return false;
		}
	}
	
	char eof = (char)4;
	if (is_last) 
		add_compression_tuple(last_id, eof);

	return true;
}