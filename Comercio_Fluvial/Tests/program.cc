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
            bool error;
            Ciudad c = r.buscar_ciudad(id_ciudad, error);
            if (error) {
				cout << "error: no existe la ciudad" << endl;
				string s;
				for (int i = 0; i < 3; ++i) getline(cin, s);
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
            int id_prod_compra, peso_prod_compra;
            cin >> id_prod_compra >> peso_prod_compra;
            
            // Lectura del producto que se quiere vender
            int id_prod_venta, peso_prod_venta;
            cin >> id_prod_venta >> peso_prod_venta;
            
            // Comprovacion de errores previa y/o ejecución de la función
            if (id_prod_compra == id_prod_venta) {
                cout << "error: no se puede comprar y vender el mismo producto" << endl;
            }
            else {
                bool error;
                Producto aux;
                aux = v.consultar_producto(id_prod_compra, error);
                if (error) {
					cout << "error: no existe el producto" << endl;
				}
				else {
					aux = v.consultar_producto(id_prod_venta, error);
					if (error) {
						cout << "error: no existe el producto" << endl;
					}
					else {
						b.modificar_barco(id_prod_compra, peso_prod_compra, id_prod_venta, peso_prod_venta);
					}
				}
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
				int id_prod = v.consultar_tamano_inventario()+1;
                Producto p(id_prod);
                p.leer();
                v.anadir_producto_nuevo(p);
            }
        }
        else if (instr == "escribir_producto" or instr == "ep") {
            int id_prod;
            cin >> id_prod;
            cout << "#" << instr << " " << id_prod << endl;
            
            if (id_prod > v.consultar_tamano_inventario()) {
				cout << "error: no existe el producto" << endl;
			}
			else {
				Producto p = v.devolver_producto(id_prod);
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
            cin >> id_ciudad >> id_prod >> tiene >> quiere;
            cout << "#" << instr << " " << id_ciudad << " " << id_prod << endl;
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
						c.quitar_prod_reserva(p);
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
			/*
			cout << "#" << instr << endl;
			int unidades = b.hacer_viaje();
			cout << unidades << endl;
			*/
			cout << "Vacio" << endl;
        }
        else if (instr == "//"){
            string s;
            getline(cin, s);
        }

        cin >> instr;
    }
}
