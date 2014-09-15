#ifndef SIMPLEPROJECT_H
#define SIMPLEPROJECT_H

#include <string>
#include <vector>
#include <iostream>
#include "Project.h"
#include "Task.h"

class SimpleProject: public Project{
	public:
		static bool DEBUG;
		SimpleProject(Task *pt);
		virtual ~SimpleProject();
		virtual bool tasksReady();
		virtual void doIt();
		
  	private:
		Task* task;
};

// Free function declarations

// None

#endif
