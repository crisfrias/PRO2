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

void Rio::redistribuir_priv(BinTree<string>& t, Inventario inv, map<string, Ciudad>& m) {
	if (t.empty()) return;
	string id_ciudad = t.value();
	if (t.left().empty()) {
		m[id_ciudad].actualizar_ciudad();
		return;
	}
	BinTree<string> esq = t.left();
	BinTree<string> dre = t.right();
	m[id_ciudad].comerciar(m[t.left().value()], inv);
	m[id_ciudad].comerciar(m[t.right().value()], inv);
	m[id_ciudad].actualizar_ciudad();
	redistribuir_priv(esq, inv, m);
	redistribuir_priv(dre, inv, m);
	
	t = BinTree<string> (id_ciudad, esq, dre);
}

// Modificadoras

void Rio::actualizar_ciudad_rio(const string& id_ciudad, const Ciudad& c) {
    mapa_cuenca[id_ciudad] = c;
}

void Rio::redistribuir(Inventario inv) {
	redistribuir_priv(cuenca, inv, mapa_cuenca);
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
        Ciudad c;
        return c;
    }
}

// Lectura y escritura

void Rio::leer_cuenca() {
	mapa_cuenca.clear();
    leer_cuenca_priv(cuenca, mapa_cuenca);
}

void Rio::leer_inventarios(Inventario inv) {
    string s;
    cin >> s;
    while (s != "#") {
		Ciudad c;
		c = mapa_cuenca[s];
		c.leer_inventario_ciudad(inv);
		mapa_cuenca[s] = c;
		cin >> s;
	}
}

