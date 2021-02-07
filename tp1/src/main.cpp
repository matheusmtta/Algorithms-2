#include <bits/stdc++.h>

#include "includes/trie.h"

using namespace std;

int main(int argc, char const* argv[]){
	//./<programa> -c <arquivo_entrada> [-o <arquivo_saida>]
	//./<programa> -x <arquivo_entrada> [-o <arquivo_saida>]
	if (argc < 4){
	  	cout << "Invalid Input" << endl;
	  	exit(0);
	}

	string input_path, command, garb, output_path;

	stringstream stream_input_path(argv[2]);
	stream_input_path >> input_path;

	stringstream stream_command(argv[1]);
	stream_command >> command;

	stringstream stream_output_path(argv[4]);
	stream_output_path >> output_path;

	if (command == "-c"){
		cout << "File compress running..." << endl;
		compress(input_path, output_path);
		cout << "Compressed file saved in " << output_path << endl;
	}
	else if (command == "-x"){
		cout << "File decompress running..." << endl;
		decompress(input_path, output_path);
		cout << "Decompressed file saved in " << output_path << endl;
	}
	else
		cout << "Undefined command" << endl;

	return 0;
}