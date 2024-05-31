#include "Fichero.h"

void convertirNumero(int *numero,char* cadena){

	int *numeros;
	numeros = (int*)(cadena);
	*numero = *numeros;

}

FicheroDatos::FicheroDatos(){
}

//funcion que crea un fichero nuevo
bool FicheroDatos::crear(string nombre,RegistroDatos registro){	

	f.open(nombre.c_str(),ios::in | ios::out);

	//comprobamos si el fichero ya existe
	if (!f.is_open()){

		//si no existe lo creamos
		
		f.open(nombre.c_str(),ios::in | ios::out | ios::trunc);
		f.seekg (0, ios::beg);
		f.seekp (0, ios::beg);

		//tamano del registro
		tamRegistro = registro.tamanoRegistro;

		//ponemos la cabecera del archivo 
		
		//tamano del registro
		f.write(reinterpret_cast<char *>(&registro.tamanoRegistro), sizeof(int));
		//numero de columnas
		f.write(reinterpret_cast<char *>(&registro.numeroCampos), sizeof(int));

		//guardamos los campos
		for(int i=0;i<registro.numeroCampos;i++){
			f.write(reinterpret_cast<char *>(&registro.campos[i].longitud), sizeof(int));
			f.write(reinterpret_cast<char *>(registro.campos[i].valor), registro.campos[i].longitud);
		}
		//enter
		f.write("\n",1);	
		
		//cerramos el fichero
		f.close();
		return true;
	}
	
	return false;
}
//abrir un fichero ya existente
bool FicheroDatos::abrir(string nombre){

	//abrimos
	f.open(nombre.c_str(),ios::in | ios::out);

	if (f.is_open()){

		f.seekg (0, ios::beg);	
		//cargamos el tamano del registro
		f.read(reinterpret_cast<char *>(&tamRegistro),sizeof(int));
		//cargamos el numero de columnas
		f.read(reinterpret_cast<char *>(&numeroColumnas),sizeof(int));

		posInicial = sizeof(int)*2 + tamRegistro+SIZE_ENTER;
		return true;
	}

	return false;
}
//cargamos la cabecera del archivo
bool FicheroDatos::cargarCabecera(RegistroDatos& cabecera){

	if (f.is_open()){

		int tamanoRegistro;
		int numeroColumnas;

		f.seekg (0, ios::beg);
		//tamano del registro
		f.read(reinterpret_cast<char *>(&tamanoRegistro),sizeof(int));
		//numero de columnas 
		f.read(reinterpret_cast<char *>(&numeroColumnas),sizeof(int));

		//nombre de las columnas
		char * cadena = new char[tamanoRegistro];
		f.read(reinterpret_cast<char *>(cadena),tamanoRegistro);
		
		cabecera = RegistroDatos(numeroColumnas,cadena);

		return true;
	}

	return false;
}
//insertar un registro en el fichero al final
void FicheroDatos::insertar(RegistroDatos & nuevo){
	if(f.is_open()){
		f.seekp (0, ios::end);

		for(int i=0;i<nuevo.numeroCampos;i++){
			f.write(reinterpret_cast<char *>(&nuevo.campos[i].longitud), sizeof(int));
			f.write(reinterpret_cast<char *>(nuevo.campos[i].valor), nuevo.campos[i].longitud);
		}

		f.write("\n",1);		
	}	
}
//insertar un registro en la posicion indicada
void FicheroDatos::insertar(int posR,int posC,RegistroDatos & nuevo){
	if(f.is_open()){

		int pos=0;
		for(int i=0; i<posC;i++){
			pos =pos + nuevo.campos[i].longitud;
		}
		f.seekp ((nuevo.tamanoRegistro+SIZE_ENTER)*posR +pos+posInicial, ios::beg);
		f.write(reinterpret_cast<char *>(nuevo.campos[posC].valor), nuevo.campos[posC].longitud);
	
	}	
}
//lee un registro entero de acuerdo a su tamano con direccion logica
void FicheroDatos::leerRegistro(int pos,char* cadena){
	if(f.is_open()){
		
		f.seekg ((tamRegistro+SIZE_ENTER)*pos+posInicial, ios::beg);
		f.read(reinterpret_cast<char *>(cadena), tamRegistro);
	}	
}
//lee un registro entero de acuerdo a su tamano con direccion fisica
void FicheroDatos::leerRegistro2(int pos,char* cadena){
	if(f.is_open()){
		
		f.seekg (pos, ios::beg);
		f.read(reinterpret_cast<char *>(cadena), tamRegistro);
	}	
}

FicheroDatos::~FicheroDatos(){
	if(f.is_open())
		f.close();
}



//fichero indices--------------

//constructores

//crea un fichero indice
bool FicheroIndice::crear(string fdatos, int columnas, int tamanoC){
	
	f.open(fdatos.c_str(),ios::in | ios::out);

	if (!f.is_open()){
		
		f.open(fdatos.c_str(),ios::in | ios::out | ios::trunc);
		f.seekg (0, ios::beg);
		tamRegistro = (sizeof(int)+tamanoC)*columnas;

		f.write(reinterpret_cast<char *>(&tamanoC), sizeof(int));
		f.write(reinterpret_cast<char *>(&columnas), sizeof(int));		

		int raiz=-1;
		f.write(reinterpret_cast<char *>(&raiz), sizeof(int));

		f.write("\n",1);	
		
		f.close();
		return true;
	}

	return false;
}
//abre un fichero indice
bool FicheroIndice::abrir(string fdatos){

	f.open(fdatos.c_str(),ios::in | ios::out);

	if (f.is_open()){
		int ancho;

		f.seekg (0, ios::beg);
		//cargamos el tamano del registro
		f.read(reinterpret_cast<char *>(&ancho),sizeof(int));
		//cargamos el numero de columnas
		f.read(reinterpret_cast<char *>(&numeroColumnas),sizeof(int));

		tamRegistro = ancho*numeroColumnas + numeroColumnas*(sizeof(int))+ (numeroColumnas+1)*(sizeof(int));
		posInicial = sizeof(int)*3+SIZE_ENTER;

		return true;
	}

	return false;
}
//inserta un registro en el fichero indice
void FicheroIndice::insertar(Registro & nuevo){
	if(f.is_open()){

		f.seekp (0, ios::end);

		//guarcmos los campos
		for(int i=0;i<nuevo.numeroCampos;i++){
			f.write(reinterpret_cast<char *>(&nuevo.campos[i].direccion), sizeof(int));
			f.write(reinterpret_cast<char *>(nuevo.campos[i].valor), nuevo.campos[i].longitud);		
		}
		//guardamos los hijos
		for(int i=0;i<nuevo.numeroCampos+1;i++){
			f.write(reinterpret_cast<char *>(&nuevo.hijos[i]), sizeof(int));
		}
		f.write("\n",1);		
	}	
}
//inserta un registro en una posicion indicada
void FicheroIndice::insertar(int posR,Registro & nuevo){
	if(f.is_open()){

		f.seekp ((nuevo.longitudFija+SIZE_ENTER)*posR+12 +SIZE_ENTER, ios::beg);
		
		for(int i=0;i<nuevo.numeroCampos;i++){
			f.write(reinterpret_cast<char *>(&nuevo.campos[i].direccion), sizeof(int));
			f.write(reinterpret_cast<char *>(nuevo.campos[i].valor), nuevo.campos[i].longitud);		
		}
		for(int i=0;i<nuevo.numeroCampos+1;i++){
			f.write(reinterpret_cast<char *>(&nuevo.hijos[i]), sizeof(int));
		}
		f.write("\n",1);		
	}	
}
//inserta un campo en la posicion indicada
void FicheroIndice::insertar(int posR,int posC,Registro& nuevo){

	int pos=0;
	for(int i=0; i<posC;i++){
		pos =pos+ 4 + nuevo.campos[i].longitud;
	}

	f.seekp ((nuevo.longitudFija+SIZE_ENTER)*posR + pos +12 + SIZE_ENTER, ios::beg);

	f.write(reinterpret_cast<char *>(&nuevo.campos[posC].direccion), sizeof(int));
	f.write(reinterpret_cast<char *>(nuevo.campos[posC].valor), nuevo.campos[posC].longitud);

}
//lee un registro indice con direccion logica
void FicheroIndice::leerRegistro(int pos,char* cadena){
	if(f.is_open()){
		
		f.seekg ((tamRegistro+SIZE_ENTER)*pos+posInicial, ios::beg);
		f.read(reinterpret_cast<char *>(cadena),tamRegistro);
	}	
}
//lee un registro indice con direccion fisica
void FicheroIndice::leerRegistro2(int pos,char* cadena){
	if(f.is_open()){
		
		f.seekg (pos+posInicial, ios::beg);
		f.read(reinterpret_cast<char *>(cadena),tamRegistro);
	}	
}
//leer el encabezado del fichero indice
void FicheroIndice::leerEncabezado(int &tamano,int &columnas,int &raiz){

	if(f.is_open()){

		f.seekg (0, ios::beg);
		f.read(reinterpret_cast<char *>(&tamano), sizeof(int) );
		f.seekg (4, ios::beg);
		f.read(reinterpret_cast<char *>(&columnas), sizeof(int) );
		f.seekg (8, ios::beg);
		f.read(reinterpret_cast<char *>(&raiz), sizeof(int) );
	}	
}

FicheroIndice::~FicheroIndice(){
	if(f.is_open())
		f.close();
}

