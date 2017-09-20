/*
 * File: RandomWriter.cpp
 * ----------------------
 * Name: Chandan Hegde
 */

#include <fstream>
#include <iostream>
#include <string>
#include "console.h"
#include "map.h"
#include "random.h"
#include "strlib.h"
#include "vector.h"

#include "simpio.h"
#include "filelib.h"
#include "foreach.h"
using namespace std;

int getSeedLength();
string getMostFrequentSeed(Map<string, Vector<char> > & model);

Map<string, Vector<char> > processFile(ifstream & stream, string filename, int seedLength);
void outputCharacters(Map<string, Vector<char> > & model);
Map<string, int> getSeedFrequencies(Map<string, Vector<char> > & model);

int main() {
	ifstream infile;
	string filename = promptUserForFile(infile, "Enter file to build random writer from: ");
	int seedLength = getSeedLength();

	cout << "Processing file ..." << endl;
	Map<string, Vector<char> > model = processFile(infile, filename, seedLength);
	outputCharacters(model);
	infile.close();
    return 0;
}

int getSeedLength(){
	int seedLength = 0;
	while(true){
		seedLength = getInteger("Enter a seed length: ");
		if(seedLength > 0 && seedLength <= 10) return seedLength;
		cout << "Seed length must be between 0 and 10. " << endl;
	}
}

Map<string, Vector<char> > processFile(ifstream & stream, string filename, int seedLength){
	Map<string, Vector<char> > seedMap;
	
	string text = "";
	char ch;
	while(stream.get(ch)){
		text += ch;
	}

	for(size_t i = 0; i < text.length() - seedLength; i++){
		Vector<char> followingCharacters;
		string seed = text.substr(i, seedLength);
		char followingChar = text[i + seedLength];
		if(seedMap.containsKey(seed)){
			Vector<char> v = seedMap.get(seed);
			v.add(followingChar);
			seedMap[seed] = v;
		}
		else{
		followingCharacters.add(followingChar);
		seedMap.put(seed, followingCharacters);
		}
	}
	return seedMap;
}

void outputCharacters(Map<string, Vector<char> > & model){
	string currentSeed = getMostFrequentSeed(model); //Initial seed
	cout << currentSeed;
	int charsOutputted = currentSeed.length();
	while(true){
		if(!(model.containsKey(currentSeed)) || charsOutputted >= 2000) break;
		Vector<char> charVec = model.get(currentSeed);
		char nextChar = charVec.get(randomInteger(0, charVec.size() - 1));

		cout << nextChar;
		charsOutputted += 1;

		currentSeed = currentSeed.substr(1) + nextChar;

	}
	cout << endl << "Processed " << charsOutputted << " characters." << endl;
}


string getMostFrequentSeed(Map<string, Vector<char> > & model){
	Map<string, int> frequencies;
	int largestFrequency = 0;
	string mostFrequentSeed;

	foreach(string seed in model){
		frequencies[seed]+= model[seed].size();
		if(frequencies[seed] > largestFrequency){
			largestFrequency = frequencies[seed];
			mostFrequentSeed = seed;
		}
		
	}
	return mostFrequentSeed;
}








