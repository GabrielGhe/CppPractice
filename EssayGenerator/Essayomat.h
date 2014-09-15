#ifndef ESSAYOMAT_H
#define ESSAYOMAT_H

#include <string>
#include <map>
#include "Sentence.h"

class Essayomat{
	public:
		Essayomat();
		const static bool DEBUG; 
		std::string generateEssay(std::multimap<double, Sentence> &scoreMap, int maxLength);
};

// Free function declarations

#endif