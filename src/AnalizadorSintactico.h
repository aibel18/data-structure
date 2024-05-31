#ifndef H_AnalizadorS
#define H_AnalizadorS

#include <iostream>
#include <string>

#include "AnalizadorLexico.h"

class AnalizadorSintactico{

	bool campos(Nodo *&temp);
	bool camposP(Nodo *&temp);
	bool camposArgumentos(Nodo *&temp);
	bool camposArgumentosP(Nodo *&temp);
	bool variableTipo(Nodo * & temp);
	bool variableTipoP(Nodo *&temp);
	bool condicion(Nodo *&temp);
	bool condicionWhere(Nodo *&temp);

	//instrucciones
	bool seleccionar(Nodo *& temp);
	bool insertar(Nodo *& temp);
	bool crear(Nodo *& temp);

	void sacarParentesis(Nodo*&);
	void sacarComas(Nodo*&);
	void sacarComillas(Nodo*&);

public:
	int analiza(Nodo *&temp);

};


#endif
