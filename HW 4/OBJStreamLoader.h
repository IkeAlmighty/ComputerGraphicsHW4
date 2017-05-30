#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <thread>

class OBJStreamLoader {
public:
	OBJStreamLoader(std::string filepath) {
		std::vector<GLfloat> vertexes = std::vector<GLfloat>();
		std::vector<GLushort> indices = std::vector<GLushort>();
		in = std::ifstream();
		in.open(filepath);
		if (!in.is_open()) {
			std::cout << "\nCould not open file: " << filepath;
			exit(-1);
		}

		std::string next;
		while(in.good()) {
			try {
				next = nextWord();
				//std::cout << "word: " << next << "\n";
				//std::this_thread::sleep_for(std::chrono::milliseconds(1));
				if (next == "v") {
					vertexes.push_back(nextFloat());
					vertexes.push_back(nextFloat());
					vertexes.push_back(nextFloat());
				}

				if (next == "f") {
					//assumes sets of threes for now.
					indices.push_back(nextFaceIndex());
					nextFaceIndex();
					nextFaceIndex();

					indices.push_back(nextFaceIndex());
					nextFaceIndex();
					nextFaceIndex();

					indices.push_back(nextFaceIndex());
					nextFaceIndex();
					nextFaceIndex();
				}
			}
			catch (std::exception& e) {
				std::cout << e.what() << "\n";
			}

		}

		//copy the floats into the returnable GLfloat[]
		floatVertices = new GLfloat[vertexes.size()];
		for (int i = 0; i < vertexes.size(); i++) {
			floatVertices[i] = vertexes.at(i);
		}
		sizev = vertexes.size();

		//copy the indexes into the returnable GLushort
		shortIndices = new GLushort[indices.size()];
		for (int i = 0; i < indices.size(); i++) {
			shortIndices[i] = indices[i];
		}
		sizei = indices.size();
	}

	GLfloat* getVertices() {
		return floatVertices;
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
	GLfloat* floatVertices;
	GLushort* shortIndices;

	int sizev;
	int sizei;

	//as far as I can tell, the bitwise operation of storing a string
	//from a file stops at whitespace (tabs, newlines, spaces)
	std::string nextWord() {
		std::string type;	
		in >> std::skipws >> type;//had to use skipws after using noskipws in another nextFaceValue, no idea why
		return type;
	}

	float nextFloat() {
		float vertex;
		in >> vertex;
		return vertex;
	}

	int nextFaceIndex() {
		int idx;
		
		//init
		char thisC;
		in >> thisC;
		//std::cout << "\t\tfirstC: " << thisC;

		//get first digit
		while (!isdigit(thisC)) {
			in >> thisC;
		}

		//convert first digit (thisC) to number.
		idx = thisC - '0'; //jeez c is clever

		//add additional digits
		in >> std::noskipws >> thisC;
		//std::cout << ", second is " << thisC << "\n";
		while (isdigit(thisC) && in.good()) {
			in >> thisC;
			idx = idx*10 + (thisC - '0');

		}
		
		//std::cout << "\tnextNum: " << idx << "\n";
		return idx;
	}
};