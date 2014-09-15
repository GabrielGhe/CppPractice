#include <string>
#include <vector>
#include "Sentence.h"

using namespace std;

// Implementation of Sentence.h

/***********************************************************
* PUBLIC FUNCTIONS
***********************************************************/

Sentence::Sentence(string filename, int position, string value, vector<int> counts, vector<double> weights) : filename(filename), position(position), value(value), counts(counts), weights(weights){}

const string & Sentence::getFilename() const{
	return filename;
}

const int & Sentence::getPosition() const{
	return position;
}

const string & Sentence::getValue() const{
	return value;
}
	
const vector<int> & Sentence::getCounts() const{
	return counts;
}

const vector<double> & Sentence::getWeights() const{
	return weights;
}
		
/***********************************************************
* PRIVATE FUNCTIONS
***********************************************************/

// No private functions

/***********************************************************
* FREE FUNCTIONS
***********************************************************/

// No free functions