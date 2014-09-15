#ifndef SENTENCE_H
#define SENTENCE_H

#include <string>
#include <vector>
class Document;
class Sentence{
	public:
		Sentence(std::string filename, int position, std::string value, std::vector<int> counts, std::vector<double> weights);	
		const std::string & getFilename() const;
		const int & getPosition() const;
		const std::string & getValue() const;
		const std::vector<int> & getCounts() const;
		const std::vector<double> & getWeights() const;
	private:
		std::string filename;
		int position;
		std::string value;
		std::vector<int> counts;
		std::vector<double> weights;
	friend class Document;
};

// Free function declarations

#endif