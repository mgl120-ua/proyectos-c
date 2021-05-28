#include "ToDo.h"
#include "Util.h"
#include "Project.h"

int ToDo::nextId=1;

ToDo::ToDo(string name){
	if(name=="")//Si el nombre esta vac
		throw ERR_EMPTY;//Lanzar excepcion
	else
		this->name=name;//Asignar nombre al proyecto
}

//string ToDo::getName() const{}
int ToDo::getPosProject(string name) const{
	int pos=-1;//Inicializar posicion a -1
	for(unsigned int i=0; i<projects.size(); i++){//Recorrer vector lista
		if(projects[i]->getName()==name)//Si el nombre coincide 
			pos=i;//Cambiar posición a la posición correcta 
	}
	return pos;
}

int ToDo::getPosProject(int id) const{
	int pos=-1;//Inicializar posicion a -1
	for(unsigned int i=0; i<projects.size(); i++){//Recorrer vector lista
		if(projects[i]->getId()==id)//Si el nombre coincide 
			pos=i;//Cambiar posición a la posición correcta 
	}
	return pos;
}

bool ToDo::setName(string name){
	if(name==""){//Si se introduce una cadena vacía
		Util::error(ERR_EMPTY);//Mostrar error
		return false;
	}
	else{
		this->name=name;//Modificar el nombre del proyecto
		return true;
	}
}

void ToDo::addProject(Project* project){
	//comprobar que el vector no esta vacio
	if(!(projects.empty())){
		for(unsigned int i=0; i<projects.size(); i++){
			//Comprobar que no hay ningun proyecto igual a la que se quiere añadir
			if(project->getName()==projects[i]->getName()){
				throw ERR_PROJECT_NAME;
				return;
			}
		}
	} 

	project->setId(nextId);
	nextId++;

	projects.push_back(project);//Añade nuevo proyecto al vector projects
}

//Funcion comprobar id
bool ToDo::checkId(int &id){
	//return(true)-> exisiste un proyecto con ese id, return(false)-> id del proyecto no existe
  	if(id==0){
  		cout<<"Enter project id: ";
  		cin>>id;
  	}

  	//comprobar que el vector no esta vacio
	if(!(projects.empty())){
		for(unsigned int i=0; i<projects.size(); i++){
			//Comprobar que hay algun proyecto con ese id
			if(id==projects[i]->getId())
				return(true);
		}
	}

	return(false);
}

void ToDo::deleteProject(int id){
	if(checkId(id))//Si el id introducido es correcto
		projects.erase(projects.begin()+getPosProject(id));//Se borra el proyecto con ese id
	else
		Util::error(ERR_ID);
}

void ToDo::setProjectDescription(string name, string description){
	//comprobar que el vector no esta vacio
	if(!(projects.empty())){
		for(unsigned int i=0; i<projects.size(); i++){
			//Comprobar que no hay ninguna lista igual a la que se quiere añadir
			if(name==projects[i]->getName()){
				projects[i]->setDescription(description);
				return;
			}
		}
	} 
	Util::error(ERR_PROJECT_NAME);
}

void ToDo::projectMenu(int id){
	if(checkId(id)){
		projects[getPosProject(id)]->menu();
	}
	else{
		Util::error(ERR_ID);
	}
}

ostream& operator<<(ostream &os, ToDo &t){
	for(unsigned int i=0; i<t.projects.size(); i++)
		os<<t.projects[i]->summary()<<endl;
	return os;
}