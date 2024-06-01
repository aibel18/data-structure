#if (defined(_WIN32) || defined(__WIN32__))

#include "Ventana.h"

#include "AnalizadorSintactico.h"
#include "Tabla.h"


Ventana::Ventana(WNDPROC winProc, const char *nombre, HINSTANCE hins){
	nombreVentana = nombre;
	IdAplicacion = hins;

	claseVentana.style = 0;
	claseVentana.lpfnWndProc= winProc;
	claseVentana.cbWndExtra =0;
	claseVentana.cbClsExtra =0;
	claseVentana.hInstance = IdAplicacion;
	claseVentana.hIcon =0;
	claseVentana.hCursor = LoadCursor(0,IDI_APPLICATION);
	claseVentana.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	claseVentana.lpszMenuName =0;
	claseVentana.lpszClassName =nombreVentana;
	registrar();
}

void Ventana::crearVentana(int ancho,int alto){

	IdVentana = CreateWindowEx(
		0,
		nombreVentana,
		nombreVentana,
		WS_OVERLAPPEDWINDOW,
		100,
		20,
		ancho,
		alto,
		0,
		LoadMenu(IdAplicacion,"Menu"),
		IdAplicacion,
		0
		);
}
void Ventana::registrar(){
	if(!RegisterClass(&claseVentana)){
		MessageBox(NULL,"ESTADO_ERROR de creacion de la ventana.","ESTADO_ERROR",MB_OK|MB_ICONEXCLAMATION);
		return ;
	}
}
void Ventana::mostrar (int cmdShow)
{
        ShowWindow (IdVentana, cmdShow);
        UpdateWindow (IdVentana);
}

void Ventana::limpiar(){

	DestroyWindow(IdVentana);
	UnregisterClass(nombreVentana,IdAplicacion);
}
int Ventana::cicloMensaje(void)
{
	while (GetMessage (&Mensaje, NULL, 0, 0))
	{	TranslateMessage (&Mensaje) ;
		DispatchMessage (&Mensaje) ;
	}
	return Mensaje.wParam ;
}
class DTabla{
public:
	int _columna;
	int _fila;

	int x_tabla;

	int y_tabla;
void dibujaTabla(HDC &hdc,int filas, int columnas){

	RECT rect;
	x_tabla = 50;
	y_tabla = 150;
	int largo = 700;
	int ancho = 400;

	SetRect(&rect,x_tabla ,y_tabla,largo,ancho);

	HBRUSH pincel = CreateSolidBrush(RGB(230, 230, 250));
	SelectObject(hdc, pincel);
	FillRect(hdc,&rect,pincel);
	
	HPEN linea = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	SelectObject(hdc, linea);
	Rectangle(hdc,x_tabla -1,y_tabla-1,largo+1,ancho+1);

	_columna = (largo-x_tabla )/columnas;
	for(int i=1;i<columnas;i++){

		MoveToEx(hdc,rect.left + _columna*i,rect.top,0);
		LineTo(hdc,rect.left + _columna*i,rect.bottom);		
	}

	_fila = (ancho-y_tabla)/filas;
	for(int i=1;i<filas;i++){

		MoveToEx(hdc,rect.left, rect.top + _fila*i,0);
		LineTo(hdc,rect.right, rect.top + _fila*i);		
	}

}
void dibujatexto(HDC &hdc,string &cadena, int fila, int columna){

	SetBkMode(hdc,TRANSPARENT);
	TextOut(hdc,_columna*(columna)+x_tabla+10,_fila*(fila)+y_tabla+_fila/4,cadena.data(),cadena.size());

}
void dibujarFila(HDC &hdc,RegistroDatos &datos, int fila){

	for(int i=0;i<datos.numeroCampos;i++){
        string valor = datos.campos[i].valor;
		dibujatexto(hdc,valor,fila,i);
	}
}
//dibuja toda una fila de datos
void escribirContenidoTabla(HDC &hdc,string title,string cadena){

    unsigned int i = 0,j=0,k=0,l=0;

    dibujatexto(hdc,title,l++,0);
    
    const char * temp = cadena.c_str();
    while(i < cadena.size()){

        while(*temp != '\0'&& *temp != '|'){

            temp = temp +1;
            i++;
        }
        string ca= cadena.substr(k,i-k);
        dibujatexto(hdc,ca,l,j);

        temp= temp +1;			

        i++;
        j++;

        if(*(temp) == '*' ){
            l++;
            i++;
            j=0;
            temp= temp +1;					
        }
        
        k = i;
    }
}
};

#define ACEPTAR 1000

//procesos de la ventana principal
LRESULT CALLBACK  procesos(HWND hwnd, UINT message, WPARAM wParam, LPARAM
							lParam)
{
	static HINSTANCE hi =((LPCREATESTRUCT)lParam)->hInstance;

	static Boton aceptar(hi,hwnd,(HMENU)ACEPTAR);
	static BotonEdit ingreso(hi,hwnd);

	static BotonEdit estado(hi,hwnd);

	static AnalizadorLexico lexico;
	static AnalizadorSintactico sintactico;

	static int * filas;
	static int * columnas;

	static DTabla dtabla;

	static Tabla tabla;

	PAINTSTRUCT ps;
	HDC hdc;
	
	switch (message)
	{
		case WM_CREATE:{

			aceptar.crear_boton("aceptar",600,75,100,20);
			ingreso.crear_boton(50,50,650,20);
			estado.crear_boton(150,100,450,30);

			filas = new int;
			columnas = new int;

			*filas = 1;
			*columnas = 1;
			
			return 0;
		}
				
		case WM_COMMAND:{
			
			if(LOWORD(wParam) == ACEPTAR){

				hdc = GetDC(hwnd);

				char cadena [100];
				GetWindowText(ingreso.IdVentana,cadena,100);

				int longitud =strlen(cadena);

				if(longitud >0)

				if(lexico.automata((string)cadena,longitud)){

					Nodo* temp = lexico.almacen.inicio;
					SetWindowText(estado.IdVentana,"");

					try{
						switch(sintactico.analiza(temp)){
							case 1:
								tabla.insertar(lexico.almacen);
								SetWindowText(estado.IdVentana,"bien insert");
								
								break;

							case 2:
								tabla.buscar(lexico.almacen);

								hdc = GetDC(hwnd);
							
								*columnas = tabla.encabezado.numeroCampos;
								*filas = 10;//tabla.encabezado.numeroCampos;

								dtabla.dibujaTabla(hdc,*filas,*columnas);
                                dtabla.escribirContenidoTabla(hdc,tabla.nombre,tabla.Buffer);
								ReleaseDC(hwnd,hdc);

								SetWindowText(estado.IdVentana,"bien selec");
								break;

							case 3:
								tabla.crearTabla(lexico.almacen);
								SetWindowText(estado.IdVentana,"bien crear");
						
								break;

							case 0:
								SetWindowText(estado.IdVentana,"error sintactico");
								break;
						}
					}
					catch(excepciones::datoNoEncuentra){
							SetWindowText(estado.IdVentana,"no se encontro ningun resultado");
					}
					catch(excepciones::tablaExiste){
							SetWindowText(estado.IdVentana,"la tabla ya existe");
					}
					catch(excepciones::tablaError){
						SetWindowText(estado.IdVentana,"se produjo algun error");
					}
					catch(excepciones::tablaNoEncuentra){
						SetWindowText(estado.IdVentana,"la tabla no se encuentra");
					}
					catch(excepciones::exesoCampos){
						SetWindowText(estado.IdVentana,"los campos no concuerdan");
					}
					catch(excepciones::campoNoEncuentra){
						SetWindowText(estado.IdVentana,"el campo no se encuentra en la tabla");
					}
				}
				else
					SetWindowText(estado.IdVentana,"error lexico");
				
			}
			return 0;
		}
		case WM_PAINT:
		{
			hdc = BeginPaint(hwnd, &ps);
			
			dtabla.dibujaTabla(hdc,*filas,*columnas);
			EndPaint(hwnd, &ps);
			return 0;
		}
		case WM_DESTROY:
		{	PostQuitMessage (0);
			
			return 0;
		}
	}
	return DefWindowProc (hwnd, message, wParam, lParam) ;
}

#endif