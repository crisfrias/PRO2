#include "Ciudad.hh"

Ciudad::Ciudad() {
    id = "NULL";
}

Ciudad::Ciudad(string id_ciudad) {
    id = id_ciudad;
}

string Ciudad::consultar_id_ciudad() const {
    return id;
}

void Ciudad::leer_inventario(string id_ciudad) {

}

void Ciudad::leer() {
    
}

void Ciudad::escribir() const {

}
