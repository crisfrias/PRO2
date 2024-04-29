#include "Prenda.hh"

// Constructoras

Prenda::Prenda() {
    peso = 0;
    color = false;
}

Prenda::Prenda(int pes, bool col) {
    peso = pes;
    color = col;
}

// Modificadoras

void Prenda::modificar(int pes, bool col) {
    peso = pes;
    color = col;
}

// Consultoras

int Prenda::consul_peso() const {
    return peso;
}

bool Prenda::consul_color() const {
    return color;
}

// Escritura

void Prenda::escribir() const {
    cout << peso << " ";
    if (color == true) cout << "true";
    else cout << "false";
    cout << endl;
}
