#include <iostream>
#include <string>
#include "CompositeProject.h"
#include "Project.h"
#include "Task.h"

using namespace std;

// Implementation of CompositeProject.h

/***********************************************************
* PUBLIC FUNCTIONS
***********************************************************/
bool CompositeProject::DEBUG = false;

/**
 * Constructor
 */
CompositeProject::CompositeProject(){	
	if(DEBUG)
		cout << "CompositeProject Constructor" << endl;
	projects = new vector<Project*>;
}

/**
 * Destructor
 */
CompositeProject::~CompositeProject(){
	if(DEBUG)
		cout << "CompositeProject Destructor" << endl;
	delete projects;
}

void CompositeProject::addProject(Project* pp){
	if(DEBUG)
		cout << "[CompositeProject::addProject()] Adding Project to CompositeProject" << endl;
	projects->push_back(pp);
}

bool CompositeProject::tasksReady(){
	if(DEBUG)cout << "Inside CompositeProject::tasksReady()" << endl;
	for(vector<Project*>::iterator it = projects->begin(); it != projects->end(); ++it)
	{
		if((*it)->tasksReady()){
			return true;
		}
	}
	return false;
}

void CompositeProject::doIt(){
	if(DEBUG)cout << "Inside CompositeProject::doIt()" << endl;
	for(vector<Project*>::iterator it = projects->begin(); it != projects->end(); ++it)
		if((*it)->tasksReady()){
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