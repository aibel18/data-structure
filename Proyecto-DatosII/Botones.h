//clase Botones-----
#ifndef Botones
#define Botones
#include <windows.h>
class BotonEdit{

public:
	HWND IdVentana;
	HWND IdPadre;
	HMENU hijo;
	HINSTANCE IdAplicacion;
	DWORD estilo;

	BotonEdit(){}

	BotonEdit(HINSTANCE hinst,HWND hwnd ,HMENU h=0);
	void set(HINSTANCE hinst,HWND hwnd,HMENU h=0);
	void SetEstilo(int e0=0,int e1=0,int e2=0,int e3=0,int e4=0);
	void crear_boton(int,int ,int,int);

};

//-------------------
class BotonStatic{
public:
	HWND IdVentana;
	HWND IdPadre;
	HINSTANCE IdAplicacion;
	DWORD estilo;
	
	char* contenido;

	BotonStatic(){}
	BotonStatic(HINSTANCE hinst,HWND hwnd);
	void set(HINSTANCE hinst,HWND hwnd);
	void SetEstilo(int e0=0,int e1=0,int e2=0,int e3=0,int e4=0);
	void crear_boton(char*,int,int,int,int);

};

//-------------------
class Boton{
public:
	HWND IdVentana;
	HWND IdPadre;
	HINSTANCE IdAplicacion;
	HMENU hijo;
	DWORD estilo;
	
	char* contenido;

	Boton(){}
	Boton(HINSTANCE hinst,HWND hwnd,HMENU h=0);
	void set(HINSTANCE hinst,HWND hwnd,HMENU h=0);
	void SetEstilo(int e0=0,int e1=0,int e2=0,int e3=0,int e4=0);	

	void crear_boton(char*,int,int,int,int);

};
#endif