#include <bits/stdc++.h>

#include "includes/file_compressor.h"

using namespace std;

int main(int argc, char const* argv[]){
	if (argc < 3){
	  	cout << "Invalid Input" << endl;
	  	exit(0);
	}

	string input_path, command, garb, output_path;

	stringstream stream_input_path(argv[2]);
	stream_input_path >> input_path;

	stringstream stream_command(argv[1]);
	stream_command >> command;
	
	if (argc > 3){
		stringstream stream_output_path(argv[4]);
		stream_output_path >> output_path;
	}
	else {
		int i = 0;
		bool slice = false;
		while (i < (int)input_path.size()){
			if (input_path[i] == '.'){
				slice = true;
				break;
			}
			i++;
		}
		if (slice)
			output_path = input_path.substr(0, i) + (command == "-c" ? ".z78" : ".txt");
		else 
			cout << "Invalid input file" << endl;
	}

	if (command == "-c"){
		cout << "File compress running..." << endl;
		if(compress(input_path, output_path))
			cout << "Compressed file saved in " << output_path << endl;
		else
			cout << "Compression failed" << endl;
	}
	else if (command == "-x"){
		cout << "File decompress running..." << endl;
		if (decompress(input_path, output_path))
			cout << "Decompressed file saved in " << output_path << endl;
		else
			cout << "Decompression failed" << endl;
	}
	else
		cout << "Undefined command" << endl;

	return 0;
}