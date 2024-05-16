#include "Inventario.hh"

// Constructoras

Inventario::Inventario() {
    ultimo_id = -1;
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
    int esq = 0, dre = catalogo.size();
    int i = busqueda_elemento(catalogo, esq, dre, id_prod);
    p.cambiar_peso(peso_nuevo);
    p.cambiar_volumen(volumen_nuevo);
    catalogo[i] = p;
}

// Consultoras

int Inventario::consultar_ultimo_id() const {
    return catalogo[tamano_inventario-1].consultar_id();
}

int Inventario::consultar_tamano_inventario() const {
	return tamano_inventario;
}

Producto Inventario::consultar_producto(int id_prod, bool& error) {
    int esq = 0, dre = catalogo.size();
    int i = busqueda_elemento(catalogo, esq, dre, id_prod);
    if (id_prod == catalogo[i].consultar_id()) {
        error = true;
        return catalogo[i];
    }
    else {
        error = true;
        return Producto();
    }
}

Producto Inventario::devolver_producto(int id_prod) {
	return catalogo[id_prod];
}

int Inventario::busqueda_elemento(const vector<Producto>& v, int esq, int dre, int id_prod) {
    int i;
    bool found = false;
    while (esq <= dre and not found) {
        i = (esq+dre)/2;
        if (id_prod < v[i].consultar_id()) dre = i-1;
        else if (id_prod > v[i].consultar_id()) esq = i+1;
        else found = true;
    }
    if (found) return i;
    else return esq;
}

// Lectura y escritura

void Inventario::leer_inventario() {
    for (int i = 0; i < tamano_inventario; ++i) {
        Producto aux(ultimo_id);
        aux.leer();
        catalogo[i] = aux;
        ++ultimo_id;
    }
}
