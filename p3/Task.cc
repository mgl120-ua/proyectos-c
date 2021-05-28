#include "Task.h"
#include "Util.h"

Task::Task(string name){
	this->name=name;
	time=1;
	deadline.day=1;
	deadline.month=1;
	deadline.year=2000;
	isDone=false;
}

//Función comprobar si la fecha es válida
bool Task::checkDate(Date deadline){
	//cout<<"Prueba"<<deadline.day<<"-"<<deadline.month<<"-"<<deadline.year<<endl;
	//return(true)-> fecha válida , return(false)->fecha no válida

	//Si ocurre algo de esto la fecha no sera valida y la tarea no se creara la tarea
	//Si el año no está entre 2000 y 2100, si el mes no esta entre 1(enero) y 12(diciembre), si los meses impares tienen mas de 31 dias, si los meses pares no tienen 30 dias excepto febrero
	if((deadline.year < 2000 || deadline.year > 2100) || (deadline.month < 1 || deadline.month > 12))
		return(false);

	//Si el mes es febrero para comprobar años bisiestos
	if(deadline.month == 2){
		//Si el año es bisiesto 
		if((deadline.year%4 == 0 && deadline.year%100 == 0 && deadline.year%400 == 0) || (deadline.year%4 == 0 && deadline.year%100 != 0)){
			//Tenga 29 dias
			if(deadline.day > 29 || deadline.day < 1)
			    return(false);
		}

		//Si el año no es bisiesto
		else{
			//Tenga 28 dias
			if(deadline.day > 28 || deadline.day < 1)
			    return(false);
		}
	}

	else if(deadline.month == 4 || deadline.month == 6 || deadline.month == 9 || deadline.month == 11 ){
		if(deadline.day > 30 || deadline.day < 1)
			return(false);
	}

	else{
		if(deadline.day > 31 || deadline.day < 1)
			return(false);
	}

	return(true);
}

bool Task::setDeadline(string deadline){
    int i=0;
    Date newDeadline;
    //int dia,mes,ano;
    for(size_t p=0, q=0; p!=deadline.npos; p=q){
        if(i==0)
            newDeadline.day=stoi(deadline.substr(p+(p!=0),(q=deadline.find('/', p+1))-p-(p!=0)));
        
        if(i==1)
            newDeadline.month=stoi(deadline.substr(p+(p!=0),(q=deadline.find('/', p+1))-p-(p!=0)));

        if(i==2)
            newDeadline.year=stoi(deadline.substr(p+(p!=0),(q=deadline.find('/', p+1))-p-(p!=0)));
        i++;   
    }

	if(checkDate(newDeadline)==false){//Comprobar si la fecha es valida y si no dar error y volver al menu
		Util::error(ERR_DATE);
		return(false);
	}
	else{
		this->deadline.day=newDeadline.day;
		this->deadline.month=newDeadline.month;
		this->deadline.year=newDeadline.year;
		return(true);
	}

}

bool Task::setTime(int time){

	if(time<1 || time>180){//Comprobar que el tiempo no esta entre 1 y 180 minutos, dar error y volver al menu
	    Util::error(ERR_TIME);
		return (false);
	}

	this->time=time;
	return(true);
}

void Task::toggle(){
	//Si la tarea no esta echa cambiarla a echa
	if(isDone==false){
		isDone=true;
	}
	//Si la tarea estaba echa cambaiarla a no echa
	else if(isDone==true){
		isDone=false;
	}
}

ostream& operator<<(ostream &os,Task &t){
	char finish;
	
	if(t.isDone==false){//Si la tarea no esta completada

		finish=' ';
		os<<"["<<finish<<"]";//Marcar si la tarea esta echa o no
		os<<" ("<<t.time<<") ";//Tiempo tarea
		os<<t.deadline.year<<"-"<<t.deadline.month<<"-"<<t.deadline.day<<" : ";//Fecha tarea		
		if(t.name!="")
			os<<t.name;//Nombre si lo hay
		os<<endl;
	}
	else if(t.isDone==true){//Si la tarea esta completada

		finish='X';
		os<<"["<<finish<<"]";//Marcar si la tarea esta echa o no
		os<<" ("<<t.time<<") ";//Tiempo tarea
		os<<t.deadline.year<<"-"<<t.deadline.month<<"-"<<t.deadline.day<<" : ";//Fecha tarea	
		
		if(t.name!="")
			os<<t.name;//Nombre si lo hay
		os<<endl;
	}
	return os;
}