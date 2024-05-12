#include "Inventario.hh"

// Constructoras

Inventario::Inventario() {
    ultimo_id = -1;
    tamaño_inventario = 0;
}

Inventario::Inventario(int n) {
    ultimo_id = 1;
    tamaño_inventario = n;
}

// Modificadoras

void Inventario::anadir_producto_nuevo(Producto p) {
    catalogo.push_back(p);
    ++tamano_inventario;
    ultimo_id = catalogo.consultar_ultimo_id();
}

void Inventario::cambiar_producto(Producto p, int peso_nuevo, int volumen_nuevo);

// Consultoras

int Inventario::consultar_ultimo_id() const {
    return catalogo[tamano_inventario-1].consultar_id();
}

int Inventario::consultar_tamano_inventario() const {
	return tamano_inventario;
}

Producto Inventario::consultar_producto(int id_prod, bool& error);

// Lectura y escritura

void Inventario::leer_inventario() {
    for (int i = 0; i < tamaño_inventario; ++i) {
        Producto aux(ultimo_id);
        aux.leer();
        catalogo[i] = aux;
        ++ultimo_id;
    }
}
