// #include "Ventana.h"
// #include <windows.h>
#include "Tabla.h"
#include "AnalizadorSintactico.h"


// int WINAPI WinMain(	HINSTANCE hInst,HINSTANCE hPrevInst,
// 				   char* cmdParam,int cmdShow)
int main()
{

	// Ventana ven(procesos,"Mi Ventana",hInst);
	// ven.crearVentana(750,500);
	// ven.mostrar(cmdShow);
	
	// return ven.cicloMensaje();

    // string cadena = "CREATE TABLE MyTable (name text(10), age text(4))";
    // string cadena = "INSERT INTO MyTable VALUES('Mikel', '12')";
    // string cadena = "INSERT INTO MyTable VALUES('Rat', '11')";
    // string cadena = "INSERT INTO MyTable VALUES('jarni', '9')";
    // string cadena = "INSERT INTO MyTable VALUES('Nayeli', '13')";
    // string cadena = "INSERT INTO MyTable VALUES('Stive', '21')";
    // string cadena = "INSERT INTO MyTable VALUES('Rosa', '31')";
    // string cadena = "INSERT INTO MyTable VALUES('Rocko', '1')";
    // string cadena = "SELECT * FROM MyTable WHERE name='Rat'";
    // string cadena = "SELECT * FROM MyTable";

    ifstream sqlFile;
    sqlFile.open ("sql.txt");
    string cadena;

    getline( sqlFile, cadena );

    static AnalizadorLexico lexico;
    static AnalizadorSintactico sintactico;
    static Tabla tabla;

    // int longitud =strlen(cadena);

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