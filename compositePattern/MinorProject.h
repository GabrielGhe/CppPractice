#ifndef MINORPROJECT_H
#define MINORPROJECT_H

#include <string>
#include <vector>
#include <iostream>
#include "Project.h"
#include "Task.h"

class MinorProject: public Project{
	public:
		static bool DEBUG;
		MinorProject();
		virtual ~MinorProject();
		void addTask(Task* task);
		virtual bool tasksReady();
		virtual void doIt();		
  	private:
  		std::vector<Task*>* tasks;
};

// Free function declarations

// None

#endif
