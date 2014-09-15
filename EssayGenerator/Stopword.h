#ifndef STOPWORD_H
#define STOPWORD_H

#include <string>
#include <vector>
#include <unordered_map>
#include <map>

class Stopword{
	public:
		Stopword();
		const static bool DEBUG;
		void setStopwords(std::string stopwordsFile);
		void filterWords(std::vector<std::string> &words);
		bool isSet();
	private:
		std::unordered_map<std::string,std::string> stopwords;
};

// free function declarations go here
void toLowerCase(std::string &str);

#endif