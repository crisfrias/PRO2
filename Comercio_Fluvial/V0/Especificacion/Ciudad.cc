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

void Ciudad::anadir_prod_reserva(const Producto& p);

void Ciudad::anadir_prod_faltante(const Producto& p);

// Consultoras

string Ciudad::consultar_id_ciudad() const {
    return id;
}

int Ciudad::consultar_peso_total() const {
    return peso_total;
}

int Ciudad::consultar_volumen_total() const;

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

void Ciudad::escribir() const;
