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

// Consultoras

void buscar_ciudad(Ciudad& c, bool& error) {

}

void Rio::leer_inventario_ciudad(string id_ciudad, bool& error) {

}

void leer_inventarios() {

}

// Lectura y escritura

Rio::leer_cuenca() {
    leer_cuenca_priv(cuenca, mapa_cuenca);
}
