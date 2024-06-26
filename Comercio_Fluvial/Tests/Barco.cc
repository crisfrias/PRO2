#include "Barco.hh"

// Constructoras

Barco::Barco() {
}

// Modificadoras

void Barco::modificar_barco(int id_compra, int unidades_compra, int id_venta, int unidades_venta) {
	prod_compra = make_pair(id_compra, unidades_compra);
	prod_vender = make_pair(id_venta, unidades_venta);
}

void Barco::reiniciar_barco() {
	list<string> l;
	historial = l;
}

void Barco::anadir_ciudad_historial(const string& s) {
	bool found = false;
	for (auto it = historial.begin(); it != historial.end() and not found; ++it) {
		if (*it == s) return;
	}
	historial.push_back(s);
}

// Consultoras

int Barco::consultar_id_prod_compra() const {
	return prod_compra.first;
}

int Barco::consultar_prod_compra() const {
	return prod_compra.second;
}
    
int Barco::consultar_id_prod_venta() const {
	return prod_vender.first;
}

int Barco::consultar_prod_venta() const {
	return prod_vender.second;
}

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
	for (auto it = historial.begin(); it != historial.end(); ++it) {
		if (it->length()>0) cout << *it << endl;
	}
}
