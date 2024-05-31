#ifndef Fichero_H
#define Fichero_H

#include <fstream>
#include <cstring>
#include "ArbolB.h"
using namespace std;

#if (defined(_WIN32) || defined(__WIN32__))
	#define SIZE_ENTER 3
#else
	#define SIZE_ENTER 1
#endif

//funcion que convierte una cadena en un numero entero
void convertirNumero(int *numero,char* cadena);

//clase campo que almacena un dato de la tabla datos
class CampoDatos{
public:
	int longitud; //longitud del dato
	char *valor; //dato
	//constructor
	CampoDatos(){}
	CampoDatos(int longitud){

		this->longitud = longitud;

		valor = new char[longitud];
	
		for(int i=0;i<longitud;i++){
			valor[i] = 0;
		}
		valor [longitud] = '\0';
	}
	//destructor
	~CampoDatos(){
		valor =0;
	}

	//llenamos el dato con un valor
	void operator = (char *cadena){

		//int longitud  = strlen(cadena);
		for(int i=0;i<longitud;i++){
			valor[i] = cadena[i];
		}
		valor[longitud] = '\0';
	}
	//llenamos el dato con un valor const
	void operator = (const char *cadena){

		//int longitudC = strlen(cadena);

		for(int i=0;i<longitud;i++){
			valor[i] = cadena[i];
		}
		valor[longitud] = '\0';
	}
};

//clase registro que contiene varios campos
class RegistroDatos{
public:
	int tamanoRegistro;//longitud del registro
	int numeroCampos;//numero de registros
	CampoDatos* campos;//campos

	//constructores
	RegistroDatos(){}
	RegistroDatos(int numC,int longitud){

		tamanoRegistro = longitud ;
		numeroCampos = numC;
		campos = new CampoDatos[numC];
	}
	RegistroDatos(int numC,int longitud,char* cadena){

		tamanoRegistro = longitud ;
		numeroCampos = numC;
		campos = new CampoDatos[numC];

		int longitudColumna=0;

		for(int i=0; i<numC;i++){

			convertirNumero(&longitudColumna ,cadena);//obtenemos el tamano del campo
			cadena = cadena +sizeof(int);

			CampoDatos campo(longitudColumna);
			campo = cadena;////obtenemos el dato del campo
			
			anadir(i,campo);//anadimos al registro
			
			cadena = cadena + longitudColumna;
		}
	}
	RegistroDatos(int numC,char* cadena){

		numeroCampos = numC;
		campos = new CampoDatos[numC];
		tamanoRegistro =0;

		int longitudColumna=0;

		for(int i=0; i<numC;i++){

			convertirNumero(&longitudColumna ,cadena);//obtenemos el tamano del campo
			cadena = cadena +sizeof(int);//avansamos el puntero el tamano del int

			CampoDatos campo(longitudColumna);
			campo = cadena;////obtenemos el dato del campo
			
			anadir(i,campo);//anadimos al registro

			//actualizamos el tamano del registro
			tamanoRegistro = tamanoRegistro + campo.longitud + sizeof(int);
			
			cadena = cadena + longitudColumna;
		}
	}

	//anadimos un campo al registro
	void anadir(int i,CampoDatos campo){
		campos[i] = campo;
		
	}
	~RegistroDatos(){
		campos = 0;
	}
    int getTotalSize() {
        return tamanoRegistro + SIZE_ENTER;
    }
};

//clase que administra el fichero de datos
class FicheroDatos {
public:
	fstream f; // Stream para E/S al fichero
	int tamRegistro;//tamano del registro
	int numeroColumnas;//tamano del registro
	int posInicial;//posicion inicial
public:
	FicheroDatos();

	~FicheroDatos();

	bool abrir(string);
	bool cargarCabecera(RegistroDatos&);

	bool crear(string fdatos,RegistroDatos);

	
	void insertar(RegistroDatos &nuevoreg);
	void insertar(int ,int,RegistroDatos &nuevoreg);
	
	void leerRegistro(int pos,char* cadena);
	void leerRegistro2(int pos,char* cadena);

	void eliminarRegistro(unsigned long pos);	
	void actualizar(unsigned long pos, const RegistroDatos &nuevoreg);
	
};

//clase campo indice
class Campo{
public:
	int direccion;//direccion al registro
	int longitud;//longitud del clave
	char *valor;//clave 
	Campo(){}
	Campo(int longitud,int direccion){
		this->longitud = longitud;
		this->direccion = direccion;
		valor = new char[longitud];
	
		for(int i=0;i<longitud;i++){
			valor[i] = 0;
		}
		valor [longitud] = '\0';
	}

	~Campo(){
		valor =0;
	}

	//llenamos el dato con un valor
	void operator = (char *cadena){

		int longitud  = strlen(cadena);
		for(int i=0;i<longitud;i++){
			valor[i] = cadena[i];
		}
		valor[longitud] = '\0';
	}
	//llenamos el dato con un valor
	void operator = (const char *cadena){

		int longitud  = strlen(cadena);
		for(int i=0;i<longitud;i++){
			valor[i] = cadena[i];
		}
		valor[longitud] = '\0';
	}
};


//clase Registro de campos de indices
class Registro{
public:
	int longitudFija;//longitud del registro
	int numeroCampos;//numero de campos
	Campo* campos;//campos
	int * hijos;//direccion de los registros indices hijos

	//constructores
	Registro(){}
	Registro(int numC,int longitud){

		longitudFija = longitud;
		numeroCampos = numC;
		campos = new Campo[numC];
		hijos = new int[numC+1];
	}

	Registro(int numC,int longitudC,int longitud,char* cadena){

		longitudFija = longitud ;
		numeroCampos = numC;
		campos = new Campo[numC];
		hijos = new int[numC+1];

		int direccionC =0;
		for(int i=0; i<numC;i++){

			convertirNumero(&direccionC ,cadena);
			cadena = cadena +sizeof(int);

			Campo temp(longitudC,direccionC);
			temp = cadena; //asignando el valor a temp
			
			anadir(i,temp);
			
			cadena = cadena + longitudC;
		}
		int direccionH =0;
		for(int i=0; i<numC+1;i++){

			convertirNumero(&direccionH ,cadena);
			cadena = cadena +sizeof(int);

			hijos[i] = direccionH;			
		}
	}

	//funcion que busca una clave
	bool buscar(string cadena,int & direccion,bool & encontrado){
		
		int tiene=0;
		for(int j=0;j<numeroCampos+1;j++){
			if(hijos[j] ==0)
				tiene ++;
		}

		int bandera ;
		int i=0;

		for(; i< numeroCampos;i++){

			if( compara((string)campos[i].valor,(string)"")==0 ){
				break;
			}

			bandera =compara(cadena,(string)campos[i].valor);

			if(bandera==0){
				direccion = campos[i].direccion;
				encontrado = true;
				return true;
			}
			else if(bandera < 0 && tiene == numeroCampos+1){
				direccion = -1;
				return false;
			}
			else if(bandera < 0){
				direccion = hijos[i];
				return false;
			}
		}
		if(tiene<numeroCampos+1)		
			direccion = hijos[i];
		else
			direccion = -1;
		return false;
	}

	//funcion que busca los mayores de la clave
	bool buscarM(string cadena,int & direccion,bool & encontrado){
		
		int tiene=0;
		for(int j=0;j<numeroCampos+1;j++){
			if(hijos[j] ==0)
				tiene ++;
		}

		int bandera ;
		int bandera2 ;
		int i=0;

		for(; i< numeroCampos;i++){

			if( compara((string)campos[i].valor,(string)"")==0 ){
				break;
			}

			bandera =compara(cadena,(string)campos[i].valor);
			bandera2 =compara(cadena,(string)campos[i+1].valor);

			if(bandera == 1 && bandera2 == -1){
				direccion = campos[i].direccion;
				encontrado = true;
				return true;
			}
			else if(bandera < 0 && tiene == numeroCampos+1){
				direccion = -1;
				return false;
			}
			else if(bandera < 0){
				direccion = hijos[i];
				return false;
			}
		}
		if(tiene<numeroCampos+1)		
			direccion = hijos[i];
		else
			direccion = -1;
		return false;
	}

	//anade un elemento al registro
	void anadir(int i,Campo campo){
		campos[i] = campo;
	}
	~Registro(){
		campos = 0;
	}
};

//clase que gestiona los ficheros de los indices
class FicheroIndice {
public: fstream f; // Stream para E/S al fichero
	int tamRegistro;//tamano de registro
	int posInicial;//pos inicial
	int numeroColumnas;
	
public:
	//constructores
	FicheroIndice(){}

	bool abrir(string);

	~FicheroIndice(); // Cierra el fichero

	bool crear(string fdatos,int,int);

	void leerEncabezado(int&,int&,int&);

	void insertar(Registro &nuevoReg);
	void insertar(int ,Registro &nuevoReg);
	void insertar(int posR,int posC,Registro &nuevoReg);

	//void buscar(Registro&,string);
	//void leerRegistro(unsigned long pos, Registro *&reg,int);

	//lee el reistro indices con una posicion logica
	void leerRegistro(int pos, char*);

	//lee el registro con una posicion fisica
	void leerRegistro2(int pos, char*);
	void eliminarRegistro(unsigned long pos);
	void actualizar(unsigned long pos, const Registro &nuevoreg);
	void compactar(); // Eliminar fnsicamente los borrados
	void vaciar(); // Eliminar todos los registros
};

#endif