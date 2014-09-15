#ifndef TASK_H
#define TASK_H

#include <vector>
#include <iostream>

class Task{
	public:
		static const bool DEBUG;
		Task();
		~Task();
		void addPrereq(Task *pt);
		bool ready();
		bool done();
		void doIt();
		
  	private:
		static int tId;
  		int id;
		bool isDone;
		std::vector<Task*> preReqs;
};

// Free function declarations

// None

#endif
