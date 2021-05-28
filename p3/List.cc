#include "List.h"
#include "Util.h"
#include "Task.h"

List::List(string name){
	if(name==""){//Si el nombre esta vacio
		throw ERR_EMPTY;//Lanzar excepcion
	}
	else{
		this->name=name;//Asignar nombre a la lista
	}
}

unsigned List::getNumTasks() const{
	int numTasks=0;//Número de tareas
	for(unsigned int i=0; i<tasks.size(); i++)
		numTasks++;
	
	return numTasks;
}

unsigned List::getNumDone() const{
	int numTasksDone=0;//Número de tareas echas
	for(unsigned int i=0; i<tasks.size(); i++){
		if(tasks[i].getIsDone()==true)
			numTasksDone++;
	}
	return numTasksDone;
}

int List::getTimeTasks() const{
	int timeTasks=0;//Tiempo de las tareas
	for(unsigned int i=0; i<tasks.size(); i++)
		timeTasks=timeTasks+tasks[i].getTime();

	return timeTasks;
}

int List::getTimeDone() const{
	int timeTasksDone=0;//Tiempo de las tareas echas
	for(unsigned int i=0; i<tasks.size(); i++){
		if(tasks[i].getIsDone()==true)
			timeTasksDone=timeTasksDone+tasks[i].getTime();
	}
	return timeTasksDone;
}

int List::getPosTask(string name) const{
	int pos=-1;//Posción del vector -1 si no existe el nombre de la tarea
	for(unsigned int i=0; i<tasks.size(); i++){
		if(name==tasks[i].getName())
			pos=i;//Posición de la tarea si existe con ese nombre
	}
	return pos;
}

bool List::setName(string name){
	if(name==""){//Si el nombre esta vacio
		Util::error(ERR_EMPTY);//Mostrar error
		return false;
	}
	else{
		this->name=name;//Si no modificar el nombre
		return true;
	}
}

bool List::deleteTask(string name){
	bool erase=false;
	for(unsigned int i=0; i<tasks.size(); i++){//Recorrer vector tareas
		if(name==tasks[i].getName()){//Si el nombre coincide
			tasks.erase(tasks.begin()+i);//Borrar la tarea
			erase=true;
			i--;
		}
	}
	if(erase)
		return true;

	Util::error(ERR_TASK_NAME);//Si no se encuentra mostrar error
	return false;
}

bool List::toggleTask(string name){
	bool change=false;
	for(unsigned int i=0; i<tasks.size(); i++){//Recorrer vector tareas
		if(name==tasks[i].getName()){//Si el nombre coincide 
			tasks[i].toggle();//Cambia el estado de completado a no completado y viceversa
			change=true;
		}
	}
	if(change)
		return true;
	
	Util::error(ERR_TASK_NAME);//Si no encuentra ningun nombre igual mostrar error
	return false;
}

ostream& operator<<(ostream &os, List &l){
	os<<l.name<<endl;//Imprimir nombre

	for(unsigned int i=0; i<l.tasks.size(); i++){
		if(l.tasks[i].getIsDone()==false){
			os<<l.tasks[i];//Operador salida de Task
		}
	}

	for(unsigned int i=0; i<l.tasks.size(); i++){
		if(l.tasks[i].getIsDone()==true){
			os<<l.tasks[i];//Operador salida de Task
		}
	}

	return os;
}
