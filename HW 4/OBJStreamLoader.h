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
			if (nextType() == "v") {
				vertexes.push_back(nextFloat());
				vertexes.push_back(nextFloat());
				vertexes.push_back(nextFloat());
			}
			else if (nextType() == "f") {
				indices.push_back(nextShort());
				indices.push_back(nextShort());
				indices.push_back(nextShort());
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

	float nextFloat() {
		float vertex;
		in >> vertex;
		return vertex;
	}
	
	short nextShort() {
		short f;
		in >> f;
		return f;
	}
};