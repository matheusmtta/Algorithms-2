#include "trie.h"

using namespace std;

bool compress(string input_path, string output_path){
	Trie trie;

	ifstream infile(input_path);
	ofstream outfile(output_path);

	if (infile.is_open() == false){
		cout << "Input file not found" << endl;
		return false;
	}

	if (outfile.is_open() == false){
		cout << "Output file not found" << endl;
		return false;
	}

	char next_ch;
	string str, chain;
	
	infile.unsetf(std::ios_base::skipws);
	while (infile >> next_ch)
 		str += string(1, next_ch); 

	for (int i = 0; i < (int)str.size(); i++){
		bool is_last = i == (int)str.size() - 1 ? true : false;
		bool isPrefix = trie.add_string(chain + str[i], is_last);
		if (isPrefix)
			chain += str[i];
		else
			chain = "";
	}

	char eof = (char)4;
	for (pair<int, char> tuple : trie.compression_tuple){
		outfile.write((char *)(&tuple.first), 4);
		if (tuple.second != eof)
			outfile.write((char *)(&tuple.second), 1);
	}

	infile.close();
	outfile.close();

	return true;
}

bool decompress(string input_path, string output_path){
	ifstream infile(input_path);
	ofstream outfile(output_path);

	if (infile.is_open() == false){
		cout << "Input file not found" << endl;
		return false;
	}

	if (outfile.is_open() == false){
		cout << "Output file not found" << endl;
		return false;
	}

	string str; char eof = (char)4;

	unordered_map <int, pair <int, char>> decomp_hash;
	decomp_hash[0] = {0, eof};

	string recoveredstr = "";

	int* code = (int*) new int;
    char* ch = (char*) new char;
	infile.unsetf(std::ios_base::skipws);
	while(infile.read((char *)code, 4)){
		string next_string = "";
		if (!infile.read(ch, 1))
			next_string += "";
		else
			next_string += *ch;

		decomp_hash[(int)decomp_hash.size()] = {*code, *ch};

		while (*code != 0){
			next_string += decomp_hash[*code].second;
			*code = decomp_hash[*code].first;
		}
		reverse(next_string.begin(), next_string.end());

		recoveredstr += next_string;
	}

	outfile << recoveredstr;

	delete code;
	delete ch;

	infile.close();
	outfile.close();

	return true;
}