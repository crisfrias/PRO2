#include "Ciudad.hh"

// Constructoras

Ciudad::Ciudad() {
    id_ciudad = "NULL";
    peso_total = 0;
    volumen_total = 0;
}

Ciudad::Ciudad(string id) {
    id_ciudad = id;
    peso_total = 0;
    volumen_total = 0;
}

// Modificadoras

void Ciudad::anadir_prod_reserva(const Producto& p) {
    prods_ciudad[p.consultar_id()].first += 1;
    peso_total += p.consultar_peso();
    volumen_total += p.consultar_vol();
}

void Ciudad::quitar_prod_reserva(const Producto& p) {
	int id_prod = p.consultar_id();
	prods_ciudad.erase(id_prod);
	peso_total -= p.consultar_peso();
	volumen_total -= p.consultar_vol();
}

void Ciudad::anadir_prod_faltante(const Producto& p) {
    prods_ciudad[p.consultar_id()].second += 1;
}

void Ciudad::modificar_producto_reserva(const Producto& p, int reserva, int lista) {
    prods_ciudad[p.consultar_id()] = make_pair(reserva, lista);
}

// Consultoras

string Ciudad::consultar_id_ciudad() const {
    return id_ciudad;
}

int Ciudad::consultar_peso_total() const {
    return peso_total;
}

int Ciudad::consultar_volumen_total() const {
    return volumen_total;
}

int Ciudad::consultar_reserva(int id_prod) {
    return prods_ciudad[id_prod].first;
}

int Ciudad::consultar_faltante(int id_prod) {
    return prods_ciudad[id_prod].second;
}

// Lectura y escritura

void Ciudad::leer_inventario_ciudad() {
	int n;
	cin >> n;
	int id, tengo, necesito;
	for (int i = 0; i < n; ++i) {
		cin >> id >> tengo >> necesito;
		prods_ciudad[id] = make_pair(tengo, necesito);
	}
}

void Ciudad::escribir() {
    for (auto it = prods_ciudad.begin(); it != prods_ciudad.end(); ++it) {
        cout << it->first << " " << prods_ciudad[it->first].first << " " << prods_ciudad[it->first].second << endl;
    }
    cout << peso_total << " " << volumen_total << endl;
}
