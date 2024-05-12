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
    v.leer();

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
            string ciudad;
            cin >> ciudad;
            cout << "#" << instr << " " << ciudad << endl;
            bool error;
            r.leer_inventario_ciudad(ciudad, error);
            if (error) cout << "error: no existe la ciudad" << endl;
            /*
            Se leerá el identificador de una ciudad. Si la ciudad no existe
            se escribirá un mensaje de error. Si la ciudad existe, se leerá un número que in-
            dica la cantidad de elementos del inventario y para cada uno de ellos se leerá el
            identificador del producto, cuantas unidades tiene la ciudad y cuantas necesita
            */
        }
        else if (instr == "leer_inventarios" or instr == "ls") {
            cout << "#" << instr << endl;
            r.leer_inventarios();
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
            }
        }
        else if (instr == "escribir_barco" or instr == "eb") {
            b.escribir();
            /*
            Se escriben los cuatro valores mencionados en la anterior ope-
            ración y los viajes realizados, en orden cronológico. Para cada viaje solo se ha de
            escribir la última ciudad visitada de la ruta escogida.
            */
        }
        else if (instr == "consultar_num" or instr == "cn") {
            cout << "#" << instr << " " << endl;
            cout << catalogo.size() << endl;
        }
        else if (instr == "agregar_productos" or instr == "ap") {
            int prod_nuevos;
            cin >> prod_nuevos;
            for (int i = 0; i < prod_nuevos; ++i) {
                Producto p;
                p.leer();
                catalogo.push_back(p);
            }
        }
        else if (instr == "escribir_producto" or instr == "ep") {
            int id_prod;
            cin >> id_prod;
            cout << "#" << instr << " " << id_prod << endl;
            bool error;
            /*
            Se lee el identificador de un producto. Si no existe el pro-
            ducto se escribe un mensaje de error. En caso contrario se escribe el peso y volumen
            del producto (hacerlo con cerca_dic)
            */
        }
        else if (instr == "escribir_ciudad" or instr == "ec") {
            string ciudad;
            cin >> ciudad;
            cout << "#" << instr << " " << ciudad << endl;
            bool error;
            Ciudad tmp = r.buscar_ciudad(ciudad, error);
            if (error) {
                cout << "error: no existe la ciudad" << endl;
            }
            else tmp.escribir();
            /*
            Se leerá el identificador de una ciudad. Si la ciudad no existe
            se escribirá un mensaje de error. Si la ciudad existe, se escribirá su inventario, y el
            peso y el volumen total de los productos almacenados
            */
        }
        else if (instr == "poner_prod" or instr == "pp") {
            string ciudad;
            int id_prod;
            cin >> ciudad >> id_prod;
            cout << "#" << instr << " " << ciudad << " " << id_prod << endl;
            bool error;
            Ciudad tmp = r.buscar_ciudad(ciudad, error);
            if (error) {
                cout << "error: no existe la ciudad" << endl;
            }
            else {
                if (error) {
                    Producto p = // Buscar si existe el producto
                    cout << "error: no existe el producto" << endl;
                }
                else {
                    tmp.anadir_prod_reserva(p);
                }
            }
        }
        else if (instr == "modificar_prod" or instr == "mp") {
            string ciudad;
            int id_prod;
            cin >> ciudad >> id_prod;

            bool error;
            Ciudad tmp = r.buscar_ciudad(ciudad, error);
            Producto p = //Consultar si existe el producto en inventario

            int peso_nuevo, volumen_nuevo;
            cin >> peso_nuevo >> volumen_nuevo;
            tmp.modificar_producto_reserva(p);
        }
        else if (instr == "quitar_prod" or instr == "qp") {
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
            /*
            Se leerá el identificador de una ciudad y de un producto. Si
            el producto no existe escribe un mensaje de error. Si la ciudad no existe, escribe un
            mensaje de error. Si el producto no está en el inventario de la ciudad, escribe un
            mensaje de error. Si no hay errores, se escribe cuantas unidades de ese producto
            tiene y quiere la ciudad.
            */
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
        }
        else {
            string s;
            getline(cin, s);
        }

        cin >> instr;
    }
}
