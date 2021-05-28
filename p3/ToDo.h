#ifndef _TODO_H_
#define _TODO_H_

#include <iostream>
#include <vector>
#include "Project.h"

using namespace std;

class ToDo{
	friend ostream& operator<<(ostream &os, ToDo &t);
	protected:
		vector<Project*>projects;
		static int nextId;
		string name;
		int getPosProject(string name) const;
		int getPosProject(int id) const;
		bool checkId(int &id);
	public:
		ToDo(string name);
		string getName() const{return name;};
		bool setName(string name);
		void addProject(Project* project);
		void deleteProject(int id=0);
		void setProjectDescription(string name, string description);
		void projectMenu(int id=0);
};

#endif