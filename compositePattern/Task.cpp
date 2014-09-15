#include <iostream>
#include <string>
#include "Task.h"

using namespace std;

// Implementation of Task.h

/***********************************************************
* PUBLIC FUNCTIONS
***********************************************************/
const bool Task::DEBUG = false;
int Task::tId = 0;

/**
 * Constructor
 */
Task::Task(){
	id = tId;
	++tId;
	isDone = false;
	if(DEBUG)
		cout << "Task Constructor (" << id << ")" << endl;
}

/**
 * Destructor
 */
Task::~Task(){
	cout << "Task " << id << " deleted." << endl;
}

void Task::addPrereq(Task *pt){
	preReqs.push_back(pt);
}

bool Task::ready(){
	if(isDone)
		return false;
	for(vector<Task*>::const_iterator it = preReqs.begin(); it != preReqs.end(); ++it)
	{
		// If any of the pre-reqs are not done, return false.
		if(!(*it)->done())
			return false;
	}
	return true;
}
bool Task::done(){
	return isDone;
}

void Task::doIt() /*throw(TaskAlreadyDone, TaskNotReady)*/{
	if(done()){
		throw /*TaskAlreadyDone(*/"Task is already done."/*)*/;
	}
	else if(!ready()){
		throw /*TaskNotReady(*/"Task is not ready."/*)*/;
	}
	else{
		isDone = true;
		cout << "Doing Task " << id << endl;
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