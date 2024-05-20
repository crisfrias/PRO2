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

/*
void Rio::redistribuir_priv(BinTree<string>& t) {
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
*/

// Modificadoras

void Rio::actualizar_ciudad_rio(const string& id_ciudad, const Ciudad& c) {
    mapa_cuenca[id_ciudad] = c;
}

/*
void Rio::redistribuir(Inventario inv) {
	redistribuir_priv(cuenca, inv);
}
*/

// Consultoras

Ciudad Rio::buscar_ciudad(const string& id_ciudad, bool& error) {
    auto it = mapa_cuenca.find(id_ciudad);
    if (it != mapa_cuenca.end()) {
        error = false;
        return mapa_cuenca[id_ciudad];
    }
    else {
        error = true;
        Ciudad c;
        return c;
    }
}

// Lectura y escritura

void Rio::leer_cuenca() {
    leer_cuenca_priv(cuenca, mapa_cuenca);
}

void Rio::leer_inventarios(Inventario inv) {
    string s;
    cin >> s;
    while (s != "#") {
		Ciudad c = mapa_cuenca[s];
		c.leer_inventario_ciudad(inv);
		mapa_cuenca[s] = c;
		cin >> s;
	}
}

