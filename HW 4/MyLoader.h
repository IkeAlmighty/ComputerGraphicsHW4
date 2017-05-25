#pragma once
#include <stdio.h>
#include <string>
#include <vector>

class MyLoader
{
public:
	MyLoader() {
		loadedOBJV = std::vector<float>();
		loadedOBJF = std::vector<float>();
	}
	~MyLoader() {}

	void load(char filename[]) {

		FILE* file = fopen(filename, "r");
		if (file == NULL) {
			printf("\n\n\nNULL file, closing");
			exit(-1);
		}
		

		//TODO: rewrite to properly store all data in 
		const int NEWLINE = 31;
		const int SPACE = 32;
		bool vFlag = false;
		char nextChar = NULL;

		//TODO this needs replaced with a dynamic array to avoid exceptions
		//and save memory
		char* currentWord = new char[300];

		int currentWordIndex = 0;
		float nextFloat = 0.0;
		std::vector<float> OBJVertexes = std::vector<float>(10);
		int currentVIndex = 0;
		while ((nextChar = fgetc(file)) != EOF) {
			if (nextChar == 'v') {
				vFlag = true;
			} 
			else if (nextChar == NEWLINE) {
				vFlag = false;
			} 
			/*At each occurance of a space or NEWLINE, if the vFlag is true, parse out the float from the
			currentWord, and reset the current Word.*/
			else if (vFlag &&(nextChar == SPACE || nextChar == NEWLINE)) {

				//create a temp char* of exact size to hand to the strtof function for parsing.
				char* temp = new char[currentWordIndex + 1];
				for (int i = 0; i < currentWordIndex + 1; i++) {
					temp[i] = currentWord[i];
				}

				if ((nextFloat = strtof(temp, NULL)) != 0) {
					if (currentVIndex > OBJVertexes.capacity() - 1) {
						OBJVertexes.reserve(OBJVertexes.capacity() * 2);
						OBJVertexes.resize(OBJVertexes.capacity());
						printf("\nc: %d", OBJVertexes.capacity());
					}
					OBJVertexes.at(currentVIndex) = nextFloat;
					//printf("\nnext: %f", nextFloat);
					currentVIndex++;
				}

				delete[] temp;
				currentWordIndex = 0;
			}

			//add the char to the next index of the currentWord. 
			//(words are divided by spaces and newlines).
			currentWord[currentWordIndex] = nextChar;
			currentWordIndex++;
		}
			
		delete[] currentWord;
		OBJVertexes.resize(currentVIndex);
		loadedOBJV = OBJVertexes;

		//TODO: write code to store fragments:
	}

	float* getVertexes() {
		float* temp = new float[loadedOBJV.size()];
		for (int i = 0; i < loadedOBJV.size(); i++) {
			temp[i] = loadedOBJV.at(i);
		}
		return temp;
	}

	float* getFragments() {
		float* temp = new float[loadedOBJF.size()];
		for (int i = 0; i < loadedOBJF.size(); i++) {
			temp[i] = loadedOBJF.at(i);
		}
		return temp;
	}

	int size() {
		return loadedOBJV.size();
	}

private:
	std::vector<float> loadedOBJV;
	std::vector<float> loadedOBJF;
};



