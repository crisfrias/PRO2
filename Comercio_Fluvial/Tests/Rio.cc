#include "Rio.hh"

// Constructoras

Rio::Rio() {
}

void Rio::leer_cuenca_priv(BinTree<string>& t, map<string, Ciudad>& m) {
    string s;
    BinTree<string> esq, dre;
    cin >> s;
    if (s != "#") {
        leer_cuenca_priv(esq, m);
        leer_cuenca_priv(dre, m);
        t = BinTree<string> (s, esq, dre);
        Ciudad c(s);
        m[s] = c;
    }
}

void Rio::redistribuir_priv(BinTree<string>& t, const Inventario& inv, map<string, Ciudad>& m) {
	if (t.empty()) return;
	string id_ciudad = t.value();
	if (t.left().empty()) {
		m[id_ciudad].actualizar_ciudad();
		return;
	}
	BinTree<string> esq = t.left();
	BinTree<string> dre = t.right();
	m[id_ciudad].comerciar(m[t.left().value()], inv);
	m[id_ciudad].comerciar(m[t.right().value()], inv);
	m[id_ciudad].actualizar_ciudad();
	redistribuir_priv(esq, inv, m);
	redistribuir_priv(dre, inv, m);
	
	t = BinTree<string> (id_ciudad, esq, dre);
}

int Rio::planear_viaje(const BinTree<string>& t, const Barco& b, stack<string>& r, int& compra_barco, int& venta_barco) {
	// Caso base
	if (t.empty()) return 0;
	if (compra_barco == 0 and venta_barco == 0) return 0;
	// Caso general
	string id_ciudad = t.value();
    int id_prod_compra = b.consultar_id_prod_compra();
    int id_prod_venta = b.consultar_id_prod_venta();
    int sobrante_ciudad = mapa_cuenca[id_ciudad].consultar_reserva(id_prod_compra) - mapa_cuenca[id_ciudad].consultar_faltante(id_prod_compra);
	int necesidad_ciudad = mapa_cuenca[id_ciudad].consultar_faltante(id_prod_venta) - mapa_cuenca[id_ciudad].consultar_reserva(id_prod_venta);
	// Calculo lo que tiene que comprar y vender el nodo actual	
	int compra = 0;
    if (mapa_cuenca[id_ciudad].consultar_producto(id_prod_compra) and compra_barco > 0){
        if (sobrante_ciudad > 0 ) {
			compra = compra_barco; 
			if (sobrante_ciudad < compra) {
				compra = sobrante_ciudad;
				compra_barco -= compra;
			}
			else compra_barco = 0;
		}
    }
    int venta=0;
    if (mapa_cuenca[id_ciudad].consultar_producto(id_prod_venta) and venta_barco > 0){
        if (necesidad_ciudad > 0) {
			venta = venta_barco;
			if (necesidad_ciudad < venta) {
				venta = necesidad_ciudad;
				venta_barco -= venta;
			}
			else venta_barco = 0;
		}
    }
    // Miro cuantas unidades me entran de la ciudad izquiera y derecha por recursion
    BinTree<string> tree_esq = t.left();
	BinTree<string> tree_dre = t.right();
	int compra_esq = compra_barco, compra_dre = compra_barco;
	int venta_esq = venta_barco, venta_dre = venta_barco;
	stack<string> aux_esq, aux_dre;
	int prods_esq = planear_viaje(tree_esq, b, aux_esq, compra_esq, venta_esq);
	int prods_dre = planear_viaje(tree_dre, b, aux_dre, compra_dre, venta_dre);
	// Defino la variable unidades que se encargará de devolver cuántos nodos han sido visitados
	int unidades;
	// Si hay más productos en la izquierda guardo la recursion izquierda
	if (prods_esq > prods_dre) unidades = planear_viaje(tree_esq, b, r, compra_barco, venta_barco);
	// Si hay más en la derecha se guarda la recursion derecha
	else if (prods_esq < prods_dre) unidades = planear_viaje(tree_dre, b, r, compra_barco, venta_barco);
	// Si hay el mismo numero se queda el camino mas corto, que en caso de empate es el izquierdo
	else if (aux_esq.size() > aux_dre.size()) unidades = planear_viaje(tree_dre, b, r, compra_barco, venta_barco);
	else unidades = planear_viaje(tree_esq, b, r, compra_barco, venta_barco);
	// Si el nodo actual no compra ni vende unidades se retorna las unidades de la recursion
	if (compra+venta == 0) return unidades;
	else {
		++unidades;
		r.push(t.value());
		return unidades;
	}
}

int Rio::hacer_viaje_priv(Barco& b, stack<string>& r, const Inventario& inv) {
	// Parámetros iniciales
	int unidades_compra = b.consultar_prod_compra();
	int unidades_venta = b.consultar_prod_venta();
	int id_compra = b.consultar_id_prod_compra();
	int id_venta = b.consultar_id_prod_venta();
	int suma_ops = 0;
	string ultima_ciudad_visitada;
	
	while (not r.empty() and (unidades_compra != 0 or unidades_venta != 0)) {
		string id_ciudad = r.top();
		Ciudad c = mapa_cuenca[id_ciudad];
		// Hacemos la compra
		if (c.consultar_producto(id_compra) and unidades_compra > 0) {
			Producto p1 = inv.devolver_producto(id_compra);
			int sobrante = c.consultar_reserva(id_compra) - c.consultar_faltante(id_compra);
			if (sobrante > 0) {
				if (unidades_compra > sobrante) {
					c.quitar_prod_reserva(p1, sobrante);
					unidades_compra -= sobrante;
					suma_ops += sobrante;
				}
				else {
					c.quitar_prod_reserva(p1, unidades_compra);
					suma_ops += unidades_compra;
					unidades_compra = 0;
				}
			}
			ultima_ciudad_visitada = id_ciudad;
		}
		// Hacemos la venta
		if (c.consultar_producto(id_venta) and unidades_venta > 0) {
			Producto p2 = inv.devolver_producto(id_venta);
			int falta = c.consultar_faltante(id_venta) - c.consultar_reserva(id_venta);
			if (falta > 0) {
				if (unidades_venta > falta) {
					c.anadir_prod_reserva(p2, falta);
					unidades_venta -= falta;
					suma_ops += falta;
				}
				else {
					c.anadir_prod_reserva(p2, unidades_venta);
					suma_ops += unidades_venta;
					unidades_venta = 0;
				}
			}
			ultima_ciudad_visitada = id_ciudad;
		}
		// Actualizamos la ciudad
		c.actualizar_ciudad();
		mapa_cuenca[id_ciudad] = c;
		r.pop();
	}
	// Si es la última ciudad visitada, la añadimos al historial
	b.anadir_ciudad_historial(ultima_ciudad_visitada);
	return suma_ops;
}

// Modificadoras

void Rio::actualizar_ciudad_rio(const string& id_ciudad, const Ciudad& c) {
    mapa_cuenca[id_ciudad] = c;
}

void Rio::redistribuir(const Inventario& inv) {
	redistribuir_priv(cuenca, inv, mapa_cuenca);
}

int Rio::hacer_viaje(Barco& b, const Inventario& inv) {
	// Reinicializamos la pila de la ruta
	stack<string> vacio;
	ruta = vacio;
	// Planeamos la ruta del viaje
	int c1 = b.consultar_prod_compra();
	int c2 = b.consultar_prod_venta();
	int d = planear_viaje(cuenca, b, ruta, c1, c2);
	// Calculamos los productos vendidos despueś de hacer el viaje y los devolvemos
	d = hacer_viaje_priv(b, ruta, inv);
	return d;
}

// Consultoras

Ciudad Rio::buscar_ciudad(const string& id_ciudad, bool& error) {
    auto it = mapa_cuenca.find(id_ciudad);
    if (it != mapa_cuenca.end()) {
        error = false;
        return mapa_cuenca[id_ciudad];
    }
    else {
        error = true;
        Ciudad c;
        return c;
    }
}

// Lectura y escritura

void Rio::leer_cuenca() {
	mapa_cuenca.clear();
	cuenca = BinTree<string> ();
    leer_cuenca_priv(cuenca, mapa_cuenca);
}

void Rio::leer_inventarios(const Inventario& inv) {
    string s;
    cin >> s;
    while (s != "#") {
		Ciudad c;
		c = mapa_cuenca[s];
		c.leer_inventario_ciudad(inv);
		mapa_cuenca[s] = c;
		cin >> s;
	}
}

