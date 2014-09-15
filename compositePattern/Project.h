#ifndef PROJECT_H
#define PROJECT_H

#include <string>
#include <vector>
#include <iostream>
#include "Task.h"

class Project{
	public:
		static bool DEBUG;
		Project();
		virtual ~Project();
		virtual bool tasksReady() = 0;
		virtual void doIt() = 0;
};

// Free function declarations

// None

#endif
