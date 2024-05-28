/** @mainpage Comercio Fluvial - Práctica PRO2 - Primavera 2024

## Introducción
Se trata de simular el comercio en una cuenca fluvial con varias ciudades ubicadas en las fuentes y en las uniones de los afluentes de un río. Las ciudades comercian productos identificados por números, cada uno con atributos de peso y volumen.

## Formato de Entrada/Salida
- La entrada puede incluir comentarios que comienzan con "//".
- Las operaciones verifican y gestionan posibles errores, imprimiendo mensajes cuando corresponda.

## Estructura de la Cuenca
- Las aguas fluyen de sur a norte.
- La desembocadura está al norte y las fuentes al sur.
- Las ciudades en la cuenca están en las fuentes y en las uniones de los afluentes.
- Cada ciudad tiene dos ciudades "siguientes" río arriba.

## Comercio
- Cada ciudad tiene un inventario de productos con cantidades disponibles y necesarias.
- Un barco comercial realiza viajes para vender y comprar productos entre las ciudades.
- El barco no puede vender y comprar el mismo producto en un viaje.

## Operaciones Principales
1. **leer_rio**: Leer la estructura de la cuenca.
2. **leer_inventario**: Leer el inventario de una ciudad específica.
3. **leer_inventarios**: Leer los inventarios de varias ciudades.
4. **modificar_barco**: Modificar los datos del barco (productos a comprar y vender).
5. **escribir_barco**: Escribir los datos del barco y los viajes realizados.
6. **consultar_num**: Consultar la cantidad de productos diferentes.
7. **agregar_productos**: Añadir nuevos productos al sistema.
8. **escribir_producto**: Escribir los datos de un producto específico.
9. **escribir_ciudad**: Escribir los datos de una ciudad.
10. **poner_prod**: Añadir un producto al inventario de una ciudad.
11. **modificar_prod**: Modificar los datos de un producto en una ciudad.
12. **quitar_prod**: Eliminar un producto del inventario de una ciudad.
13. **consultar_prod**: Consultar los datos de un producto en una ciudad.
14. **comerciar**: Dos ciudades intercambian productos.
15. **redistribuir**: Redistribuir productos a lo largo del río desde la desembocadura.
16. **hacer_viaje**: El barco realiza un viaje para comprar y vender productos.
17. **fin**: Finaliza la ejecución del programa.

## Operaciones Complejas
- **Comerciar**: Dos ciudades intercambian productos que les sobran para satisfacer necesidades mutuas.
- **Redistribuir**: Comercio entre ciudades consecutivas desde la desembocadura hacia las fuentes.
- **Viajar**: El barco realiza un viaje para comprar y vender productos por la ruta donde maximice el beneficio.
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
    Inventario v;
    v.leer_inventario();

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
            r.leer_cuenca();
            b.reiniciar_barco();
        }
        else if (instr == "leer_inventario" or instr == "li") {
            string id_ciudad;
            cin >> id_ciudad;
            cout << "#" << instr << " " << id_ciudad << endl;
            // Comprovación de errores
            bool error;
            Ciudad c = r.buscar_ciudad(id_ciudad, error);
            if (error) {
				cout << "error: no existe la ciudad" << endl;
				// Getline de todo lo siguiente porque no es válido
				int n;
				cin >> n;
				if (n != 0) {
					string s;
					for (int i = 0; i < n; ++i) getline(cin, s);
				}
			}
            else {
				c.leer_inventario_ciudad(v);
				r.actualizar_ciudad_rio(id_ciudad, c);
			}
        }
        else if (instr == "leer_inventarios" or instr == "ls") {
            cout << "#" << instr << endl;
            r.leer_inventarios(v);
        }
        else if (instr == "modificar_barco" or instr == "mb") {
            cout << "#" << instr << endl;
            
            // Lectura del producto que se quiere comprar
            int id_prod_compra, unidades_prod_compra;
            cin >> id_prod_compra >> unidades_prod_compra;
            
            // Lectura del producto que se quiere vender
            int id_prod_venta, unidades_prod_venta;
            cin >> id_prod_venta >> unidades_prod_venta;
            
            // Comprovacion de errores previa y/o ejecución de la función
            if (id_prod_compra <= 0 or id_prod_venta <= 0) {
				cout << "error: no existe el producto" << endl;
			}
			else if (id_prod_compra > v.consultar_tamano_inventario() or id_prod_venta > v.consultar_tamano_inventario()) {
				cout << "error: no existe el producto" << endl;
			}
			else if (id_prod_compra == id_prod_venta) {
                cout << "error: no se puede comprar y vender el mismo producto" << endl;
            }
            else {
				// Llamada a la función
                Producto aux;
                aux = v.devolver_producto(id_prod_compra);
                b.modificar_barco(id_prod_compra, unidades_prod_compra, id_prod_venta, unidades_prod_venta);
            }
        }
        else if (instr == "escribir_barco" or instr == "eb") {
			cout << "#" << instr << endl;
            b.escribir();
        }
        else if (instr == "consultar_num" or instr == "cn") {
            cout << "#" << instr << endl;
            cout << v.consultar_tamano_inventario() << endl;
        }
        else if (instr == "agregar_productos" or instr == "ap") {
            int prod_nuevos;
            cin >> prod_nuevos;
            cout << "#" << instr << " " << prod_nuevos << endl;
            for (int i = 0; i < prod_nuevos; ++i) {
				// El identificador del último producto coincide con el tamaño del inventario, así que le sumamos
				// uno para obtener cual será el siguiente
				int id_prod = v.consultar_tamano_inventario()+1;
				// Inicializamos el producto
                Producto p(id_prod);
                // Leemos el producto
                p.leer();
                // Lo añadimos al inventario y se actualizará el tamaño
                v.anadir_producto_nuevo(p);
            }
        }
        else if (instr == "escribir_producto" or instr == "ep") {
            int id_prod;
            cin >> id_prod;
            cout << "#" << instr << " " << id_prod << endl;
            // Comprovación de errores
            if (id_prod <= 0 or id_prod > v.consultar_tamano_inventario()) {
				cout << "error: no existe el producto" << endl;
			}
			else {
				// Llamada a función
				Producto p = v.devolver_producto(id_prod);
				p.escribir();
			}
        }
        else if (instr == "escribir_ciudad" or instr == "ec") {
            string id_ciudad;
            cin >> id_ciudad;
            cout << "#" << instr << " " << id_ciudad << endl;
            // Comprovación de errores
            bool error;
            Ciudad c = r.buscar_ciudad(id_ciudad, error);
            if (error) {
                cout << "error: no existe la ciudad" << endl;
            }
            else {
				// Llamada a función
				c.escribir();
			}
        }
        else if (instr == "poner_prod" or instr == "pp") {
            string id_ciudad;
            int id_prod, quiere, tiene;
            cin >> id_ciudad >> id_prod >> tiene >> quiere;
            cout << "#" << instr << " " << id_ciudad << " " << id_prod << endl;
            // Comprovación de errores
            bool error;
            Producto p;
			p = v.consultar_producto(id_prod, error);
			if (error) {
				cout << "error: no existe el producto" << endl;
			}
			else {
				Ciudad c = r.buscar_ciudad(id_ciudad, error);
				if (error) {
					cout << "error: no existe la ciudad" << endl;
				}
				else {
					if (c.consultar_producto(id_prod)) {
						cout << "error: la ciudad ya tiene el producto" << endl;
					}
					else {
						// Llamada a la función
						c.modificar_producto_reserva(p, tiene, quiere);
						r.actualizar_ciudad_rio(id_ciudad, c);
						cout << c.consultar_peso_total() << " " << c.consultar_volumen_total() << endl;
					}
				}
			}
        }
        else if (instr == "modificar_prod" or instr == "mp") {
            string id_ciudad;
            int id_prod, tiene, quiere;
            cin >> id_ciudad >> id_prod >> tiene >> quiere;
			cout << "#" << instr << " " << id_ciudad << " " << id_prod << endl;
			// Comprovación de errores
            bool error;
            Producto p;
			p = v.consultar_producto(id_prod, error);
			if (error) {
				cout << "error: no existe el producto" << endl;
			}
			else {
				Ciudad c = r.buscar_ciudad(id_ciudad, error);
				if (error) {
					cout << "error: no existe la ciudad" << endl;
				}
				else {
					if (not c.consultar_producto(id_prod)) {
						cout << "error: la ciudad no tiene el producto" << endl;
					}
					else {
						// Llamada a la función
						c.modificar_producto_reserva(p, tiene, quiere);
						r.actualizar_ciudad_rio(id_ciudad, c);
						cout << c.consultar_peso_total() << " " << c.consultar_volumen_total() << endl;
					}
				}
			}
        }
        else if (instr == "quitar_prod" or instr == "qp") {
			string id_ciudad;
			int id_prod;
			cin >> id_ciudad >> id_prod;
			cout << "#" << instr << " " << id_ciudad << " " << id_prod << endl;
			// Comprovación de errores
			bool error;
            Producto p;
			p = v.consultar_producto(id_prod, error);
			if (error) {
				cout << "error: no existe el producto" << endl;
			}
			else {
				Ciudad c = r.buscar_ciudad(id_ciudad, error);
				if (error) {
					cout << "error: no existe la ciudad" << endl;
				}
				else {
					if (not c.consultar_producto(id_prod)) {
						cout << "error: la ciudad no tiene el producto" << endl;
					}
					else {
						// Llamada a la función
						c.eliminar_prod_reserva(p);
						r.actualizar_ciudad_rio(id_ciudad, c);
						cout << c.consultar_peso_total() << " " << c.consultar_volumen_total() << endl;
					}
				}
			}
        }
        else if (instr == "consultar_prod" or instr == "cp") {
			string id_ciudad;
			int id_prod;
			cin >> id_ciudad >> id_prod;
			cout << "#" << instr << " " << id_ciudad << " " << id_prod << endl;
			// Comprovación de errores
            bool error;
            Producto p;
			p = v.consultar_producto(id_prod, error);
			if (error) {
				cout << "error: no existe el producto" << endl;
			}
			else {
				Ciudad c = r.buscar_ciudad(id_ciudad, error);
				if (error) {
					cout << "error: no existe la ciudad" << endl;
				}
				else {
					if (c.consultar_producto(id_prod)) {
						// Llamada a la función
						cout << c.consultar_reserva(id_prod) << " " << c.consultar_faltante(id_prod) << endl;
					}
					else {
						cout << "error: la ciudad no tiene el producto" << endl;
					}
				}
			}
        }
        else if (instr == "comerciar" or instr == "co") {
			string id_ciudad1, id_ciudad2;
			cin >> id_ciudad1 >> id_ciudad2;
			cout << "#" << instr << " " << id_ciudad1 << " " << id_ciudad2 << endl;
			// Comprovación de errores
			if (id_ciudad1 == id_ciudad2) {
				cout << "error: ciudad repetida" << endl;
			}
			else {
				bool error;
				Ciudad c1 = r.buscar_ciudad(id_ciudad1, error);
				if (error) {
					cout << "error: no existe la ciudad" << endl;
				}
				else {
					Ciudad c2 = r.buscar_ciudad(id_ciudad2, error);
					if (error) {
						cout << "error: no existe la ciudad" << endl;
					}
					else {
						// Llamada a la función
						c1.comerciar(c2, v);
						c1.actualizar_ciudad();
						c2.actualizar_ciudad();
						r.actualizar_ciudad_rio(id_ciudad1, c1);
						r.actualizar_ciudad_rio(id_ciudad2, c2);
					}
				}
			}
        }
        else if (instr == "redistribuir" or instr == "re") {
			cout << "#" << instr << endl;
			r.redistribuir(v);
        }
        else if (instr == "hacer_viaje" or instr == "hv") {
			cout << "#" << instr << endl;
			cout << r.hacer_viaje(b, v) << endl;
        }
        else if (instr == "//"){
            string s;
            getline(cin, s);
        }

        cin >> instr;
    }
}
