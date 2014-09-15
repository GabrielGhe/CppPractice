#include <iostream>
#include <string>
#include "SimpleProject.h"
#include "Task.h"

using namespace std;

// Implementation of SimpleProject.h

/***********************************************************
* PUBLIC FUNCTIONS
***********************************************************/
bool SimpleProject::DEBUG = false;

/**
 * Constructor
 */
SimpleProject::SimpleProject(Task *pt){	
	if(DEBUG)
		cout << "SimpleProject Constructor" << endl;
	task = pt;
}

/**
 * Destructor
 */
SimpleProject::~SimpleProject(){
	if(DEBUG)
		cout << "SimpleProject Destructor" << endl;
	delete task;
}

bool SimpleProject::tasksReady(){
	if(DEBUG)cout << "Inside SimpleProject::tasksReady()" << endl;
	return task->ready();
}

void SimpleProject::doIt(){
	if(DEBUG)cout << "Inside SimpleProject::doIt()" << endl;
	task->doIt();
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