#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <fstream>

class OBJStreamLoader {
public:
	OBJStreamLoader(std::string filepath) {
		std::vector<GLfloat> vertexes = std::vector<GLfloat>();
		std::vector<GLushort> indices = std::vector<GLushort>();
		in = std::ifstream();
		in.open(filepath);
		if (!in.is_open()) {
			std::cout << "\nCould not open file: " << filepath;;
			exit(-1);
		}

		std::string line;
		while(getline(in, line)) {
			std::string next = nextType();
			if (next == "v") {
				vertexes.push_back(nextFloat(line));
				vertexes.push_back(nextFloat(line));
				vertexes.push_back(nextFloat(line));
			}
			
			if (next == "f") {  
				int i0 = nextInt(line);
				int i1 = nextInt(line);
				int i2 = nextInt(line);

				std::cout << i0 << "\n";
				std::cout << i1 << "\n";
				std::cout << i2 << "\n";

				indices.push_back(i0);
				indices.push_back(i1);
				indices.push_back(i2);
			}
		}

		floatVertexes = new GLfloat[vertexes.size()];
		for (int i = 0; i < vertexes.size(); i++) {
			floatVertexes[i] = vertexes.at(i);
		}
		sizev = vertexes.size();

		shortIndices = new GLushort[indices.size()];
		for (int i = 0; i < indices.size(); i++) {
			shortIndices[i] = indices[i];
		}
		sizei = indices.size();
	}

	GLfloat* getVertexes() {
		return floatVertexes;
	}

	GLushort* getIndices() {
		return shortIndices;
	}

	int vertexCount() {
		return sizev;
	}

	int indexCount() {
		return sizei;
	}

private:
	std::ifstream in;
	GLfloat* floatVertexes;
	GLushort* shortIndices;

	int sizev;
	int sizei;

	std::string nextType() {
		std::string type;
		in >> type;
		return type;
	}

	float nextFloat(std::string line) {
		float vertex;
		in >> vertex;
		return vertex;
	}
	
	int nextInt(std::string line) {
		std::string* parsed = split(line, '/');
		line = "";
		for (int i = 0; i < sizeof(parsed); i++) {
			if (i > 0) {
				line += "/" + parsed[i];
			}
		}

		return std::stoi(parsed[0]);
	}

	std::string* split(std::string word, char delim) {
		int splitCount = 0;
		for (int i = 0; i < word.length(); i++) {
			if (word.at(i) == delim) {
				splitCount++;
			}
		}

		std::string* splitString = new std::string[splitCount];
		std::string wordSoFar = "";
		splitCount = 0;
		for (int i = 0; i < word.length(); i++) {
			if (word.at(i) == delim) {
				splitString[splitCount] = wordSoFar;
				splitCount++;
			}
			else {
				wordSoFar += word.at(i);
			}
		}

		return splitString;
	}
};