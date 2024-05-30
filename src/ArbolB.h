#ifndef ArbolB_H
#define ArbolB_H

#include <string>
#include <iostream>

using namespace std;

int compara(string c,string cadena);

struct bClaves{
	long registro;
	string valor;
	
};
class nodoB{
public:
	bClaves *claves;   
public:
	nodoB* *hijos;  

	int clavesUsadas;
public:
	int page;
	nodoB(int orden){
		claves = new bClaves[orden-1];
		hijos=new nodoB*[orden];
		clavesUsadas=0;

		for(int i=0;i<orden;i++)
			hijos[i]=0;
	}
	~nodoB(){

		delete []claves;
		delete []hijos;
		claves=0;
		hijos=0;
	}
	bool nodoLleno(int);
	bool nodoVacio(int);
	void escribeNodo();
	
	friend class ArbolB;
};

class ArbolB{
//private:
public :
	nodoB *raiz;
	int orden;
	bool encontrarNodo(nodoB *,bClaves&, int *);
public:
	ArbolB(){
		raiz =0;
		cont=0;
	}
	ArbolB(int nEle){
		orden=nEle;
		raiz=0;
		cont=0;
	}
	~ArbolB(){
		eliminarArbol(raiz);
	}
	int cont;
	
	nodoB* encontrar(bClaves &,int *pos,nodoB*Nodo=NULL, bool r=true);
	void insertar(bClaves&);
	void push(nodoB *,bClaves&,int*,bClaves *,nodoB **);
	void putLeaf(nodoB *,bClaves,nodoB*,int);
	void dividirNodo(nodoB *Act,bClaves &cl,nodoB *rd,int k,bClaves *clMedian,nodoB **newnode);
	void mostrarArbol(nodoB *Act=NULL,bool r=true);

	bClaves* busca(nodoB*,bClaves&);

	nodoB* buscar(nodoB*,bClaves&,int*);
	int buscaNodo(nodoB*,bClaves&,int*);

	void eliminarArbol(nodoB*);
	
};
/*class nodoB{
private:
	string *claves;   
	nodoB* *hijos;   
	int clavesUsadas;
public:
	int page;
	nodoB(int orden){
		claves = new string[orden-1];
		hijos=new nodoB*[orden];
		clavesUsadas=0;

		for(int i=0;i<orden;i++)
			hijos[i]=0;
	}
	~nodoB(){

		delete []claves;
		delete []hijos;
		claves=0;
		hijos=0;
	}
	bool nodoLleno(int);
	bool nodoVacio(int);
	void escribeNodo();
	
	friend class ArbolB;
};

class ArbolB{
private:
	nodoB *raiz;
	int orden;
	bool encontrarNodo(nodoB *,string&, int *);
public:
	ArbolB(){
		raiz =0;
		cont=0;
	}
	ArbolB(int nEle){
		orden=nEle;
		raiz=0;
		cont=0;
	}
	~ArbolB(){
		eliminarArbol(raiz);
	}
	int cont;
	
	nodoB* encontrar(string &,int *pos,nodoB*Nodo=NULL, bool r=true);
	void insertar(string&);
	void push(nodoB *,string&,int*,string *,nodoB **);
	void putLeaf(nodoB *,string,nodoB*,int);
	void dividirNodo(nodoB *Act,string &cl,nodoB *rd,int k,string *clMedian,nodoB **newnode);
	void mostrarArbol(nodoB *Act=NULL,bool r=true);

	string* busca(nodoB*,string&);

	nodoB* buscar(nodoB*,string&,int*);
	int buscaNodo(nodoB*,string&,int*);

	void eliminarArbol(nodoB*);
	
};
*/

#endif