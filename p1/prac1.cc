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

//Función introducir nombre de lista
bool nameList(Project toDoList, List &newList){
	//return(true)-> lista existe , return(false)-> lista no existe
	do{
    	cout<<"Enter list name: ";
		getline(cin,newList.name);

    	if(newList.name=="")
      		error(ERR_EMPTY);

	}while(newList.name=="");

	//comprobar que el vector no esta vacio
	if(!(toDoList.lists.empty())){
		for(unsigned int i=0; i<toDoList.lists.size(); i++){
			//Comprobar que no hay ninguna lista igual a la que se quiere añadir
			if(newList.name==toDoList.lists[i].name){
				return(true);
			}
		}
	}

	//vector vacio
	if(toDoList.lists.empty())
    	return(false);

	return(false);
}

//Función introducir nombre tarea
bool nameTask(Project toDoList, List &newList, Task &newTask){
	//return(true)-> tarea existe , return(false)-> tarea no existe
	cout<<"Enter task name: ";
	getline(cin,newTask.name);

	//Existe una tarea con el mismo nombre que se quiere añadir
	for(unsigned int i=0; i<toDoList.lists.size(); i++){
		for(unsigned int j=0; j<toDoList.lists[i].tasks.size(); j++){
			if(newList.name==toDoList.lists[i].name && newTask.name==toDoList.lists[i].tasks[j].name){
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

//Función comprobar si la fecha es válida
bool checkDate(Project toDoList, Task &newTask){
	//return(true)-> fecha válida , return(false)->fecha no válida

	//Si ocurre algo de esto la fecha no sera valida y la tarea no se creara la tarea
	//Si el año no está entre 2000 y 2100, si el mes no esta entre 1(enero) y 12(diciembre), si los meses impares tienen mas de 31 dias, si los meses pares no tienen 30 dias excepto febrero
	if((newTask.deadline.year < 2000 || newTask.deadline.year > 2100) || (newTask.deadline.month < 1 || newTask.deadline.month > 12))
		return(false);

	//Si el mes es febrero para comprobar años bisiestos
	if(newTask.deadline.month == 2){
		//Si el año es bisiesto 
		if((newTask.deadline.year%4 == 0 && newTask.deadline.year%100 == 0 && newTask.deadline.year%400 == 0) || (newTask.deadline.year%4 == 0 && newTask.deadline.year%100 != 0)){
			//Tenga 29 dias
			if(newTask.deadline.day > 29 || newTask.deadline.day < 1)
			    return(false);
		}

		//Si el año no es bisiesto
		else{
			//Tenga 28 dias
			if(newTask.deadline.day > 28 || newTask.deadline.day < 1)
			    return(false);
		}
	}

	else if(newTask.deadline.month == 4 || newTask.deadline.month == 6 || newTask.deadline.month == 9 || newTask.deadline.month == 11 ){
		if(newTask.deadline.day > 30 || newTask.deadline.day < 1)
			return(false);
	}

	else{
		if(newTask.deadline.day > 31 || newTask.deadline.day < 1)
			return(false);
	}

	return(true);
}

void highestPriority(const Project &toDoList, int &oldDay, int &oldMonth, int &oldYear, string &oldTask){

	for(unsigned int i=0; i<toDoList.lists.size(); i++){//Recorrer vector de listas
		for(unsigned int j=0; j<toDoList.lists[i].tasks.size(); j++){//Recorrer vector de tareas
			if(toDoList.lists[i].tasks[j].isDone==false){//Si la tarea no esta completada
				//Y si el año es mayor que el anterior
				if((oldYear>toDoList.lists[i].tasks[j].deadline.year) 
					//Si el año es igual, pero el mes es mayor que el anterio
					|| ((oldYear==toDoList.lists[i].tasks[j].deadline.year) && (oldMonth>toDoList.lists[i].tasks[j].deadline.month))
						//Si el año y el mes son iguales pero el dia es mayor 
						|| ((oldYear==toDoList.lists[i].tasks[j].deadline.year) && (oldMonth>toDoList.lists[i].tasks[j].deadline.month) && (oldDay>toDoList.lists[i].tasks[j].deadline.day))){

							//Guardar valores para comprobar con la siguiente tarea
							oldYear=toDoList.lists[i].tasks[j].deadline.year;
							oldMonth=toDoList.lists[i].tasks[j].deadline.month;
							oldDay=toDoList.lists[i].tasks[j].deadline.day;
							oldTask=toDoList.lists[i].tasks[j].name;
				}
			}
		}
	}
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
	do{
    	cout<<"Enter project name: ";
    	getline(cin,toDoList.name);

    	if(toDoList.name=="") 
    		error(ERR_EMPTY);  

	}while(toDoList.name=="");
	
	cout<<"Enter project description: ";
	getline(cin,toDoList.description); 
	}

void addList(Project &toDoList){
	List newList;

	if(nameList(toDoList,newList))//comprobar que la lista existe para dar error
		error(ERR_LIST_NAME);
	else
		toDoList.lists.push_back(newList); //Añadir lista al final del vector si la lista no existe 
}

void deleteList(Project &toDoList){
	List newList;

	if(nameList(toDoList,newList)){//Comprobar que la lista existe
		if(!(toDoList.lists.empty())){//Comprobar que el vector no esta vacio
			for(unsigned int i=0; i<toDoList.lists.size(); i++){
				if(newList.name==toDoList.lists[i].name)
					toDoList.lists.erase(toDoList.lists.begin()+i);//Eliminar lista del vector
			}
		}
	}
	else
		error(ERR_LIST_NAME);//Si el vector esta vacio el nombre de la lista no existe y tambien mostramos ERR_LIST_NAME
}

void addTask(Project &toDoList){
	List newList;
	Task newTask;

	if(!(nameList(toDoList, newList))){//Comprobar que la lista no existe para dar error y volver al menu
		error(ERR_LIST_NAME);
		return;
	}
	
	nameTask(toDoList, newList ,newTask);

	char a,b;//variables para separar dia/mes/año
	cout<<"Enter deadline: ";
	cin>>newTask.deadline.day >> a >> newTask.deadline.month >> b >> newTask.deadline.year;

	if(!(checkDate(toDoList,newTask))){//Comprobar si la fecha es valida y si no dar error y volver al menu
		error(ERR_DATE);
		return;
	}

	cout<<"Enter expected time: ";
	cin>>newTask.time;
	if(newTask.time<1 || newTask.time>180){//Comprobar que el tiempo no esta entre 1 y 180 minutos, dar error y volver al menu
	    error(ERR_TIME);
		return;
	}

	for(unsigned int i=0; i<toDoList.lists.size(); i++){
		if(newList.name==toDoList.lists[i].name){
			newTask.isDone=false;//Marcar como tarea no echa
	  		toDoList.lists[i].tasks.push_back(newTask);//Añadir nuevo registro Task en la lista correspondiente si la lista existe
	  	}
	}
}

void deleteTask(Project &toDoList){
	List newList;
	Task newTask;

	//Comprobar si la lista introducida no existe para dar error y volver al menu
	if(!(nameList(toDoList,newList))){
		error(ERR_LIST_NAME);
		return;
	}

	//Comprobar si la tarea introducida no existe para dar error y volver al menu
	if(!(nameTask(toDoList, newList, newTask))){
		error(ERR_TASK_NAME);
		return;
	}

	for(unsigned int i=0; i<toDoList.lists.size(); i++){
		for(unsigned int j=0; j<toDoList.lists[i].tasks.size(); j++){
			if(newList.name==toDoList.lists[i].name && newTask.name==toDoList.lists[i].tasks[j].name){
				toDoList.lists[i].tasks.erase(toDoList.lists[i].tasks.begin()+j);//Eliminar la tarea de la lista correspondiente
				j--;
			}
		}
	}
}

void toggleTask(Project &toDoList){
	List newList;
	Task newTask;

	if(!(nameList(toDoList,newList))){
		error(ERR_LIST_NAME);
		return;
	}

	if(!(nameTask(toDoList, newList, newTask))){
		error(ERR_TASK_NAME);
		return;
	}

	for(unsigned int i=0; i<toDoList.lists.size(); i++){
		for(unsigned int j=0; j<toDoList.lists[i].tasks.size(); j++){
			if(newList.name==toDoList.lists[i].name && newTask.name==toDoList.lists[i].tasks[j].name){
				//Si la tarea no esta echa cambiarla a echa
				if(toDoList.lists[i].tasks[j].isDone==false){
					toDoList.lists[i].tasks[j].isDone=true;
				}
				//Si la tarea estaba echa cambaiarla a no echa
				else if(toDoList.lists[i].tasks[j].isDone==true){
					toDoList.lists[i].tasks[j].isDone=false;
				}
			}
		}
	}
}

void report(const Project &toDoList){
	char finish;
	int  done=0, left=0, totalDone=0, totalLeft=0, oldDay=100, oldMonth=100, oldYear=3000;
	string oldTask;

	cout<<"Name: "<< toDoList.name << endl;
	if(toDoList.description!="")
		cout<<"Description: "<<toDoList.description<<""<<endl;

	for(unsigned int i=0; i<toDoList.lists.size(); i++){//Recorrer vector de listas
		cout<<toDoList.lists[i].name<<endl;

		if(toDoList.lists[i].tasks.empty())//Si el vector tarea esta vacio no hay ninguna tarea pendiente
			oldTask="";

		//Recorrer vector de tareas no echas
		for(unsigned int j=0; j<toDoList.lists[i].tasks.size(); j++){//Recorrer vector de tareas
			if(toDoList.lists[i].tasks[j].isDone==false){//Si la tarea no esta completada

				finish=' ';
				left++;//Contador de tareas pendientes
				totalLeft=totalLeft+toDoList.lists[i].tasks[j].time;//Contador del tiempo de las tareas pendientes

				cout<<"["<<finish<<"]";//Marcar si la tarea esta echa o no
				cout<<" ("<<toDoList.lists[i].tasks[j].time<<") ";//Tiempo tarea
				cout<<toDoList.lists[i].tasks[j].deadline.year<<"-"<<toDoList.lists[i].tasks[j].deadline.month<<"-"<<toDoList.lists[i].tasks[j].deadline.day<<" : ";//Fecha tarea		
				if(toDoList.lists[i].tasks[j].name!="")
					cout<<toDoList.lists[i].tasks[j].name;//Nombre si lo hay
				cout<<endl;
			}
		}

		//Recorrer vector de tareas echas
		for(unsigned int j=0; j<toDoList.lists[i].tasks.size(); j++){//Recorrer vector de tareas
			if(toDoList.lists[i].tasks[j].isDone==true){//Si la tarea esta completada

				finish='X';
				done++;//Contador de tareas echas
				totalDone=totalDone+toDoList.lists[i].tasks[j].time;//Contador del tiempo de las tareas echas

				cout<<"["<<finish<<"]";//Marcar si la tarea esta echa o no
				cout<<" ("<<toDoList.lists[i].tasks[j].time<<") ";//Tiempo tarea
				cout<<toDoList.lists[i].tasks[j].deadline.year<<"-"<<toDoList.lists[i].tasks[j].deadline.month<<"-"<<toDoList.lists[i].tasks[j].deadline.day<<" : ";//Fecha tarea	
				
				if(toDoList.lists[i].tasks[j].name!="")
					cout<<toDoList.lists[i].tasks[j].name;//Nombre si lo hay
				
				cout<<endl;
			}
		}	
	}

	cout<<"Total left: "<<left<<" ("<<totalLeft<<" minutes)"<<endl;//Total de las tareas pendientes
	cout<<"Total done: "<<done<<" ("<<totalDone<<" minutes)"<<endl;//Total de las tareas echas 

	highestPriority (toDoList, oldDay, oldMonth, oldYear, oldTask);

	if(oldTask!="")
	cout<<"Highest priority: "<<oldTask<<" ("<<oldYear<<"-"<<oldMonth<<"-"<<oldDay<<")"<<endl;//Mostrar la tarea mas antigua y pendiente de hacer
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
