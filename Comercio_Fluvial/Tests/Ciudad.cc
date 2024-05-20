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
	peso_total -= p.consultar_peso() * prods_ciudad[p.consultar_id()].first;
    prods_ciudad[p.consultar_id()] = make_pair(reserva, lista);
    peso_total += reserva * p.consultar_peso();
}

/*
void Ciudad::comerciar(Ciudad& c);
*/

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

void Ciudad::leer_inventario_ciudad(Inventario inv) {
	// Desinicializamos el peso, volumen y catálogo de la ciudad
	prods_ciudad.clear();
	peso_total = 0;
	volumen_total = 0;
	// Miramos cuantos productos nuevos entran en la ciudad
	int nprods;
	cin >> nprods;
	int id, tengo, necesito;
	for (int i = 0; i < nprods; ++i) {
		// Lectura de los parámetros de entrada
		cin >> id >> tengo >> necesito;
		prods_ciudad.insert(make_pair(id, make_pair(tengo, necesito)));
		bool error;
		Producto p;
		p = inv.consultar_producto(id, error);
		if (error) cout << "error: no existe el producto" << endl;
		// Actualización del peso y volumen total del p.i.
		else {
			peso_total += tengo * p.consultar_peso();
			volumen_total += tengo * p.consultar_vol();
		}
	}
}

void Ciudad::escribir() {
    for (auto it = prods_ciudad.begin(); it != prods_ciudad.end(); ++it) {
        cout << it->first << " " << prods_ciudad[it->first].first << " " << prods_ciudad[it->first].second << endl;
    }
    cout << peso_total << " " << volumen_total << endl;
}
