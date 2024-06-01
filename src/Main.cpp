#include "Tabla.h"
#include "AnalizadorSintactico.h"

#if (defined(_WIN32) || defined(__WIN32__))

#include "Ventana.h"
#include <windows.h>

int WINAPI WinMain(	HINSTANCE hInst,HINSTANCE hPrevInst, char* cmdParam,int cmdShow) {
	Ventana ven(procesos,"Mi Ventana",hInst);
	ven.crearVentana(750,650);
	ven.mostrar(cmdShow);
	
	return ven.cicloMensaje();
}

#else

int main() {
    ifstream sqlFile;
    sqlFile.open ("sql.txt");
    string cadena;

    getline( sqlFile, cadena );

    static AnalizadorLexico lexico;
    static AnalizadorSintactico sintactico;
    static Tabla tabla;

    if (cadena.size() > 0) {

        if (lexico.automata(cadena, cadena.size())) {

            Nodo* temp = lexico.almacen.inicio;
            // std::cout<<"");

            try {
                switch (sintactico.analiza(temp)) {
                    case 1:
                        std::cout << "bien insert" << std::endl;
                        tabla.insertar(lexico.almacen);

                        break;

                    case 2:
                        std::cout << "bien selec" << std::endl;
                        tabla.buscar(lexico.almacen);

                        std::cout << tabla.Buffer << endl;

                        break;

                    case 3:
                        std::cout << "bien crear" << std::endl;
                        tabla.crearTabla(lexico.almacen);

                        break;

                    case 0:
                        std::cout << "error sintactico" << std::endl;
                        break;
                }
            } catch (excepciones::datoNoEncuentra) {
                std::cout << "no se encontro ningun resultado" << std::endl;
            } catch (excepciones::tablaExiste) {
                std::cout << "la tabla ya existe" << std::endl;
            } catch (excepciones::tablaError) {
                std::cout << "se produjo algun error" << std::endl;
            } catch (excepciones::tablaNoEncuentra) {
                std::cout << "la tabla no se encuentra" << std::endl;
            } catch (excepciones::exesoCampos) {
                std::cout << "los campos no concuerdan" << std::endl;
            } catch (excepciones::campoNoEncuentra) {
                std::cout << "el campo no se encuentra en la tabla" << std::endl;
            }
        } else {
            std::cout << "error lexico" << std::endl;
        }
    }

    return 0;
	
}
#endif