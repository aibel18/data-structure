#include "AnalizadorSintactico.h"

//analiza la la lista enviada
int AnalizadorSintactico::analiza(Nodo *&temp){

	Nodo *res = temp;
	
	if(insertar(temp)){
		sacarComillas(res);
		return 1;
	}

	else if(seleccionar(temp)){
		sacarComillas(res);
		return 2;
	}
	
	else if(crear(temp))
		return 3;

	else
		return 0;
}

//comprueba que exista un campo de identificadores
bool AnalizadorSintactico::campos(Nodo *&temp){

	Nodo* respaldo = temp;

	if(!temp->informacion.compare("*")){
		temp = temp->siguiente;
		return true;
	}
	while(temp != 0 && temp->token == IDE ){

		temp = temp->siguiente;
		if(temp !=0 && !temp->informacion.compare(","))
			temp = temp->siguiente;
		else
			return true;
	}
	temp = respaldo;
	return false;
}
//comprueba que exista un campo de identificadores dentro de un parentesis
bool AnalizadorSintactico::camposP(Nodo *&temp){

	Nodo* respaldo = temp;

	if(temp != 0 && !temp->informacion.compare("(")){
		temp = temp->siguiente;

		if(campos(temp) && temp !=0 && !temp->informacion.compare(")"))
			return true;
	}
	temp = respaldo;
	return false;
}
//comprueba que exista un campo de variables
bool AnalizadorSintactico::camposArgumentos(Nodo *&temp){

	Nodo* respaldo = temp;

	while(temp != 0 && ( temp->token == CADE || temp->token == NUM )){

		temp = temp->siguiente;
		if(temp !=0 && !temp->informacion.compare(","))
			temp = temp->siguiente;
		else
			return true;
	}
	temp = respaldo;
	return false;
}
//comprueba que exista un campo de variables dentro de un parentesis
bool AnalizadorSintactico::camposArgumentosP(Nodo *&temp){

	Nodo* respaldo = temp;

	if(temp != 0 && !temp->informacion.compare("(")){
		temp = temp->siguiente;

		if(camposArgumentos(temp) && temp !=0 && !temp->informacion.compare(")"))
			return true;		
	}
	temp = respaldo;
	return false;
}
//comprueba que exista un argumentos -  VAR TIPO (TAMAÑO)
bool AnalizadorSintactico::variableTipo(Nodo * & temp){

	Nodo* respaldo = temp;

	if(temp != 0 && temp->token == IDE && temp->siguiente !=0 && temp->siguiente->token == RESER ){

		temp = temp->siguiente->siguiente;
		if(temp !=0 && !temp->informacion.compare("(") && temp->siguiente !=0
			&& temp->siguiente->token == NUM && temp->siguiente->siguiente !=0
			&& !temp->siguiente->siguiente->informacion.compare(")") ){
			
			temp = temp->siguiente->siguiente->siguiente;
			return true;
		}
	}
	temp = respaldo;
	return false;

}
//comprueba campo de argumentos este dendtro de un parentesis
bool AnalizadorSintactico::variableTipoP(Nodo *&temp){

	Nodo* respaldo = temp;

	if(temp != 0 && !temp->informacion.compare("(")){
		temp = temp->siguiente;

		while( variableTipo(temp) ){

			if(temp !=0 && !temp->informacion.compare(")")){
				temp = temp->siguiente;
				return true;
			}
			if(temp!=0 && !temp->informacion.compare(","))
				temp = temp->siguiente;
			else
				break;			
		}
	}
	temp = respaldo;
	return false;
}
//vrerifica si hay una condicion
bool AnalizadorSintactico::condicion(Nodo *&temp){

	if(temp && temp->siguiente && temp->siguiente->siguiente)

		if( temp->token == IDE && temp->siguiente->token == OpeC &&
			(temp->siguiente->siguiente->token == CADE || temp->siguiente->siguiente->token == NUM )){

				temp = temp->siguiente->siguiente->siguiente;

				return true;
		}
	return false;

}
//vreifica si hay una condicion WHERE
bool AnalizadorSintactico::condicionWhere(Nodo *&temp){

	Nodo* respaldo = temp;

	if(temp && !temp->informacion.compare("WHERE")){
		temp = temp->siguiente;
		if( condicion(temp))
			return true;
			
	}
	temp = respaldo;
	return false;
}
//instruccion seleccionar
bool AnalizadorSintactico::seleccionar(Nodo *& temp){

	Nodo* respaldo = temp;

	if(temp!=0 &&!temp->informacion.compare("SELECT")){
		temp=temp->siguiente;

		if(campos(temp) && temp && !temp->informacion.compare("FROM") ){

			temp = temp->siguiente;

			if(temp != 0 && temp->token  == IDE){
				temp = temp->siguiente;

				if(temp ==0 || condicionWhere(temp))
					return true;

			}
		}
	}
	temp = respaldo;
	return false;
}
//instruccion insertar
bool AnalizadorSintactico::insertar(Nodo *& temp){

	Nodo* respaldo = temp;

	if(temp && temp->siguiente && temp->siguiente->siguiente && temp->siguiente->siguiente->siguiente)

		if( !temp->informacion.compare("INSERT")&&
			!temp->siguiente->informacion.compare("INTO")&&
			temp->siguiente->siguiente->token == IDE ){

				temp = temp->siguiente->siguiente->siguiente;
			/*if(camposP(temp) && !temp->informacion.compare("VALUES")){
				temp = temp->siguiente;
				if(campos2P(temp))
					return true;			
			}*/
			if(!temp->informacion.compare("VALUES")){
				temp = temp->siguiente;
				if(camposArgumentosP(temp))
					return true;
			}
		}

	temp = respaldo;
	return false;
}
//instruccion crear
bool AnalizadorSintactico::crear(Nodo *& temp){

	Nodo* respaldo = temp;

	if(temp && temp->siguiente && temp->siguiente->siguiente)
		if(!temp->informacion.compare("CREATE") &&
			!temp->siguiente->informacion.compare("TABLE") &&
			temp->siguiente->siguiente->token == IDE){

				temp = temp->siguiente->siguiente->siguiente;

				if(variableTipoP(temp) )
					return true;
		}
		temp = respaldo;
		return false;
}

//saca las comillas de las variables

void AnalizadorSintactico::sacarComillas(Nodo * &temp){
	while(temp){
		if(temp->token == CADE){
			temp->informacion = temp->informacion.substr(1,temp->informacion.size()-2);
		}
		temp = temp->siguiente;
	}
}
