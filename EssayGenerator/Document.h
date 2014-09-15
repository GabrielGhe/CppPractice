#ifndef DOCUMENT_H
#define DOCUMENT_H
#include <string>
#include <vector>
#include "Sentence.h"

class Document{
	public:
		Document(std::string filename);
		const Sentence & operator[](const int idx) const;
		int size() const;
		void addSentence(std::string value, std::vector<int> counts, std::vector<double> weights);
		void addCountsToTotal(std::vector<int> &numDocsWithWord);
		void printCounts() const;
		const std::string & getFilename() const;
		void computeWeights(const std::vector<int> & numDocsWithWord, int totalNumOfDocs);
		const static bool DEBUG; 
	private:
		std::vector<Sentence> sentences;
		std::string filename;
	};

// Free function declarations 

#endif