#include <iostream>
#include <string>
#include "Project.h"
#include "Task.h"

using namespace std;

// Implementation of Project.h

/***********************************************************
* PUBLIC FUNCTIONS
***********************************************************/
bool Project::DEBUG = false;

/**
 * Default Constructor
 */
Project::Project(){
	if(DEBUG)
		cout << "Project Constructor" << endl;
}

/**
 * Destructor
 */
Project::~Project(){
	if(DEBUG)
		cout << "Project Destructor" << endl;
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