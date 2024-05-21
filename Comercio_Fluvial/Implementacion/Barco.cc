#include "Barco.hh"

// Constructoras

Barco::Barco() {
}

// Modificadoras

void Barco::modificar_barco(int id_compra, int peso_compra, int id_venta, int peso_venta) {
	prod_compra = make_pair(id_compra, peso_compra);
	prod_vender = make_pair(id_venta, peso_venta);
}

void Barco::reiniciar_barco() {
	list<string> l;
	historial = l;
}

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
                
*
int hacer_viaje();
*/

// Consultoras

// Lectura y escritura

void Barco::leer() {
	int id_prod;
	int unidades;
	// Se lee qué producto quiere comprar y cuánto
	cin >> id_prod >> unidades;
	prod_compra = make_pair(id_prod, unidades);
	
	// Se lee qué producto quiere vender y cuánto
	cin >> id_prod >> unidades;
	prod_vender = make_pair(id_prod, unidades);
}

void Barco::escribir() const {
	cout << prod_compra.first << " " << prod_compra.second << " ";
	cout << prod_vender.first << " " << prod_vender.second << endl;
	// ... imprimir historial de viajes
}
