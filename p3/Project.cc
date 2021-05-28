#include "Project.h"
#include "Util.h"
#include "List.h"
#include "Task.h"

Project::Project(string name, string description){
	if(name=="")//Si el nombre esta vac
		throw ERR_EMPTY;//Lanzar excepcion
	else{
		this->name=name;//Asignar nombre al proyecto
		this->description=description;//Asignar descripción al proyeto
		id=0;//Inicializar id
	}
}

int Project::getPosList(string name) const{
	int pos=-1;//Inicializar posicion a -1
	for(unsigned int i=0; i<lists.size(); i++){//Recorrer vector lista
		if(lists[i].getName()==name)//Si el nombre coincide 
			pos=i;//Cambiar posición a la posición correcta 
	}
	return pos;
}

bool Project::setId(int id){
	if(id>=0){
		this->id=id;//Modificar identificador del proyecto
		return true;
	}
	else{
		Util::error(ERR_ID);//Mostrar error
		return false;
	}
}

bool Project::setName(string name){
	if(name==""){//Si se introduce una cadena vacía
		Util::error(ERR_EMPTY);//Mostrar error
		return false;
	}
	else{
		this->name=name;//Modificar el nombre del proyecto
		return true;
	}
}

void Project::edit(string name, string description){
	do{
    	cout<<"Enter project name: ";
    	getline(cin,name); 
	}while(setName(name)==false);
	
	cout<<"Enter project description: ";
	getline(cin,description);  
	setDescription(description);
}

//Función introducir nombre de lista
bool Project::nameList(List &newList){
	//return(true)-> lista existe , return(false)-> lista no existe
	string newName;
	do{
		cout<<"Enter list name: ";
		getline(cin, newName);
	}while(newList.setName(newName)==false);

	//comprobar que el vector no esta vacio
	if(!(lists.empty())){
		for(unsigned int i=0; i<lists.size(); i++){
			//Comprobar que no hay ninguna lista igual a la que se quiere añadir
			if(newList.getName()==lists[i].getName())
				return(true);
		}
	}

	//vector vacio
	if(lists.empty())
    	return(false);

	return(false);
}

//Función introducir nombre tarea
bool Project::nameTask(List &newList, Task &newTask){
	//return(true)-> tarea existe , return(false)-> tarea no existe
	string newName;
	cout<<"Enter task name: ";
	getline(cin,newName);
	newTask.setName(newName);

	//Existe una tarea con el mismo nombre que se quiere añadir
	for(unsigned int i=0; i<lists.size(); i++){
		for(unsigned int j=0; j<lists[i].getTasks().size(); j++){
			if(newList.getName()==lists[i].getName() && newTask.getName()==lists[i].getTasks()[j].getName()){
				return(true);
			}
		}
	}

	//Vector vacio, por tanto no existe ninguna tarea
	for(unsigned int i=0; i<lists.size(); i++){
		if(lists[i].getTasks().empty())
			return(false);
	}
	return(false);
}

void Project::addList(string name){
	List newList(name);

	if(nameList(newList))//comprobar que la lista existe para dar error
		Util::error(ERR_LIST_NAME);
	else
		lists.push_back(newList); //Añadir lista al final del vector si la lista no existe 
}

void Project::deleteList(string name){
	List newList(name);

	if(nameList(newList)){//Comprobar que la lista existe
		if(!(lists.empty())){//Comprobar que el vector no esta vacio
			for(unsigned int i=0; i<lists.size(); i++){
				if(newList.getName()==lists[i].getName())
					lists.erase(lists.begin()+i);//Eliminar lista del vector
			}
		}
	}
	else
		Util::error(ERR_LIST_NAME);//Si el vector esta vacio el nombre de la lista no existe y tambien mostramos ERR_LIST_NAME
}

void Project::addTaskToList(string name){
	List newList(name);
	Task newTask(name);
	string newName,newDeadline;
	int newTime;

	if(!(nameList(newList))){//Comprobar que la lista no existe para dar error y volver al menu
		Util::error(ERR_LIST_NAME);
		return;
	}
	
	cout<<"Enter task name: ";
	getline(cin,newName);
	newTask.setName(newName);

	cout<<"Enter deadline: ";
	cin>>newDeadline;
	if(newTask.setDeadline(newDeadline)==false)
		return;

	cout<<"Enter expected time: ";
	cin>>newTime;
	if(newTask.setTime(newTime)==false)
		return;

	for(unsigned int i=0; i<lists.size(); i++){
		if(newList.getName()==lists[i].getName()){
	  		lists[i].addTask(newTask);//Añadir nuevo registro Task en la lista correspondiente si la lista existe  		
	  	}
	}
}

void Project::deleteTaskFromList(string name){
	List newList(name);
	Task newTask(name);

	//Comprobar si la lista introducida no existe para dar error y volver al menu
	if(!(nameList(newList))){
		Util::error(ERR_LIST_NAME);
		return;
	}

	//Comprobar si la tarea introducida no existe para dar error y volver al menu
	if(!(nameTask(newList, newTask))){
		Util::error(ERR_TASK_NAME);
		return;
	}
	for(unsigned int i=0; i<lists.size(); i++){
		if(newList.getName()==lists[i].getName()){
			lists[i].deleteTask(newTask.getName());
		}
	}
}

void Project::toggleTaskFromList(string name){
	List newList(name);
	Task newTask(name);

	if(!(nameList(newList))){
		Util::error(ERR_LIST_NAME);
		return;
	}

	if(!(nameTask(newList, newTask))){
		Util::error(ERR_TASK_NAME);
		return;
	}

	for(unsigned int i=0; i<lists.size(); i++){
		if(newList.getName()==lists[i].getName()){
			lists[i].toggleTask(newTask.getName());
		}
	}
}

void showMenu(){
  cout << "1- Edit project" << endl
       << "2- Add list" << endl
       << "3- Delete list" << endl 
       << "4- Add task" << endl
       << "5- Delete task" << endl
       << "6- Toggle task" << endl
       << "7- Report" << endl
       << "b- Back to main menu" << endl
       << "Option: ";
}

void Project::menu(){
  	char option;
	do{
		showMenu();
		cin>>option;
		cin.get();
	    
	    switch(option){
		    case '1': edit(name,description);
		                break;
		    case '2': addList(name);
		                break;
		    case '3': deleteList(name);
		                break;
		    case '4': addTaskToList(name);
		                break;
		    case '5': deleteTaskFromList(name);
		                break;
		    case '6': toggleTaskFromList(name);
		                break;
		    case '7': cout << *this << endl;
		                break;
		    case 'b': break;
		    default: Util::error(ERR_OPTION);
	   	}
	}while(option!='b');
}

string Project::summary() const{
	int  notDone=0, total=0;
	string concatenation="";
		
	for(unsigned int j=0; j<lists.size(); j++){//Recorrer vector de listas
		for(unsigned int k=0; k<lists[j].getTasks().size(); k++){//Recorrer vector de tareas
			total++;

			if(lists[j].getTasks()[k].getIsDone()==true)//Si la tarea no esta completada
				notDone++;//Contador de tareas pendientes
		}
	}
	concatenation+="("+to_string(id)+") "+name+" ["+to_string(notDone)+"/"+to_string(total)+"]";
	return concatenation;
}

ostream& operator<<(ostream &os, Project &p){
	int  done=0, left=0, totalDone=0, totalLeft=0, oldDay=100, oldMonth=100, oldYear=3000;
	string oldTask;
	os<<"Name: "<<p.name<<endl;//Imprimir nombre
	if(p.description!="")
		os<<"Description: "<<p.description<<endl;
	
	for(unsigned int i=0; i<p.lists.size(); i++){//Recorrer vector de listas
		os<<p.lists[i];//Operador salida de List
		//Recorrer vector de tareas no echas
		for(unsigned int j=0; j<p.lists[i].getTasks().size(); j++){//Recorrer vector de tareas
			if(p.lists[i].getTasks()[j].getIsDone()==false){//Si la tarea no esta completada
				left++;//Contador de tareas pendientes
				totalLeft=totalLeft+p.lists[i].getTasks()[j].getTime();//Contador del tiempo de las tareas pendientes
			}
		}

		//Recorrer vector de tareas echas
		for(unsigned int j=0; j<p.lists[i].getTasks().size(); j++){//Recorrer vector de tareas
			if(p.lists[i].getTasks()[j].getIsDone()==true){//Si la tarea esta completada
				done++;//Contador de tareas echas
				totalDone=totalDone+p.lists[i].getTasks()[j].getTime();//Contador del tiempo de las tareas echas
			}
		}	
	}
		os<<"Total left: "<<left<<" ("<<totalLeft<<" minutes)"<<endl;//Total de las tareas pendientes
		os<<"Total done: "<<done<<" ("<<totalDone<<" minutes)"<<endl;//Total de las tareas echas 
		for(unsigned int i=0; i<p.lists.size(); i++){//Recorrer vector de listas
			for(unsigned int j=0; j<p.lists[i].getTasks().size(); j++){//Recorrer vector de tareas
				if(p.lists[i].getTasks()[j].getIsDone()==false){//Si la tarea no esta completada
					//Y si el año es mayor que el anterior
					if((oldYear>p.lists[i].getTasks()[j].getDeadline().year) 
						//Si el año es igual, pero el mes es mayor que el anterio
						|| ((oldYear==p.lists[i].getTasks()[j].getDeadline().year) && (oldMonth>p.lists[i].getTasks()[j].getDeadline().month))
							//Si el año y el mes son iguales pero el dia es mayor 
							|| ((oldYear==p.lists[i].getTasks()[j].getDeadline().year) && (oldMonth>p.lists[i].getTasks()[j].getDeadline().month) && (oldDay>p.lists[i].getTasks()[j].getDeadline().day))){

								//Guardar valores para comprobar con la siguiente tarea
								oldYear=p.lists[i].getTasks()[j].getDeadline().year;
								oldMonth=p.lists[i].getTasks()[j].getDeadline().month;
								oldDay=p.lists[i].getTasks()[j].getDeadline().day;
								oldTask=p.lists[i].getTasks()[j].getName();
					}
				}
			}
		}
		if(oldTask!="")
			os<<"Highest priority: "<<oldTask<<" ("<<oldYear<<"-"<<oldMonth<<"-"<<oldDay<<")"<<endl;//Mostrar la tarea mas antigua y pendiente de hacer
	return os;
}