//50507753Y GRIMALDOS LOPEZ, MARTA

#include <iostream>
#include <vector>
#include <cstdlib>
#include<fstream>
#include <cstring>

using namespace std;

const int KMAXNAME=20;
const int KMAXDESC=40;

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

struct BinTask{
	char name[KMAXNAME];
	Date deadline;
	bool isDone;
	int time;
};

struct List{
  string name;
  vector<Task> tasks;
};

struct BinList{
	char name[KMAXNAME];
	unsigned numTasks;
};

struct Project{
  int id;
  string name;
  string description;
  vector<List> lists;
};

struct BinProject{
	char name[KMAXNAME];
	char description[KMAXDESC];
	unsigned numLists;
};

struct ToDo{
	int nextId;
	string name;
	vector<Project> projects;
};

struct BinToDo{
	char name[KMAXNAME];
	unsigned numProjects;
};

enum Error{
  ERR_OPTION,
  ERR_EMPTY,
  ERR_LIST_NAME,
  ERR_TASK_NAME,
  ERR_DATE,
  ERR_TIME,
  ERR_ID,
  ERR_PROJECT_NAME,
  ERR_FILE,
  ERR_ARGS
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
      break;
    case ERR_ID:
      cout << "ERROR: wrong project id" << endl;
      break;
    case ERR_PROJECT_NAME:
      cout << "ERROR: wrong project name" << endl;
      break;
    case ERR_FILE:
      cout << "ERROR: cannot open file" << endl;
      break;
    case ERR_ARGS:
      cout << "ERROR: wrong arguments" << endl;
  }
}

void showMainMenu() {
  cout << "1- Project menu" << endl
       << "2- Add project" << endl
       << "3- Delete project" << endl 
       << "4- Import projects" << endl
       << "5- Export projects" << endl
       << "6- Load data" << endl
       << "7- Save data" << endl
       << "8- Summary" << endl
       << "q- Quit" << endl
       << "Option: ";	
}
void showMainProjectMenu(){
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

//Funcion comprobar id
bool checkId(ToDo &toDoProject, int &id){
	//return(true)-> exisiste un proyecto con ese id, return(false)-> id del proyecto no existe
	Project toDoList;

  	cout<<"Enter project id: ";
  	cin>>id;

  	//comprobar que el vector no esta vacio
	if(!(toDoProject.projects.empty())){
		for(unsigned int i=0; i<toDoProject.projects.size(); i++){
			//Comprobar que hay algun proyecto con ese id
			if(id==toDoProject.projects[i].id){
				id=i;//numero de id que coincide +1;
				return(true);
			}
		}
	}

	return(false);
}

void projectMenu(ToDo &toDoProject){
	Project toDoList;
  	toDoList.id=1;
  	char option;
  	int id;

	if(checkId(toDoProject, id)){
		do{
			showMainProjectMenu();
			cin>>option;
			cin.get();
		    
		    switch(option){
			    case '1': editProject(toDoProject.projects[id]);
			                break;
			    case '2': addList(toDoProject.projects[id]);
			                break;
			    case '3': deleteList(toDoProject.projects[id]);
			                break;
			    case '4': addTask(toDoProject.projects[id]);
			                break;
			    case '5': deleteTask(toDoProject.projects[id]);
			                break;
			    case '6': toggleTask(toDoProject.projects[id]);
			                break;
			    case '7': report(toDoProject.projects[id]);
			                break;
			    case 'b': break;
			    default: error(ERR_OPTION);
		   	}
		}while(option!='b');
	}
	else{
		error(ERR_ID);
	}
}

void addProject(ToDo &toDoProject){
	Project toDoList;
	do{
    	cout<<"Enter project name:";
		getline(cin,toDoList.name);

    	if(toDoList.name=="")
      		error(ERR_EMPTY);

	}while(toDoList.name=="");//Mientras no introduzca un nombre

	//comprobar que el vector no esta vacio
	if(!(toDoProject.projects.empty())){
		for(unsigned int i=0; i<toDoProject.projects.size(); i++){
			//Comprobar que no hay ninguna lista igual a la que se quiere añadir
			if(toDoList.name==toDoProject.projects[i].name){
				error(ERR_PROJECT_NAME);
				return;
			}
		}
	}
	cout<<"Enter project description: ";
	getline(cin,toDoList.description); 

	toDoList.id=toDoProject.nextId;
	toDoProject.nextId++;

	toDoProject.projects.push_back(toDoList);//Añade nuevo proyecto al vector projects
}

void deleteProject(ToDo &toDoProject){
	Project toDoList;
	int id;

	if(checkId(toDoProject, id))//Si el id introducido es correcto
		toDoProject.projects.erase(toDoProject.projects.begin()+id);//Se borra el proyecto con ese id
	else
		error(ERR_ID);
}

void importProjects(ToDo &toDoProject, string nameFile){

	if(nameFile==""){
		cout << "Enter filename: ";
		cin >> nameFile;
	}

	ifstream fl(nameFile);//El fichero se abrira para escribir
	if(fl.is_open()){//Se abre el fichero 

		char start=' ';//Caracter que se esta leyendo
		string line, arrayTask;//line: linea que se esta leyendo, arrayTask: cadena de caracteres para el nombre de una nueva tarea
		int num;

		while(fl >> start){//Leer caracter a caracter

			if(start == '<'){
				fl >> start;
				if(start == '#'){//Si el caracter es # hay un proyecto

					Project toDoList;
					getline(fl,line);//Leer una linea
					bool coincide=false;//Inicializacion del boleeano para comprobar el nombre del proyecto 

					if(!(toDoProject.projects.empty())){//comprobar que el vector no esta vacio
						for(unsigned int i=0; i<toDoProject.projects.size(); i++){//Recorrer vector de proyectos
							if(line==toDoProject.projects[i].name){//Si hay alguna lista igual a la que se quiere añadir
								error(ERR_PROJECT_NAME);//Error de nombre del proyecto
								coincide=true;
							}
						}
					}
					if(coincide==false){//Si no coincide el nombre del proyecto
						toDoList.name=line;//Nombre del proyecto 
						toDoList.id=toDoProject.nextId;//Id del proyecto 
						toDoProject.nextId++;//Incremento del id para el siguiente 

						fl >> start;//Leer siguiente caracter
						if(start == '*'){//Si el caracter es * hay descripcion
							getline(fl,line);//Leer linea
							toDoList.description=line;//Descripcion del proyecto

							fl >> start;
						}

						while(start == '@'){//Mientras el caracter sea @ hay una lista
							List newList;
							getline(fl,line);
							newList.name=line;//Nombre de la lista
							fl >> start;
							
							while(start != '@' && start != '>'){//Mientras no haya una lista (@) o un final de datos(>) hay una tarea
								Task newTask;
								while(start != '|'){//Mientras no hay |
									arrayTask.push_back(start);//Se añade el nuevo caracter al array
									fl.get(start);//usamos .get para leer los blancos y leemos todo el nombre de la tarea hasta encontrar |
							    }

							    newTask.name=arrayTask;//El array creado es el nombre de la tarea

								fl >> num;
								newTask.deadline.day=num;
								fl >> start >> num;
								newTask.deadline.month=num;
								fl >> start >> num;
								newTask.deadline.year=num;

								if(!(checkDate(toDoList,newTask))){//Comprobar si la fecha es valida
									error(ERR_DATE);
									arrayTask.erase();
									getline(fl,line);//Seguir leyendo tareas
									fl>>start;
								} else if(checkDate(toDoList,newTask)){
									fl >> start >> start;//Lee el caracter '|' y el de si la tarea esta echa o no
									if(start == 'F')
										newTask.isDone=false;
									else if( start == 'T')
										newTask.isDone=true;

									fl >> start >> num;//Lee el caracter '|' y el tiempo 
									newTask.time=num;
									if(newTask.time<1 || newTask.time>180){//Comprobar que el tiempo no esta entre 1 y 180 minutos, dar error 
									    error(ERR_TIME);
									    arrayTask.erase();
									    getline(fl,line);//Seguir leyendo tareas
									    fl>>start;
									}else{//Si todo es correcto
										newList.tasks.push_back(newTask);//Se añade la tarea al vector tasks
										arrayTask.erase();//Se restea el array para la proxima tarea
										fl >> start;
									}
								}
						    }
							toDoList.lists.push_back(newList);//Añadir lista al vector lists
						}
						toDoProject.projects.push_back(toDoList);//Añadir proyecto al vector projects
					}
				}
			}
		}
		
		fl.close();//Se cierra el fichero
	}
	else{//Error de apertura
		error(ERR_FILE);
	}
}

void exportProjects(ToDo &toDoProject){
	char save;//Variable S/N
	int id;
	string nameFile;//Variable nombre del fichero
	
	do{//Mientras no se introduzca Y/N mayuscula o minuscula
		cout<<"Save all projects [Y/N]?:";
		cin>>save;
	}while(save!='Y' && save!='y' && save!='N' && save!='n');

	if(save=='N' || save=='n'){//Si el usuario elige no guardar todos los proyectos
		if(!(checkId(toDoProject, id))){//Comprobacion de que el id introducido existe
			error(ERR_ID);
			return;
		}
	}

	cout<<"Enter filename:";
	cin>>nameFile;

	ofstream fe(nameFile,ios::out);//Se borra el contenido que hubiera en el fichero que vamos a abrir para escribir
	if(fe.is_open()){//Se abre el fichero 

		//Recorrer vector de proyectos
		for(unsigned int i = 0; i < toDoProject.projects.size(); i++){

			//Si se elige anteriromente la opcion no el proyecto será el id elegido
			if(save=='N' || save=='n')
				i=id;

			fe << "<" << endl;//Comienzo de los datos del proyecto
			fe << "#" << toDoProject.projects[i].name << endl;//Nombre del proyecto
			if( toDoProject.projects[i].description != ""){//Si hay descripcion 
				fe << "*" << toDoProject.projects[i].description <<endl;
			}

			//Recorrer vector de listas 
			for (unsigned int j = 0; j < toDoProject.projects[i].lists.size(); j++){
				fe << "@" << toDoProject.projects[i].lists[j].name << endl;//Nombre de la lista

				//Recorrer vector de tareas
				for (unsigned int k = 0; k < toDoProject.projects[i].lists[j].tasks.size(); k++){

					fe << toDoProject.projects[i].lists[j].tasks[k].name;//Nombre de l tarea
					fe << "|" << toDoProject.projects[i].lists[j].tasks[k].deadline.day << "/" << toDoProject.projects[i].lists[j].tasks[k].deadline.month << "/" << toDoProject.projects[i].lists[j].tasks[k].deadline.year;//Fecha de la tarea
					fe << "|" ;//Separacion

					if (toDoProject.projects[i].lists[j].tasks[k].isDone == true)//Si la tarea esta echa escribir T
						fe << "T";
					else//Si la tarea no esta echa escribir F
						fe<< "F";

					fe << "|" << toDoProject.projects[i].lists[j].tasks[k].time << endl;//Tiempo de la tarea 		
				}
			}

			fe << ">" << endl;//Final de los datos del proyecto

			if(save=='N' || save=='n')
				break;//Si se elige no mostrar todos los proyectos salir del bucle para no mostrar otra vez el mismo proyecto 
		}

		fe.close();//Cierra el fichero
	}else
		error(ERR_FILE);//Error al abrir el fichero
}

void loadData(ToDo &toDoProject, string nameFile){
	BinToDo toDoBinProject;
	BinProject newBinProject;
	Project toDoList;
	BinList newBinList;
	List newList;
	BinTask newBinTask;
	Task newTask;
	int numT, numL, numP;
	char save='y';//Variable S/N

	if(nameFile==""){
		cout<<"Enter filename: ";
		cin>>nameFile;
		save=' ';		
	}

	ifstream fbl(nameFile, ios::binary);
	if(fbl.is_open()){//Se abre el fichero 

		if(save==' '){
			do{//Mientras no se introduzca Y/N mayuscula o minuscula
				cout<<"Confirm [Y/N]?: ";
				cin>>save;
			}while(save!='Y' && save!='y' && save!='N' && save!='n');
		}

		if(save=='Y' || save=='y'){

			if(!(toDoProject.projects.empty())){//Comprobar que el vector no esta vacio
				toDoProject.projects.clear();//Eliminar projectos del vector
			}
		
			toDoProject.nextId=1;//Se inicializa el id a 1 otra vez	

			while(fbl.read((char *)&toDoBinProject, sizeof(BinToDo))){//Lee el registro BinToDo 
				toDoProject.name = toDoBinProject.name;
				numP = toDoBinProject.numProjects;

				if(numP > 0){//Si el numero de projectos es mayor de 0 
					while(fbl.read((char *)&newBinProject, sizeof(BinProject))){//Lee el registro de projectos
						toDoList.lists.clear();//Limpia el vector de lista en cada proyecto nuevo
						toDoList.name = newBinProject.name;
						toDoList.description = newBinProject.description;
						toDoList.id = toDoProject.nextId;
						toDoProject.nextId++;
						numL = newBinProject.numLists;
						numP--;//El numero de proyectos decrementa cada vez leido uno
						
						if(numL > 0){//Si el numero de listas es mayor de 0
							while(fbl.read((char *)&newBinList, sizeof(BinList))){//Lee el registro de listas
								newList.tasks.clear();//Limpia el vector de tareas en cada lista nueva
								newList.name=newBinList.name;
								numT = newBinList.numTasks;
								numL--;//El numero de listas decrementa cada vez leida una

								if(numT > 0){//Si el numero de tareas es mayor de 0
									while(fbl.read((char *)&newBinTask, sizeof(BinTask))){//Lee el registro de tareas
										newTask.name = newBinTask.name;
										newTask.deadline = newBinTask.deadline;
										newTask.isDone = newBinTask.isDone;
										newTask.time = newBinTask.time;

										numT--;//El numero de tareas decrementa cada vez leida una

										newList.tasks.push_back(newTask);//Se añade la tarea al vector de tasks

										if(numT == 0)//Si no quedan tareas
											break;//Se termina el bucle de leer las tareas
									}
								}

								toDoList.lists.push_back(newList);//Se añade la lista al vector de lists

								if(numL == 0)//Si no quedan listas
									break;//Se termina el bucle de leer las listas
							}
						}

						toDoProject.projects.push_back(toDoList);//Se añade el proyecto al vector de projects


						if(numP == 0)//Si no quedan proyectos
							break;//Se termina el bucle de leer los proyectos
					}
				}
			}
		}

		if(save=='N' || save=='n'){
			fbl.close();//Cierra el fichero
		}

		fbl.close();//Cierra el fichero
	}else
		error(ERR_FILE);//Error al abrir el fichero
}

void saveData(ToDo &toDoProject){

	BinToDo toDoBinProject;
	BinProject newBinProject;
	Project toDoList;
	BinList newBinList;
	List newList;
	BinTask newBinTask;
	Task newTask;
	string nameFile;

	cout<<"Enter filename:";
	cin>>nameFile;

	ofstream fbe(nameFile,ios::out | ios::binary);//Se borra el contenido que hubiera en el fichero binario que vamos a abrir para escribir
	if(fbe.is_open()){//Se abre el fichero 

		//Con strcpy() copia la informacion a una cadena de caracteres y .c_str() para para un string a cadena de caracteres
		strncpy(toDoBinProject.name, toDoProject.name.c_str(), KMAXNAME-1);//Almacena el nombre del proyecto
		toDoBinProject.name[KMAXNAME-1]='\0';
		toDoBinProject.numProjects = toDoProject.projects.size();//El tamaño del vector proyectos es el numero de proyectos
		fbe.write((const char*)&toDoBinProject, sizeof(BinToDo));//Escribimos la informacion en el fichero

		for (unsigned int i = 0; i < toDoProject.projects.size(); i++){//Recorre el vector de proyectos
			toDoList = toDoProject.projects[i];

			strncpy(newBinProject.name, toDoList.name.c_str(), KMAXNAME-1);
			newBinProject.name[KMAXNAME-1]='\0';
			strncpy(newBinProject.description, toDoList.description.c_str(), KMAXDESC-1);
			newBinProject.description[KMAXDESC-1]='\0';
			newBinProject.numLists  = toDoProject.projects[i].lists.size();
			fbe.write((const char *)&newBinProject,sizeof(BinProject));

			for (unsigned int j = 0; j < toDoProject.projects[i].lists.size(); j++){//Recorre el vector de listas
				newList = toDoProject.projects[i].lists[j];

				strncpy(newBinList.name, newList.name.c_str(), KMAXNAME-1);
				newBinList.name[KMAXNAME-1]='\0';
				newBinList.numTasks = toDoProject.projects[i].lists[j].tasks.size();
				fbe.write((const char *)&newBinList,sizeof(BinList));

				for (unsigned int k = 0; k < toDoProject.projects[i].lists[j].tasks.size(); k++){//Recorre el vector de tareas
					newTask = toDoProject.projects[i].lists[j].tasks[k];

					strncpy(newBinTask.name, newTask.name.c_str(), KMAXNAME-1);
					newBinTask.name[KMAXNAME-1]='\0';
					newBinTask.deadline = newTask.deadline;
					newBinTask.isDone = newTask.isDone;
					newBinTask.time = newTask.time;
					fbe.write((const char *)&newBinTask,sizeof(BinTask));
				}
			}
		}

		fbe.close();//Cierra el fichero
	}else
		error(ERR_FILE);//Error al abrir el fichero
}

void summary(ToDo &toDoProject){

	for(unsigned int i=0; i<toDoProject.projects.size(); i++){

		int  notDone=0, total=0;
		cout << "(" << toDoProject.projects[i].id << ") " << toDoProject.projects[i].name;
		
		for(unsigned int j=0; j<toDoProject.projects[i].lists.size(); j++){//Recorrer vector de listas
			for(unsigned int k=0; k<toDoProject.projects[i].lists[j].tasks.size(); k++){//Recorrer vector de tareas
				total++;

				if(toDoProject.projects[i].lists[j].tasks[k].isDone==true)//Si la tarea no esta completada
					notDone++;//Contador de tareas pendientes
			}
		}

		cout<<" ["<<notDone<<"/"<<total<<"] "<<endl;
	}
}

int main(int argc, char *argv[]){
	ToDo toDoProject;
	toDoProject.name="My ToDo list";
	toDoProject.nextId=1;
	char option;
	bool argument=false;
	string nameFile;

	if(argc==1)//Si hay un argumento sera el ejegutable
		argument=true;
	else if(argc==3){
		if(strcmp(argv[1],"-i") == 0){//Si el segundo argumento es -i
			argument=true;
			string nameFile(argv[2]);//El siguiente argumento es el nombre del fichero de texto
			importProjects(toDoProject, nameFile);//Se importa la informacion
		}else if(strcmp(argv[1],"-l") == 0){//Si el segundo argumento es -l
			argument=true;
			string nameFile(argv[2]);
			loadData(toDoProject, nameFile);//Se carga la informacion del fichero binario
		}else
			error(ERR_ARGS);
	}
	else if(argc==5){
		if(strcmp(argv[1],"-i") == 0 && strcmp(argv[3],"-l") == 0){//Si se introduce -i namefile2 -l namefile 
			string nameFile(argv[4]);
			string nameFile2(argv[2]);

			//Se abren ambos ficheros
			ifstream fbl(nameFile, ios::binary);
			ifstream fl(nameFile2);
			if(fbl.is_open() && fl.is_open()){//Si se abren
				argument=true;
				fbl.close();
				fl.close();
				loadData(toDoProject, nameFile);//Primero se carga la informacion del fichero bineario
				importProjects(toDoProject, nameFile2);//Despues se importa la informacion del fichero de texto
			}else//Si no se abre algun fichero o ambos
				error(ERR_FILE);//Error al abrir el fichero
		}			
		else if(strcmp(argv[1],"-l") == 0 && strcmp(argv[3],"-i") == 0){//Si se introduce -l namefile -i namefile2 
			string nameFile(argv[2]);
			string nameFile2(argv[4]);

			//Se abren ambos ficheros
			ifstream fbl(nameFile, ios::binary);
			ifstream fl(nameFile2);
			if(fbl.is_open() && fl.is_open()){//Si se abren
				argument=true;
				fbl.close();
				fl.close();
				loadData(toDoProject, nameFile);//Primero se carga la informacion del fichero bineario
				importProjects(toDoProject, nameFile2);//Despues se importa la informacion del fichero de texto
			}else//Si no se abre algun fichero o ambos
				error(ERR_FILE);//Error al abrir el fichero
		}else 
			error(ERR_ARGS);
	}
	else
		error(ERR_ARGS);

	if(argument==true){
		do{
			showMainMenu();
			cin >> option;
			cin.get();

			switch(option){
				case '1': projectMenu(toDoProject);
				        break;
				case '2': addProject(toDoProject);
				        break;
				case '3': deleteProject(toDoProject);
				        break;
				case '4': importProjects(toDoProject, nameFile);
				        break;
				case '5': exportProjects(toDoProject);
				        break;
				case '6': loadData(toDoProject, nameFile);
				        break;
				case '7': saveData(toDoProject);
				        break;
				case '8': summary(toDoProject);
				        break;
				case 'q': break;
				default: error(ERR_OPTION);
			}
		}while(option!='q');

		return 0;    
	}
}
