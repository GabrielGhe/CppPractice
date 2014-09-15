#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <sstream>
#include <numeric>
#include <cmath>
#include <set>
#include <stdio.h>
#include <iomanip>
#include <ctype.h>
#include <cassert>
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>
#include "Library.h"
#include "Stopword.h"
#include "Document.h"
#include "SentenceSplitter.h"

using namespace std;

// Implementation of Library.h

const bool Library::DEBUG = false;

/***********************************************************
* PUBLIC FUNCTIONS
***********************************************************/

Library::Library(bool useSentences) : useSentences(useSentences){
	if(DEBUG){
		string s = useSentences ? "We are using sentences for this library." : "Not using sentences for this library.";
		cout << s << endl;
	}
}

Library::Library(bool useSentences, string stopwordsFile) : useSentences(useSentences){
	stopword.setStopwords(stopwordsFile);
	if(DEBUG){
		string s = useSentences ? "We are using sentences for this library." : "Not using sentences for this library.";
		cout << s << endl;
	}
}

/**
* Populates the Library with the files contained as a list within the input file.
*/
void Library::populate(string filenameOfList){
	resetVariables();
	set<string> setWords;
	// Save all file names to a the map, and create a document for each.
	// Open the file that was input.
	ifstream fin(filenameOfList.c_str());
	
	string filename;
	while(fin >> filename){
		Document d(filename); 
		map.insert(pair<string, Document>(filename, d));
	}
	
	// Close the file input
	fin.close();
	
	// Print out the file names if in DEBUG mode.
	if(DEBUG){
		cout << "Map contains:" << endl;
		for ( unordered_map<string,Document>::const_iterator it = map.begin(); it != map.end(); ++it )
			cout << setw(15) << it->first << endl;
		cout << endl;
	}
	
	// Go through each file, building up the words vector.
	for ( unordered_map<string,Document>::iterator it = map.begin(); it != map.end(); ++it ){
		filename = it->first;	
		// Open the current file
		ifstream fin2(filename);
		string word;
		vector<string> fileWords;
		while(fin2 >> word){
			// Make the word lower case
			toLowerCase(word);
			// Remove punctuation
			removePunctuation(word);
			
			if(word.size() != 1 || hasAlphaNumChar(word)){
				set<string>::size_type orgSize = setWords.size();
				setWords.insert(word);
				if(DEBUG && !setWords.size() == orgSize)
					cout << "Words vector already contained '" << word << "'" << ". Not added" << endl;
			}
			fileWords.push_back(word);
		}
		// Print out the words in a file.
		if(DEBUG){
			cout << "Words in " << filename << endl;
			for(vector<string>::const_iterator it = fileWords.begin(); it != fileWords.end(); ++it)
				cout << "   '" << *it << "'" << endl;
		}
		// Close the file input
		fin2.close();
	}

	// Move the words from a SET to a VECTOR
	//cout << "WORDS SET:";
	for(set<string>::iterator it = setWords.begin(); it != setWords.end(); ++it){
		//cout << " '" << *it << "'";
		words.push_back(*it);
	}
	cout << endl;
		
	// Use the Stopword obj on Words vector
	if(stopword.isSet()){
		if(DEBUG)
			cout << "Using stopword on Words vector." << endl;
		stopword.filterWords(words);
	}
	else{
		if(DEBUG)
			cout << "Not using stopword on Words vector." << endl;
	}
	
	// Prints out the WORDS vector
	if(DEBUG)
	{
		cout << "Words vector:" << endl;
		for(vector<string>::const_iterator it = words.begin(); it != words.end(); ++it){
			cout << (it - words.begin()) << " : '" << *it << "'" << endl;
		}
	}

	// Set numOfDocsWithWord to #WORDS of zeros
	for(vector<string>::size_type i = 0; i != words.size(); ++i)
		numDocsWithWord.push_back(0);
	
	// Go through each file, building up the count vectors (contained in the sentences, in the Document).
	// If useSentences option is used for the Library, the Document will contain multiple sentences,
	// otherwise it will only contain one.
	for ( unordered_map<string,Document>::iterator it = map.begin(); it != map.end(); ++it ){
		filename = it->first;
		Document document = it->second;
		
		vector<string> wordsFromFile;
		
		// Open the current file
		ifstream fin2(filename);
		string word;
		
		while(fin2 >> word){
			wordsFromFile.push_back(word);		
		} // end while file input
		
		// Close the file input
		fin2.close();
		
		if(useSentences){
			// Multiple Sentence objs will be needed, inside one Document obj.
			string sentence = ""; 
			for(vector<string>::iterator wIt = wordsFromFile.begin(); wIt != wordsFromFile.end(); ++wIt)
				sentence += *wIt + " ";
			// Use SentenceSplitter class to seperate all the sentences.
			SentenceSplitter sentenceSplitter;
			vector<string> allSentences = sentenceSplitter.sentenceSplit(sentence);
			
			for(vector<string>::iterator sIt = allSentences.begin(); sIt != allSentences.end(); ++sIt){
				vector<string> sentenceWords;
				// Splits by spaces (i.e words).
				stringstream s(*sIt);
				while(!s.eof()) {
					string tmp;
					s >> tmp;
					
					sentenceWords.push_back(tmp);
				}
				processSentence(document, sentenceWords);
			}
		}
		else{
			// We are not using sentences, therefore only one Sentence obj.
			processSentence(document, wordsFromFile);
		}
		
		// Make this Document increment the counts of numDocsWithWord if needed
		document.addCountsToTotal(numDocsWithWord);
		it->second = document;
		
		if(DEBUG){
			cout << "Calculated counts for: " << document.getFilename() << endl;
			cout << "Number of sentences: " << document.size() << endl;
		}
	}
	// Print out the counts, including numDocsWithWord
	/* // FOR BIG INPUT THIS TAKES TOO LONG
	if(DEBUG){
		cout << "*COUNTS*" << endl;
		for ( auto it = map.begin(); it != map.end(); ++it ){
			cout << "For file: " << it->first << endl;
			it->second.printCounts();
		}
		cout << endl;
		
		cout << "COUNTS: NUM OF DOCUMENTS WITH WORDS:" << endl;
		for ( vector<int>::const_iterator cit = numDocsWithWord.begin(); cit != numDocsWithWord.end(); ++cit )
			cout << "   " << *cit << endl;
	}
	*/
	
	// Needed when using WEIGHT formula that uses Sentence counts instead of Document counts
	int totalNumSentences = 0;
	// Calculate total number of sentences
	for(unordered_map<string, Document>::iterator it = map.begin(); it != map.end(); ++it){
		totalNumSentences += it->second.size();
	}
	
	// Compute the weight vectors of each sentence in each document.
	for(unordered_map<string, Document>::iterator it = map.begin(); it != map.end(); ++it){
		//it->second.computeWeights(numDocsWithWord, map.size());
		it->second.computeWeights(numDocsWithWord, totalNumSentences);
	}
	
}

multimap<double, Sentence> Library::processQuery(string query){
	// Query for key words.
	vector<string> keywords;
	string input = query;
	toLowerCase(input);
	
	// Splits the input by words.
	stringstream s(input);
	while(!s.eof()) {
		string tmp;
		s >> tmp;
		removePunctuation(tmp);
		keywords.push_back(tmp);
	}
	
	/* // TAKES LONG FOR BIG INPUT
	if(DEBUG){
		for(vector<string>::const_iterator it = keywords.begin(); it != keywords.end(); ++it)
			cout << *it << "*";
		cout << endl;
	}
	*/
	// Go through key words and create count vector for query.
	vector<int> keywordsCounts;
	int count = 0;
	for(vector<string>::const_iterator it = words.begin(); it != words.end(); ++it, ++count)
	{
		bool found = false;
		for(vector<string>::const_iterator key = keywords.begin(); key != keywords.end(); ++key){
			if(*key == *it)
			{
				found = true;
				// If found for the first time
				if(count >= keywordsCounts.size())
					keywordsCounts.push_back(1);
				else // Found before
					keywordsCounts[count] += 1;
			}
		}
		// If not found then we add a 0 to the counts for keywords.
		if(!found)
			keywordsCounts.push_back(0);
	}
	
	/* // TAKES TOO LONG FOR BIG INPUT
	if(DEBUG){
		for(vector<int>::const_iterator it = keywordsCounts.begin(); it != keywordsCounts.end(); ++it)
			cout << *it << endl;
	}
	*/
	
	multimap<double, Sentence> scoreMap;
	
	// Go through each file count vector and find score with query.
	for ( unordered_map<string,Document>::iterator mapit = map.begin(); mapit != map.end(); ++mapit ){
		// Calculates the score for each Sentence in a Document
		for(int sentenceInd = 0; sentenceInd != mapit->second.size(); ++sentenceInd){
			double score;
			double topEquation = 0.0;
			Sentence sentence = (mapit->second)[sentenceInd];
			double bottomEquation;
				// We use weights here
				vector<double> sentenceCounts = sentence.getWeights();
				topEquation = inner_product(sentenceCounts.begin(), sentenceCounts.end(),keywordsCounts.begin(), 0.0);
				bottomEquation = findMagnitude(sentenceCounts) * findMagnitude(keywordsCounts);				
			if(bottomEquation == 0)
				bottomEquation = 1;
			score = topEquation / bottomEquation;
			
			scoreMap.insert(scoreMap.end(), pair<double, Sentence>(score, sentence));
		}
	}
	
	return scoreMap;
}

/***********************************************************
* PRIVATE FUNCTIONS
***********************************************************/

/*
* Private function to reset global vars.
*/
void Library::resetVariables(){
	map.clear();
	words.clear();
	numDocsWithWord.clear();
}

/*
* Returns the number of documents (i.e size of map)
*/
int Library::getNumOfDocuments(){
	return (int)map.size();
}

/*
* Processes one sentence and adds it to the document
*/
void Library::processSentence(Document & document, vector<string> & sentenceWords){
	vector<int> counts;
	string sentence = "";
	string word;
	// Add extra ZEROs for all words.
	for(vector<int>::size_type i = 0; i < words.size(); ++i)
		counts.insert(counts.end(),0);
	for(vector<string>::iterator wIt = sentenceWords.begin(); wIt != sentenceWords.end(); ++wIt){
		word = *wIt;
		sentence += word + " ";
		toLowerCase(word);
		removePunctuation(word);	
		int index = binarySearch(words, word);
		// index could be -1 when stopwords was used.
		if(index != -1)
			counts[index] += 1;		
	}
	
	// EMPTY Weights (calculated later)
	vector<double> weights;
	
	/*
	if(DEBUG)
		cout << "Processing sent: " << sentence << endl;
	*/
	
	// Add the SINGLE sentence to Document
	document.addSentence(sentence, counts, weights);
}
/***********************************************************
* FREE FUNCTIONS
***********************************************************/

/**
* Changes a string's characters to lower case letters.
*/
void toLowerCase(string &str){
	const int length = str.length();
	for(int i=0; i < length; ++i)
	{
		str[i] = tolower(str[i]);
	}
}

/**
* Finds the magnitude of a vector of integers.
* 
* param: vector<int>
* return: double
*/
double findMagnitude(const vector<int> &values){
	double mag = 0;
	for(vector<int>::const_iterator it = values.begin(); it != values.end(); ++it){
		mag += ((*it) * (*it));
	}
	return sqrt(mag);
}
/**
* Finds the magnitude of a vector of doubles.
* 
* param: vector<int>
* return: double
*/
double findMagnitude(const vector<double> &values){
	double mag = 0;
	for(vector<double>::const_iterator it = values.begin(); it != values.end(); ++it){
		mag += ((*it) * (*it));
	}
	return sqrt(mag);
}

/**
* Binary search through a vector<string>
* param: vector<string>
* param: string value
* return int
*/
int binarySearch(const vector<string> &v, const string value){
	int low = 0;
	int high = v.size();
	while( low <= high ){
		int mid = (low + high)/2;
		if(v[mid] > value)
			high = mid - 1;
		else if(v[mid] < value)
			low = mid + 1;
		else
			return mid;
	}
	return -1;
}

/**
* Removes commas, periods, exclamation marks, and question marks from the end of the string.
*/
void removePunctuation(std::string &str){
	if(str.size() > 1){
		char c = str[str.size()-1];
		if(c == '.' || c == ',' || c == '!' || c == '?')
			str = str.substr(0, str.size() - 1);
		c = str[0];
		if(c == '-' || c == '\'')
			str = str.substr(0, str.size() - 1);
	}
}

/**
* Checks whether a string contains at least one alpha numeric character.
*/

bool hasAlphaNumChar(const string &str){
	for(int i = 0; i < str.size(); ++i)
		if(isalnum(str[i]))
			return true;
	return false;
}