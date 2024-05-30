#include "Fichero.h"
#include "ArbolB.h"

#include "ListaDoble.h"

//exepciones 
namespace excepciones
{
	class tablaAbierto{};
	class tablaExiste{};
	class tablaNoEncuentra{};
	class campoNoEncuentra{};
	class tablaError{};
	class datoNoEncuentra{};

	class exesoCampos{};
}

RegistroDatos codificar(Lista & );

void guardarCampo(FicheroIndice &f,nodoB* n,int &,int &j);
void guardar(FicheroIndice &f,nodoB *Act,int &,int&j);

class Tabla{
public:
	RegistroDatos encabezado;
	Registro raiz;

	string nombre;
	int * resultados;

	int ordenArbol;
public:
	void crearTabla( Lista&);
	void insertar( Lista&);

	void ordenar(Lista&);

	void buscar(Lista&);

	void buscar(string, char*);
	void crearIndice(int);
};