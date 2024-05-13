#ifndef H_Analizador  
#define H_Analizador

#include <iostream>
#include <string>

#include "ListaDoble.h"

using namespace std;
#define numOpe 8
#define numRes 15

#define NUM 00
#define IDE 10

//binarios----
#define OpeC 25
#define OpeI 26
//---------
#define OpeO 21

#define RESER 32
#define CADE 40


class AnalizadorLexico{
public:

	AnalizadorLexico();
	~AnalizadorLexico();

	bool automata(string&,int);

	bool buscaNumero(string&,int&);
	bool buscaIdentificador(string&,int&);
	bool buscaReservada(string&,int&);
	int buscaOperador(string&,int&);
	bool buscaCadena(string&,int&);
	bool buscaCaracter(string&,int&);

	void reiniciarAlmacen();

	Lista almacen;

private:
	string bancoReservadas[numRes];
	char bancoOperadores[numOpe];

	void cargarReservadas();
	void cargarOperadores();

};

#endif