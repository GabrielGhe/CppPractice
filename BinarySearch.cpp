//============================================================================
// Name        : BinarySearch.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <string>
using namespace std;

int binarySearch(vector<string> v, string value){
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

int main() {
	vector<string> words;
	words.insert(words.end(), "ab");
	words.insert(words.end(), "ac");
	words.insert(words.end(), "ad");
	words.insert(words.end(), "ae");
	words.insert(words.end(), "af");
	words.insert(words.end(), "ag");
	words.insert(words.end(), "ah");
	words.insert(words.end(), "bb");
	words.insert(words.end(), "bc");
	words.insert(words.end(), "bd");
	words.insert(words.end(), "be");
	words.insert(words.end(), "bf");
	words.insert(words.end(), "bg");
	words.insert(words.end(), "bh");

	int pos = binarySearch(words, "as");
	bool good = (pos != -1)? true : false;
	cout << "Pos is " << pos;
	if(good)
		cout << " element is " << words[pos];

	cout << endl;

	return 0;
}
