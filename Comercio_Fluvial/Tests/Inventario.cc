#include "Inventario.hh"

// Constructoras

Inventario::Inventario() {
    ultimo_id = 1;
    tamano_inventario = 0;
}

Inventario::Inventario(int n) {
    ultimo_id = 1;
    tamano_inventario = n;
}

// Modificadoras

void Inventario::anadir_producto_nuevo(const Producto& p) {
    catalogo.push_back(p);
    ++tamano_inventario;
    ++ultimo_id;
}

void Inventario::cambiar_producto(Producto p, int peso_nuevo, int volumen_nuevo) {
    int id_prod = p.consultar_id();
    p.cambiar_peso(peso_nuevo);
    p.cambiar_volumen(volumen_nuevo);
    catalogo[id_prod-1] = p;
}

// Consultoras

int Inventario::consultar_tamano_inventario() const {
	return tamano_inventario;
}

Producto Inventario::consultar_producto(int id_prod, bool& error) const {
    if (id_prod <= tamano_inventario) {
        error = false;
        return catalogo[id_prod-1];
    }
    else {
		error = true;
		Producto p;
        return p;
	}
}

Producto Inventario::devolver_producto(int id_prod) const {
	return catalogo[id_prod-1];
}

// Lectura y escritura

void Inventario::leer_inventario() {
	catalogo.clear();
	peso_inventario = 0;
	volumen_inventario = 0;
	cin >> tamano_inventario;
	int i;
    for (i = 0; i < tamano_inventario; ++i) {
        Producto aux(i+1);
        aux.leer();
        catalogo.push_back(aux);
    }
}
