#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include "Essayomat.h"
#include "Sentence.h"

using namespace std;

// Implementation of Essayomat.h

const bool Essayomat::DEBUG = true;

/***********************************************************
* PUBLIC FUNCTIONS
***********************************************************/

Essayomat::Essayomat(){}

/**
* Generates an essay from the given ranked sentences and a max length.
*/
string Essayomat::generateEssay(multimap<double, Sentence> &scoreMap, int maxLength){
	multimap<string, Sentence> sentencesMap;
	int total = 0;
	set<string> filenames;
	
	/*
	For each Sentence, you want to take all the ones with  the same filename, and put them in the same map<int,double>
	*/
	// Get the sentences you will be using for the essay.
	if(DEBUG)
		cout << "Original order of sentences:" << endl;
	for(multimap<double, Sentence>::reverse_iterator rit = scoreMap.rbegin(); rit != scoreMap.rend(); ++rit){
		Sentence sen = rit->second;
		total += sen.getValue().size();
		if(total >= maxLength)
			break;
		else{
			filenames.insert(filenames.end(), sen.getFilename());
			sentencesMap.insert(pair<string,Sentence>(sen.getFilename(), sen));
			if(DEBUG){
				cout << "Score: " << rit->first << " for filename: " << sen.getFilename() << " at position [" << sen.getPosition() << "]" << endl;
			}
		}
	}
	string essay = "";
	if(Essayomat::DEBUG && sentencesMap.size() == 0)
		cout << "Best match sentence >= max length (" << maxLength << ") or no match." << endl;
		
	// Sorts by file name and then by position
	// I hope this is what the teacher wanted?
	if(DEBUG)
		cout << "Order of sentences in essay:" << endl;
	for(set<string>::const_iterator it = filenames.begin(); it != filenames.end(); ++it){
	
		pair<multimap<string, Sentence>::iterator, multimap<string, Sentence>::iterator> ret;
		ret = sentencesMap.equal_range(*it);
		
		map<int, Sentence> positionMap;
		for(multimap<string, Sentence>::iterator sit = ret.first; sit != ret.second; ++sit){
			positionMap.insert(pair<int, Sentence>(sit->second.getPosition(), sit->second));
		}
		for(map<int, Sentence>::const_iterator sortedS = positionMap.begin(); sortedS != positionMap.end(); ++sortedS){
			if(Essayomat::DEBUG){
					cout << "Adding to essay filename: " << sortedS->second.getFilename() << " at position [" << sortedS->second.getPosition() << "]" << endl;
					cout << "    '" << sortedS->second.getValue() << "'" << endl;
			}
			essay += sortedS->second.getValue();
		}
	}
		
	return essay;
}

/***********************************************************
* PRIVATE FUNCTIONS
***********************************************************/

// No private functions

/***********************************************************
* FREE FUNCTIONS
***********************************************************/

// No free functions
