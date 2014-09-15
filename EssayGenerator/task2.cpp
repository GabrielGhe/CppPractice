#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include <map>
#include "Library.h"
#include "Essayomat.h"
#include "Sentence.h"

using namespace std;

/**
* COMP345 Assignment #2 - TASK 2
* To compile: g++ -std=c++11 task2.cpp Library.cpp Essayomat.cpp Stopword.cpp Document.cpp Sentence.cpp SentenceSplitter.cpp -o task2
* Authors: 	Natacha Gabbamonte 6892574
*			Gabriel Gheorghian 5726115
*/

const bool DEBUG = true;

void displayTitle(){
	cout << endl << "WELCOME TO ESSAY-GENERATING ESSAYOMAT APP" << endl << endl;
}

void displayMenu(){
	cout << "Enter 1,2,3 or 4" << endl << setw(20) << "1) Answer questions in file q1.txt with list of files in q1docslist.txt." << endl;
	cout << setw(20) << "2) Answer questions in file q2.txt with list of files in q2docslist.txt." << endl;
	cout << setw(20) << "3) Answer questions in file q3.txt with list of files in q3docslist.txt." << endl;
	cout << setw(20) << "4) Enter a custom questions file and document list file." << endl; 
}

void createAndDisplayEssay(string questions, string filenameOfList){

	const bool USE_SENTENCES = true;
	const string STOPWORDS_FILE = "stopwords.txt";
	
	int maxLength = 500; // max length of essay
	
	Library library(USE_SENTENCES, STOPWORDS_FILE); // The library obj
	
	// Populates library with the file list.
	library.populate(filenameOfList);
	multimap<double, Sentence> scoreMap = library.processQuery(questions);
	
	// Ask for the maximum length of the essay
	cout << "Enter the maximum length for the essay:" << endl;
	cin >> maxLength;
	
	Essayomat essayomat;
	string essay = essayomat.generateEssay(scoreMap, maxLength);
	cout << endl << "Questions:" << endl;
	cout << questions << endl;
	cout << endl << "Essay ("<< essay.size() << "/" << maxLength << "):" << endl;
	cout << essay << endl;
}

string readInFile(string filename){
	string file = "";
	ifstream fin(filename.c_str());
	string word;
	while(fin >> word){
		file += word + " ";
	}
	if(file.size() > 2){
		file.substr(static_cast<string::size_type>(0),static_cast<string::size_type>(file.size() -1));
	}
	if(DEBUG)
		cout << "Read file: " << filename << endl;
	return file;
}

string askForStrInput(string displayStr){
	string str;
	cout << displayStr << endl;
	cin >> str;
	return str;
}

bool processInput(int input){
	bool valid = true;
	string questionFilename;
	string listFilename;
	switch(input){
		case 1:
			createAndDisplayEssay(readInFile("data/q1.txt"), "data/q1docslist.txt");
			break;
		case 2:
			createAndDisplayEssay(readInFile("data/q2.txt"), "data/q2docslist.txt");
			break;
		case 3:
			createAndDisplayEssay(readInFile("data/q3.txt"), "data/q3docslist.txt");
			break;
		case 4:
			questionFilename = askForStrInput("Enter the file containing the questions to be answered:");
			listFilename = askForStrInput("Enter the file containing the list of documents to answer the questions:");
			createAndDisplayEssay(readInFile(questionFilename), listFilename);
			break;
		default:
			valid = false;
			break;
	}
	return valid;
}

/**
* Main method
*/
int main(){
	displayTitle();
	bool valid = true;
	do{
		displayMenu();
		int input;
		cin >> input;
		valid = processInput(input);
		if(!valid)
			cout << "Invalid input!! Try again." << endl;
	}while(!valid);
	cout << endl << "Thank you for using Natacha and Gabriel's Essayomat!" << endl;
	return 0;
}
