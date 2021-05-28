#ifndef _PROJECT_H_
#define _PROJECT_H_

#include <iostream>
#include <vector>
#include <string>
#include "List.h"

using namespace std;

class Project{
	friend ostream& operator<<(ostream &os, Project &p);
	protected:
		vector<List>lists;
		int id;
		string name;
		string description; 
		int getPosList(string name) const;
		//Funciones añadidas
		bool nameList(List &newList);
		bool nameTask(List &newList, Task &newTask) ;
	public:
		Project(string name, string description="");
		int getId() const{return id;};
		string getName() const{return name;};
		string getDescription() const{return description;};
		bool setId(int id);
		bool setName(string name);
		void setDescription(string description){this->description=description;};
		void edit(string name="", string description="");
		void addList(string name="");
		void deleteList(string name="");
		void addTaskToList(string name="");
		void deleteTaskFromList(string name="");
		void toggleTaskFromList(string name="");
		void menu();
		string summary() const;
};

#endif