#include <string>
#include <vector>
#include "SentenceSplitter.h"

using namespace std;

/**
 * Constructor
 */
SentenceSplitter::SentenceSplitter(){}

/**
 * sentenceSplit
 * Takes a long string and returns a vector of
 * every sentence in that string
 */
vector<string> SentenceSplitter::sentenceSplit(string all){
	vector<string> result;
	string temp = "";

	//iterate through string
	for(string::const_iterator it = all.begin(); it != all.end(); ++it){
		//if it is a punctuation
		if(isPunct(*it)){
			if(temp.size() > 0){
				temp += *it;
				result.push_back(temp);
				temp = "";
			}
		}
		//if it is not the case that the character is " " and temp is empty
		else if(!((*it) == ' ' && temp.size() == 0))
			temp += *it;
	}
	if(temp.size() != 0)
		result.push_back(temp);
	return result;
}

/**
 * isPunct
 * Returns true or false depending on if
 * the parameter is a punctuation character
 */
bool SentenceSplitter::isPunct(char c){
	bool result = false;
	if(c == '.' || c == '?' || c == '!')
		result = true;
	return result;
}

