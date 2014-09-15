#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <cmath>
#include "Document.h"
#include "Sentence.h"

using namespace std;

// Implementation of Document.h

const bool Document::DEBUG = true;

/***********************************************************
* PUBLIC FUNCTIONS
***********************************************************/

/**
* Document constructor needing a file name.
*/
Document::Document(string filename) : filename(filename){}

/**
* Returns the file name.
*/
const string & Document::getFilename() const{
	return filename;
}

/**
* Returns the number of sentences in the document.
*/
int Document::size() const{
	return sentences.size();
}

/**
* Returns the sentence of the document at the specified index.
*/
const Sentence & Document::operator[](const int idx) const{
	return sentences[idx];
}

/**
* Adds a sentence to the document.
*/
void Document::addSentence(string value, std::vector<int> counts, std::vector<double> weights){
	Sentence s(filename, size()+1, value, counts, weights);
	/*
	cout << "Adding sentence:" << endl
		<< "   " << filename << endl
		<< "   " << size()+1 << endl
		<< "   " << value << endl;
		*/
	sentences.push_back(s);
}

/**
* Adds 1 to a word count if this Document has at least one of that specific word.
*/
void Document::addCountsToTotal(vector<int> &numDocsWithWord){
	int index = 0;
	for(vector<int>::iterator it = numDocsWithWord.begin(); it != numDocsWithWord.end(); ++it){
		for(vector<Sentence>::const_iterator senIt = sentences.begin(); senIt != sentences.end(); ++senIt){
			if((senIt->counts)[index] != 0){
				(*it) += 1;
				//break; //*Doesn't need the break when WEIGHT formula has "Num of Docs with Word" to mean "Num of Sentences with Word"
			}
		}
		++index;
	}
	
}

void Document::printCounts() const{
	for(vector<Sentence>::const_iterator senIt = sentences.begin(); senIt != sentences.end(); ++senIt){
		vector<int> counts = senIt->counts;
		cout << "  " << "sentence at " << senIt->position << endl;
		for(vector<int>::const_iterator it = counts.begin(); it != counts.end(); ++it){
			cout << "   " << *it << endl;
		}
		cout << endl;
	}
}

void Document::computeWeights(const vector<int> & numDocsWithWord, int totalNumOfDocs){
	int index = 0;
	for(vector<Sentence>::iterator it = sentences.begin(); it != sentences.end(); ++it)
	{
		index = 0;
		vector<int> counts = it->counts;
		vector<double> weights = it->weights;
		weights.clear();
		assert(counts.size() == numDocsWithWord.size() && "The vectors of counts and the total docs with certain word vectors should be equal.");
		for(vector<int>::const_iterator countsIt = counts.begin(); countsIt != counts.end(); ++countsIt, ++index){
			if(*countsIt != 0){
				assert(numDocsWithWord[index] != 0 && "If number of documents that have this word is = to 0 then this line should never execute!");
				double w;
				double temp1 = *countsIt;
				temp1 = log10(temp1);
				double temp2 = totalNumOfDocs;
				temp2 /= numDocsWithWord[index];
				temp2 = log10(temp2);
				
				assert(temp2 >= 0 && "SECOND log is >= 0");		
				assert(temp1 >= 0 && "FIRST log is >= 0");
				
				w = 1 + (temp1 * temp2);
				
				/*
				if(DEBUG)
					cout << "Weight for document (" << filename << ")[" << index << "]: 1 + log10(" << *countsIt << ")*log10(" << totalNumOfDocs << "/" << numDocsWithWord[index] << ") = " << w << endl;	
				*/
				weights.push_back(w);
			}
			else
				weights.push_back(0);
		}
		it->counts = counts;
		it->weights = weights;
		
	}
	if(DEBUG)
			cout << "Done computing weights for Document: " << filename << ", num of Sentence= " << size() << endl; 
}

/***********************************************************
* PRIVATE FUNCTIONS
***********************************************************/

// No private functions

/***********************************************************
* FREE FUNCTIONS
***********************************************************/

// No free functions