#include "Producto.hh"

// Constructoras

Producto::Producto() {
    id = -1;
}

Producto::Producto(string id_prod) {
    id = id_prod;
    peso = 0;
    vol = 0;
}

//Modificadoras

void Producto::cambiar_peso(int p) {
    peso = p;
}

void Producto::cambiar_volumen(int v) {
    vol = v;
}

// Consultoras

int Producto::consultar_id() const {
    return id;
}

int Producto::consultar_peso() const {
    return peso;
}

int Producto::consultar_vol() const {
    return vol;
}

// Lectura y escritura

void Producto::leer() {
    // Leemos peso y volumen
    int p, v;
    std::cin >> p >> v;
    // Asignamos parametros
    peso = p;
    vol = v;
}

void Producto::escribir() const {
    std::cout << id << " " << peso << " " << vol << std::endl;
}
