#include "Rio.hh"

// Constructoras

Rio::Rio() {
}

void Rio::leer_cuenca_priv(BinTree<string>& t, map<string, Ciudad>& m) {
    string s;
    BinTree<string> esq, dre;
    cin >> s;
    if (s != "#") {
        leer_cuenca_priv(esq, m);
        leer_cuenca_priv(dre, m);
        t = BinTree<string> (s, esq, dre);
        Ciudad c(s);
        m[s] = c;
    }
}

void Rio::redistribuir_priv(BinTree<string>& t, Inventario inv) {
	if (t.empty()) {
		if (not t.left().empty()) {
			comerciar(t.value(), t.left().value(), inv);
			redistribuir_priv(t.left());
		}
		else if (not t.right().empty()) {
			comerciar(t.value(), t.right().value(), inv);
			redistribuir_priv(t.right());
		}
	}
}

// Modificadoras

void Rio::actualizar_ciudad_rio(const string& id_ciudad, const Ciudad& c) {
    mapa_cuenca[id_ciudad] = c;
}

void Rio::comerciar(const string& s1, const string& s2, Inventario inv) {
	if (inv.consultar_tamano_inventario() == 0) return;
	
	Ciudad c1 = mapa_cuenca[s1];
	int reserva1, faltante1;
	
	Ciudad c2 = mapa_cuenca[s2];
	int reserva2, faltante2;
	
	for (int i = 1 ; i < inv.consultar_tamano_inventario ; ++i) {
		// Producto p = inv.devolver_producto(i);
		reserva1 = c1.consultar_reserva(i);
		faltante1 = c1.consultar_faltante(i);
		
		reserva2 = c2.consultar_reserva(i);
		faltante2 = c2.consultar_faltante(i);
		
		if (not (reserva1 == 0 and reserva2 == 0)) {
			// ...
		}
	}
}

void Rio::redistribuir(Inventario inv) {
	redistribuir_priv(cuenca, inv);
}

// Consultoras

Ciudad Rio::buscar_ciudad(const string& id_ciudad, bool& error) {
    auto it = mapa_cuenca.find(id_ciudad);
    if (it != mapa_cuenca.end()) {
        error = false;
        return mapa_cuenca[id_ciudad];
    }
    else {
        error = true;
        return Ciudad();
    }
}

// Lectura y escritura

void Rio::leer_cuenca() {
    leer_cuenca_priv(cuenca, mapa_cuenca);
}

void Rio::leer_inventarios() {
    string s;
    cin >> s;
    while (s != "#") {
		Ciudad c = mapa_cuenca[s];
		c.leer_inventario_ciudad();
		cin >> s;
	}
}

