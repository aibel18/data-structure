#include "ListaDoble.h"

Nodo* busca(Nodo* nodo,string infor){

	while(nodo != 0){

		if(!nodo->informacion.compare(infor)){
			return nodo;
		}
		nodo = nodo->siguiente;
	}
	return 0;
}
Nodo* busca(Nodo* nodo,Tokens token){

	while(nodo != 0){

		if(nodo->token == token){
			return nodo;
		}
		nodo = nodo->siguiente;
	}
	return 0;
}


string* Lista::getInicio(){
	return &inicio->informacion;

}
void Lista::operator= (Lista &l){

	inicio= l.inicio;
	final= l.final;
	numNodos= l.numNodos;

	l.inicio=0;
	l.final=0;
	l.numNodos=0;
	
}
bool Lista::operator< (Lista &l){
	if(this!=0 && this->inicio!=0)
		return inicio->informacion < l.inicio->informacion;
	return false;
}
bool Lista::operator== (Lista &l){

	if(this)
		return inicio->informacion == l.inicio->informacion;
	return false;
	
}
int Lista::compara(string &cadena){

	unsigned int temp = inicio->informacion.length() ;
	unsigned int temp2 = cadena.length() ;

	unsigned int limite;
		
	if( temp > temp2)
		limite = temp2;
	else
		limite = temp;

	for(unsigned int i=0;i < limite ;i++){

		if ( inicio->informacion[i] > cadena[i] )
			return 1;
		
		else if( inicio->informacion[i] < cadena[i] )
			return -1;
	}
	if ( temp > temp2 )
			return 1;
		
	else if( temp < temp2 )
			return -1;
	else
		return 0;
	
}
void Lista::ingresar(Nodo* n){

}
void Lista::ingresar(string &x,Tokens px){
	Nodo *nuevo = new Nodo();

	nuevo->token = px;
	nuevo->informacion = x;

	if(inicio  == 0){
		inicio = nuevo;
		final = inicio;
	}
	else{
		final->siguiente = nuevo;
		nuevo->anterior = final;
		final = nuevo;
	}
	numNodos++;
}

ostream& operator<<(ostream& o,Lista &l){

	Nodo* temp = l.inicio;

	while(temp){

		cout<<temp->informacion<<endl;
		temp=temp->siguiente;

	}	
	return o;
}

void Lista::eliminarLista(Nodo* &nodo){
	if(nodo){
		eliminarLista(nodo->siguiente);
		nodo->token=0;
		delete nodo;
		nodo=0;
		numNodos--;	
	}
}

void Lista::eliminar(Nodo* nodo){

	if(nodo){
		if(inicio==nodo){
			inicio = nodo->siguiente;
			inicio->anterior=0;
		}
		else if(final==nodo){
			final = nodo->anterior;
			final->siguiente=0;
		}
		else{
			
			nodo->siguiente->anterior = nodo->anterior;
			nodo->anterior->siguiente =nodo->siguiente;
		}
		numNodos--;
	}
	
}
