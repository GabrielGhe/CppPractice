#ifndef COMPOSITEPROJECT_H
#define COMPOSITEPROJECT_H

#include <string>
#include <vector>
#include <iostream>
#include "Project.h"
#include "Task.h"

class CompositeProject: public Project{
	public:
		static bool DEBUG;
		CompositeProject();
		virtual ~CompositeProject();
		void addProject(Project* pp);
		virtual bool tasksReady();
		virtual void doIt();
		
  	private:
  		std::vector<Project*>* projects;
};

// Free function declarations

// None

#endif
