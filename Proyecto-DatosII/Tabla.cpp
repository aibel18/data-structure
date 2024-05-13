#include "Tabla.h"
#include "ArbolB.h"
#include "ListaDoble.h"

#include <iostream>

using namespace std;

//funcion de convierte un cadena en numero
int convertir(string cadena){
	int longitud = cadena.size(),i=0;

	int numero=0;
	int temp =0;
	while(cadena[i]!='.' && i<longitud ){
		temp = (cadena[i]-'0');
		numero = numero*10 +temp;
		i++;		
	}
	return numero;
}
//funcion que codifica una lista de campos en un registro
RegistroDatos codificar(Lista & lista){

	Nodo* temp = lista.inicio->siguiente->siguiente->siguiente->siguiente;

	int numeroC =0;
	int tamañoC =0;
	while(temp->informacion.compare(")")){

		tamañoC += convertir(temp->siguiente->siguiente->siguiente->informacion)+ sizeof(int);

		numeroC++;

		temp = temp->siguiente->siguiente->siguiente->siguiente->siguiente;

		if(!temp->informacion.compare(","))
			temp = temp->siguiente;

	}
	temp = lista.inicio->siguiente->siguiente->siguiente->siguiente;

	RegistroDatos rd(numeroC,tamañoC);

	int i=0;
	while(temp->informacion.compare(")")){

		CampoDatos cd1(convertir(temp->siguiente->siguiente->siguiente->informacion));
		cd1 = temp->informacion.c_str();

		rd.añadir(i,cd1);

		temp = temp->siguiente->siguiente->siguiente->siguiente->siguiente;

		i++;

		if(!temp->informacion.compare(","))
			temp = temp->siguiente;
	}

	return rd;
}
//codifica una lista de argumentos a un registro de campos
RegistroDatos codificar2(RegistroDatos & r,Lista & lista){

	Nodo* temp = lista.inicio->siguiente->siguiente->siguiente->siguiente->siguiente;

	RegistroDatos rd(r.numeroCampos,r.tamañoRegistro);

	int i=0;
	while(temp->informacion.compare(")")){

		CampoDatos cd1( r.campos[i].longitud);
		cd1 = temp->informacion.c_str();

		rd.añadir(i,cd1);

		temp = temp->siguiente;

		i++;

		if(!temp->informacion.compare(","))
			temp = temp->siguiente;
	}

	
	if(i!=r.numeroCampos)
		throw excepciones::exesoCampos();

	return rd;
}

//crea una tabla
void Tabla::crearTabla(Lista &lista){

	ordenArbol = 4;

	nombre = lista.inicio->siguiente->siguiente->informacion;

	FicheroDatos f;

	string nombreV = "BaseDatos/"+nombre+".txt";

	if(f.abrir(nombreV)){
		throw excepciones::tablaExiste();
	}
	else{
		RegistroDatos rd = codificar(lista);
			
		if(f.crear(nombreV,rd)){

			FicheroIndice f2;
			string nombreIV;

			for(int i=0;i<rd.numeroCampos;i++){

				 nombreIV= "BaseDatos/"+nombre+"-"+rd.campos[i].valor+".txt";
				 if(!f2.crear(nombreIV,ordenArbol-1,rd.campos[i].longitud)){

					 throw excepciones::tablaError();
					 return ;
				 }
			}

			cout<<"se creo satisfactoriamente";
			f2.f.close();
			
		}
	}
}
//inserta los datos especificados
void Tabla::insertar( Lista& lista){

	FicheroDatos f;

	nombre = lista.inicio->siguiente->siguiente->informacion;

	string nombreV = "BaseDatos/"+nombre+".txt";

	if(f.abrir(nombreV)){

		f.cargarCabecera(encabezado);

		RegistroDatos registro = codificar2(encabezado,lista);

		f.insertar(registro);

		f.f.close();

		for(int i=0;i< encabezado.numeroCampos;i++){

			crearIndice(i);

		}
		f.f.close();
	}
	else{
		throw excepciones::tablaNoEncuentra();
	}
}

//busca un dato
void Tabla::buscar(Lista &lista){

	FicheroDatos ff;
	nombre = lista.inicio->siguiente->siguiente->siguiente->informacion;
	string nombreV = "BaseDatos/"+nombre+".txt";

	if(ff.abrir(nombreV)){

		ff.cargarCabecera(encabezado);
		nombreV = "BaseDatos/"+nombre+"-"+lista.inicio->siguiente->siguiente->siguiente->siguiente->siguiente->informacion+".txt";
		FicheroIndice fI;	
		if(fI.abrir(nombreV)){

			Nodo* tem = lista.inicio;
			tem = busca(tem,"WHERE");

			if(tem){

				int dRaiz;
				fI.leerEncabezado(raiz.longitudFija,raiz.numeroCampos,dRaiz);

				char *cadena = new char [fI.tamRegistro];
				fI.leerRegistro(dRaiz,cadena);

				Registro b (raiz.numeroCampos,raiz.longitudFija,fI.tamRegistro,cadena);

				int direccion ;
				bool encontrado = false;
				
				while(!b.buscar(tem->siguiente->siguiente->siguiente->informacion,direccion,encontrado)){

					if(direccion ==-1)
						break;
					fI.leerRegistro2(direccion,cadena);
					Registro t (raiz.numeroCampos,raiz.longitudFija,fI.tamRegistro,cadena);

					b= t;
				}
				if(encontrado){
					resultados = new int;
					*resultados = direccion;
				}
				else
					throw excepciones::datoNoEncuentra();
			}
		}
		else	
			throw excepciones::campoNoEncuentra();
	}

	else	
		throw excepciones::tablaNoEncuentra();
}

void Tabla::ordenar(Lista& lista){


}
//crea los indices segun lacolumna
void Tabla::crearIndice(int columna){

	string nombreV = "BaseDatos/"+nombre+".txt";

	ordenArbol =4;

	FicheroDatos f;
	if(f.abrir(nombreV)){

		f.tamRegistro = encabezado.tamañoRegistro;

		f.posInicial = 10 +encabezado.tamañoRegistro;
	
		ArbolB a(ordenArbol);
		bClaves t ;
		char caden[80];
	
		f.f.seekg (0, ios::end);
		int length = f.f.tellg();

		length = (length-f.posInicial)/encabezado.tamañoRegistro;
		
		for(int i =0;i<length; i++){

			f.leerRegistro(i,caden);

			RegistroDatos temporal(encabezado.numeroCampos,f.tamRegistro,caden);

			t.registro = (temporal.tamañoRegistro+2)*i+f.posInicial;//dando la direcion fisica al fichero de indicees
			t.valor = temporal.campos[columna].valor;

			a.insertar(t);
		}
		a.mostrarArbol();

		string cadena2 = "BaseDatos/"+nombre+"-"+encabezado.campos[columna].valor+".txt";

		FicheroIndice f2;

		if(f2.abrir(cadena2)){

			f2.tamRegistro = ((encabezado.campos[columna].longitud +sizeof(int))*(ordenArbol-1))+sizeof(int)*ordenArbol;

			//escribimos la direccion de la raiz en el fichero de indices
			f2.f.seekp (8, ios::beg);
			f2.f.write(reinterpret_cast<char *>(&a.raiz->page), sizeof(int));

			int ref = ordenArbol-1;
			guardar(f2,a.raiz,ref,encabezado.campos[columna].longitud);

		}
		f.f.close();
	}
}
//guarda un nodo de un arbol en un fichero
void guardarCampo(FicheroIndice &f,nodoB* n,int &numeroC,int &tamañoC){

	Campo campo;
	Registro registro(numeroC,f.tamRegistro);
	int i;
	for(i=0;i<n->clavesUsadas;i++){
		campo = Campo(tamañoC,n->claves[i].registro);
		campo = n->claves[i].valor.c_str();

		registro.añadir(i,campo);
	}

	for(int k=i;k<registro.numeroCampos;k++){
		campo = Campo(tamañoC,0);
		registro.añadir(k,campo);
	}

	
	int j;
	for(j=0;j<n->clavesUsadas+1;j++){
		if(!n->hijos[j])
			break;
		registro.hijos[j] = n->hijos[j]->page*(f.tamRegistro+2);
		
	}

	for(int k=j;k<registro.numeroCampos+1;k++){
		registro.hijos[k] = 0;
	}

	f.insertar(n->page,registro);
}
//guarda todos el arbol en un fichero
void guardar(FicheroIndice &f,nodoB *Act,int &numeroC,int&j){
	int i;
	
	if(!Act)return;
	guardarCampo(f,Act,numeroC,j);

	for(i=0;i<=Act->clavesUsadas;i++)
		guardar(f,Act->hijos[i],numeroC,j);
}