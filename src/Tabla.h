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
//clase tabla que es la que maneja todas las funciones de una tabla en SQL
class Tabla{
	void crearIndice(int);
	void mostrarTabla(FicheroDatos &,int );
public:
    Tabla();
	RegistroDatos encabezado;//regsitro cabecera del la tabla datos
	Registro raiz;//registro de un la raiz del arbol

	string nombre;//nombre de la tabla

	string Buffer;//buffer para los resultados obtenidos
	int ordenArbol;//orden del arbol

public:
	void crearTabla( Lista&);
	void insertar( Lista&);

	void ordenar(Lista&);

	void buscar(Lista&);
	
};

//convierte una cadena en numero
int convertir(string cadena);
//funcion que codifica una lista de campos en un registro
RegistroDatos codificar(Lista & );

//funcocion que guarda un campo en un fichero
void guardarCampo(FicheroIndice &f,nodoB* n,int &,int &j);
//funcion que guarda un ragistro en un fichero
void guardar(FicheroIndice &f,nodoB *Act,int &,int&j);
