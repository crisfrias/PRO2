#include "Inventario.hh"

// Constructoras

Inventario::Inventario(int n) {
    ultimo_id = 1;
    tamaño_inventario = n;
}

// Modificadoras

void anadir_producto_nuevo(Producto p) {
    catalogo.push_back(p);
    ++tamano_inventario;
    ultimo_id = catalogo.consultar_ultimo_id();
}

void Inventario::cambiar_producto(Producto p, int peso_nuevo, int volumen_nuevo);

int Inventario::consultar_ultimo_id() {
    return catalogo[tamano_inventario-1].consultar_id();
}

void Inventario::leer_inventario() {
    for (int i = 0; i < tamaño_inventario; ++i) {
        Producto aux(ultimo_id);
        aux.leer();
        catalogo[i] = aux;
        ++ultimo_id;
    }
}