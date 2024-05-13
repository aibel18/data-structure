#include "Ventana.h"
#include <windows.h>


int WINAPI WinMain(	HINSTANCE hInst,HINSTANCE hPrevInst,
				   char* cmdParam,int cmdShow)
{
	Ventana ven(procesos,"Mi Ventana",hInst);
	ven.crearVentana(750,500);
	ven.mostrar(cmdShow);
	
	return ven.cicloMensaje();
	return 0;
	
}