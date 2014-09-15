#ifndef SENTENCESPLITTER_H_
#define SENTENCESPLITTER_H_

#include <string>
#include <vector>

class SentenceSplitter{
	public:
		SentenceSplitter();
		std::vector<std::string> sentenceSplit(std::string all);
	private:
		bool isPunct(char c);
};


#endif /* SENTENCESPLITTER_H_ */
