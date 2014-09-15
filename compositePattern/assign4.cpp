#include <iostream>
#include <string>
#include "Task.h"
#include "Project.h"
#include "SimpleProject.h"
#include "MinorProject.h"
#include "CompositeProject.h"

using namespace std;

/**
* COMP 345 - Assignment #4
* To compile: g++ assign4.cpp CompositeProject.cpp MinorProject.cpp SimpleProject.cpp Project.cpp Task.cpp -o assign4
* Authors: 	Natacha Gabbamonte 6892574
*			Gabriel Gheorghian 5726115
*/

/*
int main(){
	Project* p1 = new SimpleProject(new Task());
	cout << "p1 ready: " << p1->tasksReady() << endl;
	MinorProject* p2 = new MinorProject();
	p2->addTask(new Task());
	cout << "p2 ready: " << p2->tasksReady() << endl;
	
	/*
	vector<Project*>* projects = new vector<Project*>;
	projects->push_back(p1);
	projects->push_back(p2);
	
	for(vector<Project*>::iterator it = projects->begin(); it != projects->end(); ++it)
		if((*it)->tasksReady())
			cout << "YAY" << endl;
	
	CompositeProject* cp = new CompositeProject();
	cp->addProject(p1);
	cp->addProject(p2);
	cout << "cp ready: " << cp->tasksReady() << endl;
	
	delete p1;
	delete p2;
	delete cp;
	
	return 0;
}
*/


int main()
{
	const bool DEBUG = false;
	// Create tasks
	Task* tasks[7];
	for (int i = 0; i != 7; ++i)
	tasks[i] = new Task();
	if(DEBUG)cout << "*Done creating tasks" << endl << endl;
	// Set prerequisites
	tasks[1]->addPrereq(tasks[0]);
	tasks[2]->addPrereq(tasks[1]);
	tasks[3]->addPrereq(tasks[2]);
	tasks[3]->addPrereq(tasks[4]);
	tasks[4]->addPrereq(tasks[0]);
	tasks[5]->addPrereq(tasks[4]);
	tasks[6]->addPrereq(tasks[3]);
	tasks[6]->addPrereq(tasks[5]);
	if(DEBUG)cout << "*Done setting prerequisites" << endl << endl;
	// Create projects
	MinorProject *mp1 = new MinorProject();
	mp1->addTask(tasks[1]);
	mp1->addTask(tasks[2]);
	mp1->addTask(tasks[3]);
	if(DEBUG)cout << "*Done adding tasks to MinorProject mp1" << endl << endl;
	MinorProject *mp2 = new MinorProject();
	mp2->addTask(tasks[4]);
	mp2->addTask(tasks[5]);
	if(DEBUG)cout << "*Done adding tasks to MinorProject mp2" << endl << endl;
	CompositeProject *cp = new CompositeProject();
	
	cp->addProject(new SimpleProject(tasks[0]));
	cp->addProject(mp1);
	cp->addProject(mp2);
	cp->addProject(new SimpleProject(tasks[6]));
	if(DEBUG)cout << "*Done adding projects to CompositeProject cp" << endl << endl;
	
	if(DEBUG)cout << "*About to perform all tasks:" << endl << endl;
	// Perform all tasks
	while (cp->tasksReady()){
		try{
		cp->doIt();
		}catch(char const* e){
			cout << "Exception occurred: " << e << endl;
			delete e;
			break;
		}
	}
	
	if(DEBUG)cout << "*Done performing tasks!" << endl << endl;
	
	// Clean up
	delete cp;
	return 0;
}


/*
int main(){
	Task* t1 = new Task();
	Task* t2 = new Task();
	t1->addPrereq(t2);
	if(t1->ready())
		cout << "Task1 is ready";
	else
		cout << "Task1 is not ready";
	cout << endl;

	if(t1->done())
		cout << "Task1 is done";
	else
		cout << "Task1 is not done";
	cout << endl;
	
	try{
		cout << "Trying to do Task 1..." << endl;
		t1->doIt();
	}catch(char const* e){
		cout << "Exception occured: " << e << endl;
		delete e;
	}
	cout << "Trying to do Task 2..." << endl;
	t2->doIt();
	if(t1->ready())
		cout << "Task1 is ready";
	else
		cout << "Task1 is not ready";
	cout << endl;
	
	try{
		cout << "Trying to do Task 1..." << endl;
		t1->doIt();
	}catch(char const* e){
		cout << "Exception occured: " << e << endl;
		delete e;
	}
	if(t1->done())
		cout << "Task1 is done";
	else
		cout << "Task1 is not done";
	cout << endl;
	
	delete t1;
	delete t2;
	return 0;
}
*/