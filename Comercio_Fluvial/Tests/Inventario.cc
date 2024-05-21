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

Producto Inventario::devolver_producto(int id_prod) {
	return catalogo[id_prod-1];
}

int Inventario::busqueda_elemento(const vector<Producto>& v, int esq, int dre, int id_prod) {
    int i = esq;
    bool found = false;
    while (esq <= dre and not found) {
        i = (esq+dre)/2;
        if (id_prod < v[i].consultar_id()) dre = i-1;
        else if (id_prod > v[i].consultar_id()) esq = i+1;
        else found = true;
    }
    if (found) return i;
    else return v.size();
}

// Lectura y escritura

void Inventario::leer_inventario() {
	cin >> tamano_inventario;
	int i;
    for (i = 0; i < tamano_inventario; ++i) {
        Producto aux(i+1);
        aux.leer();
        catalogo.push_back(aux);
    }
    ultimo_id = tamano_inventario;
}
