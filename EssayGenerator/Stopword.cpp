#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <unordered_map>
#include <cassert>
#include "Stopword.h"

using namespace std;


// Implementation of Stopword.h

const bool Stopword::DEBUG = true;

/***********************************************************
* PUBLIC FUNCTIONS
***********************************************************/

Stopword::Stopword(){}

void Stopword::setStopwords(string stopwordsFile){
	stopwords.clear();
	ifstream fin(stopwordsFile.c_str());
	
	string word;
	while(fin >> word){
		stopwords.insert(stopwords.end(),pair<string,string>(word,word));
	}
	
	// Close the file input
	fin.close();
	
	// Print out the file names if in DEBUG mode.
	if(DEBUG){
		cout << "STOPWORDS showing MAX 5 out of "<< stopwords.size() << endl;
		int count = 0;
		for ( unordered_map<string,string>::const_iterator it = stopwords.begin(); it != stopwords.end() && count < 5; ++it )
		{
			cout << setw(15) << it->first << endl;
			++count;
		}
		cout << endl;
	}	
}

void Stopword::filterWords(vector<string> &words){
	vector<string>::size_type orgSize = words.size();
	int count = 0;
	for(vector<string>::iterator it = words.begin(); it != words.end();)
		// If its equal to the end it was NOT found.
		if(stopwords.find(*it) != stopwords.end()){
			++count;
			if(DEBUG)
				cout << "Stopword has erased the word: " << *it << endl;
			words.erase(it); 
		}
		else
			++it;
	assert(orgSize - count == words.size());
}

bool Stopword::isSet(){
	return stopwords.size() != 0;
}

/***********************************************************
* PRIVATE FUNCTIONS
***********************************************************/

// No private functions

/***********************************************************
* FREE FUNCTIONS
***********************************************************/

// No free functions