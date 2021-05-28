#ifndef _LIST_H_
#define _LIST_H_

#include <iostream>
#include <vector>
#include "Task.h"


using namespace std;

class List{
	friend ostream& operator<<(ostream &os, List &l);
	protected:
		vector<Task> tasks;
		string name;
	public:
		List(string name);
		string getName() const{return name;}
		vector<Task> getTasks() const{return tasks;}
		unsigned int getNumTasks() const;
		unsigned int getNumDone() const;
		int getTimeTasks() const;
		int getTimeDone() const;
		int getPosTask(string name) const;
		bool setName(string name);
		void addTask(const Task& task){	tasks.push_back(task);}
		bool deleteTask(string name);
		bool toggleTask(string name);
};

#endif