#ifndef H_ListaDoble  
#define H_ListaDoble
#include <iostream>
#include <string>

using namespace std;
typedef int  Tokens;

class Nodo{
public:
	string informacion;

	Tokens token;

	Nodo* siguiente;
	Nodo* anterior;
	Nodo():siguiente(0),anterior(0){}

	
};
Nodo* busca(Nodo*,string);

class Lista{
public:
	//friend ostream;
	Nodo* inicio;
	Nodo* final;
	int numNodos;
	void ingresar(string&,Tokens);
	void ingresar(Nodo*);
	void eliminarLista(Nodo*&);
	void eliminar(Nodo*);

	void operator=(Lista&);
	bool operator<(Lista&);
	bool operator==(Lista&);
	//bool operator<(Lista&);

	int compara(string&);

	string* getInicio();
	
	Lista(){inicio=0;final=0;numNodos =0;};
	~Lista(){
		eliminarLista(inicio);
		inicio=0;
		final=0;
	}
};

void eliminar(Nodo*);

ostream& operator<<(ostream&,Lista &);

#endif