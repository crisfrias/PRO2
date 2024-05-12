#include "Rio.hh"

// Constructoras

Rio::Rio();

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

void Rio::actualizar_ciudad_rio(string id_ciudad, const Ciudad& c);

// Consultoras

Ciudad Rio::buscar_ciudad(const Ciudad& c, bool error);

// Lectura y escritura

void Rio::leer_cuenca() {
    leer_cuenca_priv(cuenca, mapa_cuenca);
}
void Rio::leer_inventarios();

