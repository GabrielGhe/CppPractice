#include <iostream>
#include <string>
#include "MinorProject.h"
#include "Task.h"

using namespace std;

// Implementation of MinorProject.h

/***********************************************************
* PUBLIC FUNCTIONS
***********************************************************/
bool MinorProject::DEBUG = false;

/**
 * Default Constructor
 */
MinorProject::MinorProject(){	
	if(DEBUG)
		cout << "MinorProject Constructor" << endl;
	tasks = new vector<Task*>;
}

/**
 * Destructor
 */
MinorProject::~MinorProject(){
	if(DEBUG)
		cout << "MinorProject Destructor" << endl;
	delete tasks;
}

/**
* Adds a Task for this project.
*/
void MinorProject::addTask(Task* task){
	tasks->push_back(task);
}

bool MinorProject::tasksReady(){
	if(DEBUG)cout << "Inside MinorProject::tasksReady()" << endl;
	for(vector<Task*>::iterator it = tasks->begin(); it != tasks->end(); ++it)
		if((*it)->ready())
			return true;
	return false;
}

void MinorProject::doIt(){
	if(DEBUG)cout << "Inside MinorProject::doIt()" << endl;
	for(vector<Task*>::iterator it = tasks->begin(); it != tasks->end(); ++it)
		if((*it)->ready()){
			(*it)->doIt();
			break;
		}
}

/***********************************************************
* PRIVATE FUNCTIONS
***********************************************************/

// No private functions

/***********************************************************
* FREE FRIEND FUNCTIONS
***********************************************************/

// No friend functions

/***********************************************************
* FREE FUNCTIONS
***********************************************************/

// No free functions