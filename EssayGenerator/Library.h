#ifndef LIBRARY_H
#define LIBRARY_H

#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include "Stopword.h"
#include "Document.h"
#include "Sentence.h"

class Library{
	public:
		Library(bool useSentences);
		Library(bool useSentences, std::string stopwordsFile);
		const static bool DEBUG; 
		void populate(std::string filename);
		std::multimap<double, Sentence> processQuery(std::string query);
	private:
		std::unordered_map<std::string, Document> map;
		std::vector<std::string> words;
		std::vector<int> numDocsWithWord;
		bool useSentences;
		Stopword stopword;
		void resetVariables();
		int getNumOfDocuments();
		void processSentence(Document & document, std::vector<std::string> & words);
};

// Free function declarations 
int binarySearch(const std::vector<std::string> &v, const std::string value);
double findMagnitude(const std::vector<int> &values);
double findMagnitude(const std::vector<double> &values);
void toLowerCase(std::string &str);
void removePunctuation(std::string &str);
bool hasAlphaNumChar(const std::string &str);

#endif