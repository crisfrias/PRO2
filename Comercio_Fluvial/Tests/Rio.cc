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

pair<pair<int, int>, int > Rio::buscar_ruta(const BinTree<string>& t, const Barco& b, stack<string>& r) {
	// Caso base
    if (t.empty()) return make_pair(make_pair(0, 0),0);

	// Caso general
	string id_ciudad = t.value();
    int id_prod_compra = b.consultar_id_prod_compra();
    int id_prod_venta = b.consultar_id_prod_venta();
    
  

    // Unidades que la ciudad puede comprar al barco
    int sobrante_ciudad = mapa_cuenca[id_ciudad].consultar_reserva(id_prod_compra)-mapa_cuenca[id_ciudad].consultar_faltante(id_prod_compra);
    if (sobrante_ciudad>b.consultar_prod_compra()) sobrante_ciudad=b.consultar_prod_compra();
    if (sobrante_ciudad<0) sobrante_ciudad=0;
    
    // Unidades que la ciudad puede vender al barco
    
    int necesidad_ciudad = mapa_cuenca[id_ciudad].consultar_faltante(id_prod_venta) - mapa_cuenca[id_ciudad].consultar_reserva(id_prod_venta);
    if (necesidad_ciudad>b.consultar_prod_venta()) necesidad_ciudad=b.consultar_prod_venta();
    if (necesidad_ciudad<0) necesidad_ciudad=0;
    
    // Es hoja? Esto nos ayuda a poder asumir que si no se cumple, o t.left() o t.righ() no son vacíos
    if (t.left().empty() and t.right().empty()){
        r.push(id_ciudad);
        return make_pair(make_pair(sobrante_ciudad, necesidad_ciudad), 0 );
    }
    
    // Creamos dos pilas diferentes para conseguir la mejor ruta de t.left() y t.righ()
    stack<string> ruta_l;
    stack<string> ruta_r;
    
    // Conseguimos la mejor ruta (función recursiva)
    pair<pair<int, int>,int > buscar_ruta_l= buscar_ruta(t.left(),b,ruta_l);
    pair<pair<int, int>,int > buscar_ruta_r= buscar_ruta(t.right(),b,ruta_r);
    
    //Casos donde hayamos hecho una ruta vacía
    bool ruta_vacia;
    ruta_vacia= ruta_l.empty() and ruta_r.empty();
    if (not ruta_vacia){
        ruta_vacia= ruta_l.size()<=1 and ruta_r.size()<=1;
        ruta_vacia= ruta_vacia and (buscar_ruta_l.first.first+ buscar_ruta_l.first.second)==0 and (buscar_ruta_r.first.first+ buscar_ruta_r.first.second)==0;
    }
    
    //Es ruta vacía?
    if (ruta_vacia){
        ruta.push(t.value());
        return make_pair(make_pair(sobrante_ciudad, necesidad_ciudad), 0);
    }

    //No es ruta vacía -> tenemos que comprobar cual es mejor
    int sobrantes_l=buscar_ruta_l.first.first;
    int necesidad_l=buscar_ruta_l.first.second;
    int distancia_l=buscar_ruta_l.second;
    int sobrantes_r=buscar_ruta_r.first.first;
    int necesidad_r=buscar_ruta_r.first.second;
    int distancia_r=buscar_ruta_r.second;
    
    
    //Comparamos rutas
    
    bool option_l;
    if ((sobrantes_l+necesidad_l > sobrantes_r+necesidad_r)  or  (sobrantes_l+necesidad_l == sobrantes_r+necesidad_r and distancia_l<=distancia_r)){
        option_l=true;
    }
    else if (sobrantes_l+necesidad_l == sobrantes_r+necesidad_r and distancia_l==distancia_r and ruta_l.size() <= ruta_r.size()){
        option_l=true;
    }
    else option_l=false;
    
    
    //Una vez tenemos la ruta eliminamos las ciudades que no pertenecen a la ruta
    
    int sobrantes_t;
    int faltantes_t;
    int distancia_t;
    
    r.push(t.value());
    if (option_l) {
        while (not ruta_l.empty()) {
            r.push(ruta_l.top());
            r.pop();
        }
        sobrantes_t=min(b.consultar_prod_compra(),(sobrantes_l + sobrante_ciudad));
        faltantes_t=min(b.consultar_prod_venta(),(necesidad_l + necesidad_ciudad));
        distancia_t=distancia_l + 1 ;
    }
    else{
        while (not ruta_r.empty()) {
            r.push(ruta_r.top());
            r.pop();
        }
        sobrantes_t=min(b.consultar_prod_compra(),(sobrantes_r + sobrante_ciudad));
        faltantes_t=min(b.consultar_prod_venta(),(necesidad_r + necesidad_ciudad));
        distancia_t=distancia_r + 1;
    }
    
    // Devolvemos los valores
    return make_pair( make_pair(sobrantes_t , faltantes_t) , distancia_t );
}


int Rio::min(int a, int b){
    if (a<b) return a;
    else return b;
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
	pair<pair<int,int>, int> f = buscar_ruta(cuenca, b, ruta);
	f.first.first = f.first.second;
	
	if (not cuenca.empty()){
        if (not cuenca.left().empty() and cuenca.left().value()==ruta.top()) ruta.push(cuenca.value());
        else if (not cuenca.right().empty() and cuenca.right().value()==ruta.top()) ruta.push(cuenca.value());
    }

	// Calculamos los productos vendidos despueś de hacer el viaje y los devolvemos
	int d = hacer_viaje_priv(b, ruta, inv);
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
