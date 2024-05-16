#include "Barco.hh"

// Constructoras

Barco::Barco();

// Modificadoras

void Barco::modificar_barco(int id_compra, int peso_compra, int id_venta, int peso_venta) {
	prod_compra = make_pair(id_compra, peso_compra);
	prod_vender = make_pair(id_venta, peso_venta);
}

void Barco::reiniciar_barco() {
	list<string> l;
	historial = l;
}

int hacer_viaje();

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
	cout << prod_compra.first << " " << prod_compra.second << endl;
	cout << prod_vender.first << " " << prod_vender.second << endl;
	// ... imprimir historial de viajes
}
