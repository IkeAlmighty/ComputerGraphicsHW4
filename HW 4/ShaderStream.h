#pragma once
#include <string>
#include <iostream>
#include <fstream>

class ShaderStream {
public:

	ShaderStream(std::string filepath) {
		std::ifstream in = std::ifstream();
		in.open(filepath);
		if (!in.is_open()) {
			std::cout << "\nFile stream failure: " << filepath;
			exit(-1);
		}

		std::string streamString = "";
		std::string line;
		while (getline(in, line)) {
			streamString.append(line);
			streamString.append("\n");
		}

		stream = new char[streamString.size()];
		for (int i = 0; i < streamString.size(); i++) {
			stream[i] = streamString.at(i);
		}
		_size = streamString.size();

		in.close();
	}

	~ShaderStream() {
		delete stream;
	}

	/*
	returns the entire file as a char[]
	*/
	char* getProg() {
		return stream;
	}

	/*
	returns the number of chars in the stream
	*/
	int size() {
		return _size;
	}

private:
	char* stream;
	int _size;
};