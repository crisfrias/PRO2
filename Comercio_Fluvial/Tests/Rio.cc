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

void Rio::redistribuir_priv(BinTree<string>& t, Inventario inv, map<string, Ciudad>& m) {
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
    
    int d;
    if (t.left().empty()) {
		int compra_dre = compra_barco;
		int venta_dre = venta_barco;
		BinTree<string> tree_dre = t.right();
		d = planear_viaje(tree_dre, b, r, compra_dre, venta_dre);
		if (compra+venta == 0 and compra_dre+venta_dre == 0) return 0;
		r.push(t.value());
	}
	else if (t.right().empty()) {
		int compra_esq = compra_barco;
		int venta_esq = venta_barco;
		BinTree<string> tree_esq = t.left();
		d = planear_viaje(tree_esq, b, r, compra_esq, venta_esq);
		if (compra+venta == 0 and compra_esq+venta_esq == 0) return 0;
		r.push(t.value());
	}
	else {
		BinTree<string> tree_esq = t.left();
		BinTree<string> tree_dre = t.right();
		int compra_esq = compra_barco, compra_dre = compra_barco;
		int venta_esq = venta_barco, venta_dre = venta_barco;
		// Guardamos el resultado de hacer planear_viaje recursivo
		stack<string> aux = r;
		int d1 = planear_viaje(tree_esq, b, r, compra_esq, venta_esq);
		int d2 = planear_viaje(tree_dre, b, r, compra_dre, venta_dre);
		if (compra_esq+venta_esq == 0 and compra_dre+venta_dre == 0 and compra+venta == 0) return 0;
		if (compra_esq+venta_esq > compra_dre+venta_dre) {
			d = d2;
		}
		else if (d1 > d2) {
			d = d2;
		}
		else {
			d = d1;
		}
		r.push(t.value());
	}
	return d+1;
}

/*
pair<int,pair<int,int>> Rio::planear_viaje(const BinTree<string>& t, const Barco& b, stack<string>& r) {
    if (t.empty()) return make_pair(0, make_pair(0,0));
    // Asignamos parámetros iniciales
    string id_ciudad = t.value();
    int id_prod_compra = b.consultar_id_prod_compra();
    int id_prod_venta = b.consultar_id_prod_venta();
    int sobrante_ciudad_compra_barco = mapa_cuenca[id_ciudad].consultar_reserva(id_prod_compra) - mapa_cuenca[id_ciudad].consultar_faltante(id_prod_compra);
    int necesidad_ciudad_venta_barco = mapa_cuenca[id_ciudad].consultar_faltante(id_prod_venta) - mapa_cuenca[id_ciudad].consultar_reserva(id_prod_venta);

    // Se establecen los productos que se van a comprar y vender entre la ciudad y el barco
    int compra = 0;
    if (mapa_cuenca[id_ciudad].consultar_producto(id_prod_compra)){
        if (sobrante_ciudad_compra_barco > 0 ) {
			compra = b.consultar_prod_compra(); 
			if (sobrante_ciudad_compra_barco < compra) compra = sobrante_ciudad_compra_barco;
		}
    }
    int venta=0;
    if (mapa_cuenca[id_ciudad].consultar_producto(id_prod_venta)){
        if (necesidad_ciudad_venta_barco > 0) {
			venta = b.consultar_prod_venta();
			if (necesidad_ciudad_venta_barco < venta) venta = necesidad_ciudad_venta_barco;
		}
    }
	// Si el nodo que buscamos es una "hoja" del árbol, devuelve los valores anteriores
    if (t.left().empty() and t.right().empty()){
        return make_pair(1,make_pair(compra,venta));
    }
	BinTree<string> tree_esq = t.left();
	BinTree<string> tree_dre = t.right();
	// Guardamos el resultado de hacer planear_viaje recursivo
	pair<int,pair<int,int>> esq = planear_viaje(tree_esq, b, r);
	pair<int,pair<int,int>> dre = planear_viaje(tree_dre, b, r);
	cout << t.left().value() << ": el barco le comprara " << esq.second.first << " y vendera " << esq.second.second << endl;
	cout << t.right().value() << ": el barco le comprara " << dre.second.first << " y vendera " << dre.second.second << endl;
	
	// Actualizamos la cantidad de compra
	int compra_esq = esq.second.first;
	if (compra_esq > b.consultar_prod_compra()) compra_esq = b.consultar_prod_compra();
	else if (compra_esq < 0) compra_esq = 0;
	
	int compra_dre = dre.second.first;
	if (compra_dre > b.consultar_prod_compra()) compra_dre = b.consultar_prod_compra();
	else if (compra_dre < 0) compra_dre = 0;
	
	// Actualizamos la cantidad de venta
	int venta_esq = esq.second.second;
	if (venta_esq > b.consultar_prod_venta()) venta_esq = b.consultar_prod_venta();
	else if (venta_esq < 0) venta_esq = 0;
	
	int venta_dre = dre.second.second;
	if (venta_dre > b.consultar_prod_venta()) venta_dre = b.consultar_prod_venta();
	else if (venta_dre < 0) venta_dre = 0;
	
	// Comparamos para ver con que ruta quedarnos
	bool esq_bool = false;
	if ((compra_esq + venta_esq) >= (compra_dre + venta_dre)) {
		esq_bool = true;
		cout << "Es mejor el lado izquierdo pork " << compra_esq + venta_esq << " >= " << compra_dre + venta_dre << endl;
	}
	else if (t.right().empty() and (compra_esq + venta_esq) != 0) {
		esq_bool = true;
		cout << "Es mejor lado izquierdo pork derecha vacia" << endl;
	}
	else if (t.right().empty() and (compra_esq + venta_esq) == 0) return make_pair(1, make_pair(0,0));
	
	// Añadimos la ciudad a la ruta segun sea la izquiera o la derecha y retornamos 
	if (esq_bool) {
		if ((b.consultar_prod_compra() - compra > 0) or (b.consultar_prod_venta() - venta > 0)) {
			r.push(t.left().value());
			cout << "Se ha añadido " << t.left().value() << " a la ruta" << endl; 
		}
		int aux1, aux2;
		aux1 = compra_esq + compra;
		aux2 = venta_esq + venta;
		if (aux1 < b.consultar_prod_compra()) aux1 = b.consultar_prod_compra();
		if (aux2 < b.consultar_prod_venta()) aux2 = b.consultar_prod_venta();
		pair<int,int> aux = make_pair(aux1, aux2); 
		return make_pair(esq.first+1, aux);
	}
	else {
		if ((b.consultar_prod_compra() - compra > 0) or (b.consultar_prod_venta() - venta > 0)) {
			r.push(t.right().value());
			cout << "Se ha añadido " << t.right().value() << " a la ruta" << endl; 
		}
		int aux1, aux2;
		aux1 = compra_dre + compra;
		aux2 = venta_dre + venta;
		if (aux1 < b.consultar_prod_compra()) aux1 = b.consultar_prod_compra();
		if (aux2 < b.consultar_prod_venta()) aux2 = b.consultar_prod_venta(); 
		pair<int,int> aux = make_pair(aux1, aux2); 
		return make_pair(dre.first+1, aux);
	
	}
	return make_pair(0, make_pair(0,0));
}
*/
int Rio::hacer_viaje_priv(Barco& b, stack<string>& r, Inventario inv) {
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

void Rio::redistribuir(Inventario inv) {
	redistribuir_priv(cuenca, inv, mapa_cuenca);
}

int Rio::hacer_viaje(Barco& b, Inventario inv) {
	// Reinicializamos la pila de la ruta
	stack<string> vacio;
	ruta = vacio;
	// Planeamos la ruta del viaje
	// pair<int,pair<int,int>> d = planear_viaje(cuenca, b, ruta);
	int c1 = b.consultar_prod_compra();
	int c2 = b.consultar_prod_venta();
	int d = planear_viaje(cuenca, b, ruta, c1, c2);
	/*
	if (not cuenca.empty()) {
		// Añadimos la cuenca a la ruta 
		if (not cuenca.left().empty() and cuenca.left().value() == ruta.top()) {
			ruta.push(cuenca.value());
		}
		else if (not cuenca.right().empty() and cuenca.right().value() == ruta.top()) {
			ruta.push(cuenca.value());
		}
	}
	*/
	// d.first = d.second.first + d.second.second;
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
    leer_cuenca_priv(cuenca, mapa_cuenca);
}

void Rio::leer_inventarios(Inventario inv) {
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

