#include "Rio.hh"

// Constructoras

Rio::Rio() {
}

static void Rio::leer_cuenca_priv(BinTree<string>& t, map<string, Ciudad>& m) {
    string s;
    BinTree<string> esq, dre;
    cin >> s;
    if (s != "#") {
        leer_cuenca(esq, mapa_cuenca);
        leer_cuenca(dre, mapa_cuenca);
        t = BinTree<string> (s, esq, dre);
        m[s] = Ciudad c(s);
    }
}

// Modificadoras

void Rio::actualizar_ciudad_rio(const string& id_ciudad, const Ciudad& c) {
    mapa_cuenca[id_ciudad] = c;
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
    
}

