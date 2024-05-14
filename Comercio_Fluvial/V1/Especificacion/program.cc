/**
* @mainpage Comercio fluvial
*
*/

#include "Rio.hh"
#include "Ciudad.hh"
#include "Barco.hh"
#include "Inventario.hh"
#include "Producto.hh"

#ifndef NO_DIAGRAM
#include <iostream>
#include <string>
using namespace std;

#endif

/** @brief Programa Principal
*/

int main() {
    // Inicializar inventario global
    int n_prods;
    cin >> n_prods;
    Inventario v(n_prods);
    v.leer_inventario(n_prods);

    // Inicializar la cuenca
    Rio r;
    r.leer_cuenca();
    // Inicializar barco
    Barco b;
    b.leer();

    // Siguientes opciones
    string instr;
    cin >> instr;
    while (instr != "fin") {
        if (instr == "leer_rio" or instr == "lr" ) {
            cout << "#" << instr << endl;
            r.leer_cuenca()
        }
        else if (instr == "leer_inventario" or instr == "li") {
            string id_ciudad;
            cin >> id_ciudad;
            cout << "#" << instr << " " << id_ciudad << endl;
            bool error;
            Ciudad c = r.buscar_ciudad(id_ciudad, error);
            if (error) {
				cout << "error: no existe la ciudad" << endl;
			}
            else {
				c.leer_inventario_ciudad();
				r.actualizar_ciudad_rio(id_ciudad, c);
			}
        }
        else if (instr == "leer_inventarios" or instr == "ls") {
            cout << "#" << instr << endl;
            r.leer_inventarios();
            /*
             * Se leerán los inventarios de ciudades del río. Todas las ciudades existirán. 
             * Los datos del inventario son como en la funcionalidad anterior.
             * No necesariamente todas las ciudades del río tendrán inventario.
             */
        }
        else if (instr == "modificar_barco" or instr == "mb") {
            cout << "#" << instr << endl;
            // Lectura del producto que se quiere comprar
            int id_prod_compra, peso_prod_compra;
            cin >> id_producto >> peso_producto;
            // Lectura del producto que se quiere vender
            int id_prod_venta, peso_prod_venta;
            cin >> id_prod_venta >> peso_prod_venta;
            // Comprovacion de errores previa y/o ejecución de la función
            if (id_prod_compra == id_prod_venta) {
                cout << "error: no se puede comprar y vender el mismo producto" << endl;
            }
            else {
                bool error;
                b.modificar_barco(id_producto, peso_producto, error);
                if (error) cout << "error: no existe el producto" << endl;
                // Actualizar el rio ??
            }
        }
        else if (instr == "escribir_barco" or instr == "eb") {
            b.escribir();
        }
        else if (instr == "consultar_num" or instr == "cn") {
            cout << "#" << instr << " " << endl;
            cout << v.consultar_tamano_inventario << endl;
        }
        else if (instr == "agregar_productos" or instr == "ap") {
            int prod_nuevos;
            cin >> prod_nuevos;
            for (int i = 0; i < prod_nuevos; ++i) {
                Producto p;
                p.leer();
                v.anadir_producto_nuevo(p);
            }
        }
        else if (instr == "escribir_producto" or instr == "ep") {
            int id_prod;
            cin >> id_prod;
            cout << "#" << instr << " " << id_prod << endl;
            bool error;
            Producto p = v.consultar_producto(id_prod, error);
            if (error) {
				cout << "error: no existe el producto" << endl;
			}
			else {
				p.escribir();
			}
        }
        else if (instr == "escribir_ciudad" or instr == "ec") {
            string id_ciudad;
            cin >> id_ciudad;
            cout << "#" << instr << " " << id_ciudad << endl;
            bool error;
            Ciudad c = r.buscar_ciudad(id_ciudad, error);
            if (error) {
                cout << "error: no existe la ciudad" << endl;
            }
            else {
				c.escribir();
			}
        }
        else if (instr == "poner_prod" or instr == "pp") {
            string id_ciudad;
            int id_prod, quiere, tiene;
            cin >> ciudad >> id_prod >> quiere >> tiene;
            cout << "#" << instr << " " << id_ciudad << " " << id_prod << endl;
            bool error;
            Ciudad c = r.buscar_ciudad(id_ciudad, error);
            if (error) {
                cout << "error: no existe la ciudad" << endl;
            }
            else {
                Producto p = v.consultar_producto(id_prod, error);
                if (error) {
                    cout << "error: no existe el producto" << endl;
                }
                else {
                    c.anadir_prod_reserva(p, );
                    r.actualizar_ciudad_rio(id_ciudad, c);
                }
            }
        }
        else if (instr == "modificar_prod" or instr == "mp") {
            string id_ciudad;
            int id_prod;
            cin >> id_ciudad >> id_prod;

            bool error;
            Ciudad c = r.buscar_ciudad(id_ciudad, error);
            if (error) {
				cout << "error: no existe la ciudad" << endl;
			}
			else {
				Producto p = v.consultar_producto(id_prod, error);
				if (error) {
					cout << "error: no existe el producto" << endl;
				}
				else {
					int peso_nuevo, volumen_nuevo;
					cin >> peso_nuevo >> volumen_nuevo;
            		c.modificar_producto_reserva(p, quiere, tiene);
            		r.actualizar_ciudad_rio(id_ciudad, c);
				}
			}
        }
        else if (instr == "quitar_prod" or instr == "qp") {
			string id_ciudad;
			int id_prod;
			cin >> id_ciudad >> id_prod;
            /*
            Se leerá el identificador de una ciudad y de un producto. Si
            el producto no existe escribe un mensaje de error. Si la ciudad no existe, escribe
            un mensaje de error. Si el producto no está en el inventario de la ciudad, escribe
            un mensaje de error. Si no hay errores, se quitan los datos de este producto en la
            ciudad, modificándose el peso y el volumen total si hace falta. Se escribe el peso y
            el volumen total
            */
        }
        else if (instr == "consultar_prod" or instr == "cp") {
			string id_ciudad;
			int id_prod;
			cin >> id_ciudad >> id_prod;

            bool error;
            Producto p = v.consultar_producto(id_prod, error);
            if (error) {
				cout << "error: no existe el producto" << endl;
			}
            else {
                Ciudad c = r.buscar_ciudad(id_ciudad, error);
                if (error) {
				    cout << "error: no existe la ciudad" << endl;
			    }
                else {
                    cout << c.consultar_reserva(id_prod) << " " << c.consultar_faltante(id_prod) << endl;
                }
            }
        }
        else if (instr == "comerciar" or instr == "co") {
            /*
            Se leerán los identificadores de dos ciudades. Si no existen alguna
            de las dos (o las dos), se escribe un mensaje de error. Si las dos ciudades existen se
            intercambian los productos que le sobren a una y necesite la otra
            */
        }
        else if (instr == "redistribuir" or instr == "re") {
            /*
            No se leen datos. La ciudad de la desembocadura comercia con su
            ciudad río arriba a mano derecha y luego con la ciudad río arriba a mano izquierda,
            y así sucesivamente.
            */
        }
        else if (instr == "hacer_viaje" or instr == "hv") {
            /*
            El barco busca la ruta a partir de la desembocadura que le per-
            mita comprar y vender el mayor número posible de productos. En caso que haya
            más de una ruta que lo cumpla, se queda con la más corta, y en caso de que ten-
            gan la misma longitud, se queda con la que viene río arriba a mano derecha. Una
            vez encontrada la ruta, se hace el viaje y se compran y venden los productos a lo
            largo de la ruta, modificándose los inventarios de las ciudades. Se escribe el total
            de unidades de productos compradas y vendidas por el barco.
            */

            // hacer suma de cada prod los que tiene y los que necesita y hacer la diferencia, ej:
            /*
                Ruta_izq = x1+x3+x3+...xn - (y1+y2+y3+...+yn)
                Ruta_derecha = x1'+x2'+x3'+...xn' - (y1'+y2'+y3'+...+ yn')

                Si el peso o volumen max se alcanzan antes de acabar la rama, parar e ir a la siguiente
                Comparar según lo que tiene y lo que le falta
                
            */
        }
        else {
            string s;
            getline(cin, s);
        }

        cin >> instr;
    }
}
