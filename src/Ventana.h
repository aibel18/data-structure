#include <windows.h>
#include "Botones.h"
//clase Ventana ----------
class Ventana{

private:
	WNDCLASS  claseVentana;
protected:
	HWND      IdVentana;
public:
	HINSTANCE IdAplicacion;
	const char *nombreVentana;
	MSG       Mensaje;

	Ventana(){}
	Ventana(WNDPROC winProc,char const* nombre,HINSTANCE hins);
	~Ventana(){
		limpiar();	
	}
	void registrar();
	void mostrar(int );
	void crearVentana(int,int);
	void limpiar();

	int cicloMensaje(void);

};
//procesos de la ventana
LRESULT CALLBACK procesos
    (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

