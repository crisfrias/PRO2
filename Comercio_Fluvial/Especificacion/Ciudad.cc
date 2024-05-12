#include "Ciudad.hh"

Ciudad::Ciudad() {
    id_ciudad = "NULL";
}

Ciudad::Ciudad(string id) {
    id_ciudad = id;
}

string Ciudad::consultar_id_ciudad() const {
    return id;
}

int Ciudad::consultar_peso_total() const {
    return peso_total;
}

void Ciudad::leer_inventario(string id_ciudad) {

}

void Ciudad::leer() {
    string s;
    cin >> s;
    id = s
}

void Ciudad::escribir() const {

}
