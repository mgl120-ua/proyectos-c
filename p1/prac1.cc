//50507753Y GRIMALDOS LOPEZ, MARTA

#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

struct Date{
  int day;
  int month;
  int year;
};

struct Task{
  string name;
  Date deadline;
  bool isDone;
  int time;
};

struct List{
  string name;
  vector<Task> tasks;
};

struct Project{
  int id;
  string name;
  string description;
  vector<List> lists;
};

enum Error{
  ERR_OPTION,
  ERR_EMPTY,
  ERR_LIST_NAME,
  ERR_TASK_NAME,
  ERR_DATE,
  ERR_TIME
};

void error(Error e){
  switch(e){
    case ERR_OPTION:
      cout << "ERROR: wrong menu option" << endl;
      break;
    case ERR_EMPTY:
      cout << "ERROR: empty string" << endl;
      break;
    case ERR_LIST_NAME:
      cout << "ERROR: wrong list name" << endl;
      break;
    case ERR_TASK_NAME:
      cout << "ERROR: wrong task name" << endl;
      break;
    case ERR_DATE:
      cout << "ERROR: wrong date" << endl;
      break;
    case ERR_TIME:
      cout << "ERROR: wrong expected time" << endl;
  }
}

//Funcion introducir nombre de lista
bool nameList(Project toDoList, List &newlist){
	//return(true)-> lista existe , return(false)-> lista no existe
	do{
    	cout<<"Enter list name:";
		getline(cin,newlist.name);

    	if(newlist.name=="")
      		error(ERR_EMPTY);

	}while(newlist.name=="");

	//comprobar que el vector no esta vacio
	if(!(toDoList.lists.empty())){
		for(unsigned int i=0; i<toDoList.lists.size(); i++){
			//Comprobar que no hay ninguna lisrta igual a la que se quiere añadir
			if(newlist.name==toDoList.lists[i].name){
				return(true);
			}
		}
	}
	//vector vacio
	if(toDoList.lists.empty())
    	return(false);

	return(false);
}

bool nameTask(Project toDoList, Task &newtask){
	//return(true)-> tarea existe , return(false)-> tarea no existe
	cout<<"Enter task name:";
	getline(cin,newtask.name);

	//Existe una tarea con el mismo nombre que se quiere añadir
	for(unsigned int i=0; i<toDoList.lists.size(); i++){
		for(unsigned int j=0; j<toDoList.lists[i].tasks.size(); j++){
			if(newtask.name==toDoList.lists[i].tasks[j].name){
				return(true);
			}
		}
	}

	//Vector vacio, por tanto no existe ninguna tarea
	for(unsigned int i=0; i<toDoList.lists.size(); i++){
			if(toDoList.lists[i].tasks.empty())
				return(false);
	}
	return(false);
}

void showMainMenu(){
  cout << "1- Edit project" << endl
       << "2- Add list" << endl
       << "3- Delete list" << endl 
       << "4- Add task" << endl
       << "5- Delete task" << endl
       << "6- Toggle task" << endl
       << "7- Report" << endl
       << "q- Quit" << endl
       << "Option: ";
}

void editProject(Project &toDoList){
	while(toDoList.name==""){
    	cout<<"Enter project name:";
    	getline(cin,toDoList.name);

    if(toDoList.name=="") 
    	error(ERR_EMPTY);     
  } 
	
	cout<<"Enter project description:";
	getline(cin,toDoList.description); 
}

void addList(Project &toDoList){
	List newlist;

	if(nameList(toDoList,newlist))
		error(ERR_LIST_NAME);
	else
		toDoList.lists.push_back(newlist); //Añadir lista al final del vector
}

void deleteList(Project &toDoList){
	List newlist;

	if(nameList(toDoList,newlist)){
		if(!(toDoList.lists.empty())){
			for(unsigned int i=0; i<toDoList.lists.size(); i++){
				if(newlist.name==toDoList.lists[i].name)
					toDoList.lists[i].name.pop_back();//Eliminar lista del vector
				else
					error(ERR_LIST_NAME);//Si no encuentra un vector con el nombre introducido
			}
		}
	}
	else
		error(ERR_LIST_NAME);//Si el vector esta vacio el nombre de la lista no existe y tambien mostramos ERR_LIST_NAME
}

void addTask(Project &toDoList){
	List newlist;
	Task newtask;

	if(!(nameList(toDoList, newlist))){
		error(ERR_LIST_NAME);
		return;
	}
	
	nameTask(toDoList,newtask);

	char a,b;
	cout<<"Enter deadline:";
	cin>>newtask.deadline.day >> a >> newtask.deadline.month >> b >> newtask.deadline.year;

	//Si ocurre algo de esto la fecha no sera valida y la tarea no se creara
	//Si el año no está entre 2000 y 2100, si el mes no esta entre 1(enero) y 12 (diciembre), si los meses impares tienen mas 31 dias, si los meses pares no tienen 30 dias excepto febrero, si el año es bisiesto que febrero no tenga 29 dias y si el año no es bisiesto que febrero no tenga 28 dias 
	if((newtask.deadline.year < 2000 || newtask.deadline.year > 2100) || (newtask.deadline.month < 1 || newtask.deadline.month > 12) || (newtask.deadline.month%2 != 0 && newtask.deadline.day > 31) || (newtask.deadline.month%2 == 0 && newtask.deadline.day > 30) || (((((newtask.deadline.year%4 == 0 && newtask.deadline.year%100 == 0) && newtask.deadline.year%400 == 0) || (newtask.deadline.year%4 == 0 && newtask.deadline.year%100 != 0)) && newtask.deadline.month == 2) && newtask.deadline.day > 29) || (((((newtask.deadline.year%4 != 0 && newtask.deadline.year%100 != 0) && newtask.deadline.year%400 != 0) || (newtask.deadline.year%4 != 0 && newtask.deadline.year%100 == 0)) && newtask.deadline.month == 2) && newtask.deadline.day > 28)){
		error(ERR_DATE);
	    return;
	}

	cout<<"Enter expected time:";
	cin>>newtask.time;
	if(newtask.time<1||newtask.time>180){
	    error(ERR_TIME);
		return;
	}

	//Añadir nuevo registro Task en la lista correspondiente si la lista existe
	for(unsigned int i=0; i<toDoList.lists.size(); i++){
		if(newlist.name==toDoList.lists[i].name){
	  		toDoList.lists[i].tasks.push_back(newtask);
	  		newtask.isDone=false;
	  	}
	}
}

void deleteTask(Project &toDoList){
	List newlist;
	Task newtask;

	if(!(nameList(toDoList,newlist))){
		error(ERR_LIST_NAME);
		return;
	}

	if(!(nameTask(toDoList,newtask))){
		error(ERR_TASK_NAME);
		return;
	}

	//Eliminar la tarea de la lista correspondiente
	for(unsigned int i=0; i<toDoList.lists.size(); i++){
		for(unsigned int j=0; j<toDoList.lists[i].tasks.size(); j++){
			if(newtask.name==toDoList.lists[i].tasks[j].name){
				toDoList.lists[i].tasks[j].name.pop_back();
			}
		}
	}
}

void toggleTask(Project &toDoList){
	List newlist;
	Task newtask;

	if(!(nameList(toDoList,newlist))){
		error(ERR_LIST_NAME);
		return;
	}

	if(!(nameTask(toDoList,newtask))){
		error(ERR_TASK_NAME);
		return;
	}

	for(unsigned int i=0; i<toDoList.lists.size(); i++){
		for(unsigned int j=0; j<toDoList.lists[i].tasks.size(); j++){
			if(newtask.name==toDoList.lists[i].tasks[j].name){
				//repasa isDone
				cout<<toDoList.lists[i].tasks[j].isDone<<endl;
				cout<<"yes1"<<endl;
				if(toDoList.lists[i].tasks[j].isDone==false){
					toDoList.lists[i].tasks[j].isDone=true;
					cout<<"yes"<<endl;
				}
				else if(toDoList.lists[i].tasks[j].isDone==true){
					toDoList.lists[i].tasks[j].isDone=false;
					cout<<"no"<<endl;
				}
			
			}
		}
	}
}

void report(const Project &toDoList){
}

int main(){
  Project toDoList;
  toDoList.id=1;
  char option;

  
  do{
    showMainMenu();
    cin >> option;
    cin.get();
    
    switch(option){
      case '1': editProject(toDoList);
                break;
      case '2': addList(toDoList);
                break;
      case '3': deleteList(toDoList);
                break;
      case '4': addTask(toDoList);
                break;
      case '5': deleteTask(toDoList);
                break;
      case '6': toggleTask(toDoList);
                break;
      case '7': report(toDoList);
                break;
      case 'q': break;
      default: error(ERR_OPTION);
    }
  }while(option!='q');
  
  return 0;    
}
