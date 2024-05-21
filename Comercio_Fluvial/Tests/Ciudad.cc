#include "Ciudad.hh"

// Constructoras

Ciudad::Ciudad() {
    id_ciudad = "NULL";
    peso_total = 0;
    volumen_total = 0;
}

Ciudad::Ciudad(string id) {
    id_ciudad = id;
    peso_total = 0;
    volumen_total = 0;
}

// Modificadoras

void Ciudad::anadir_prod_reserva(const Producto& p) {
    prods_ciudad[p.consultar_id()].first += 1;
    peso_total += p.consultar_peso();
    volumen_total += p.consultar_vol();
}

void Ciudad::quitar_prod_reserva(const Producto& p) {
	int id_prod = p.consultar_id();
	peso_total -= prods_ciudad[id_prod].first * p.consultar_peso();
	volumen_total -= prods_ciudad[id_prod].first * p.consultar_vol();
	prods_ciudad.erase(id_prod);
}

void Ciudad::anadir_prod_faltante(const Producto& p) {
    prods_ciudad[p.consultar_id()].second += 1;
}

void Ciudad::modificar_producto_reserva(const Producto& p, int reserva, int lista) {
	peso_total -= p.consultar_peso() * prods_ciudad[p.consultar_id()].first;
	volumen_total -= p.consultar_vol() * prods_ciudad[p.consultar_id()].first;
    prods_ciudad[p.consultar_id()] = make_pair(reserva, lista);
    peso_total += reserva * p.consultar_peso();
    volumen_total += reserva * p.consultar_vol();
}

void Ciudad::actualizar_ciudad() {
	for (auto it = prods_ciudad.begin(); it != prods_ciudad.end(); ) {
		if (prods_ciudad[it->first].first == 0) {
            it = prods_ciudad.erase(it); 
        } else {
            ++it;
        }
	}
}

void Ciudad::comerciar(Ciudad& c, Inventario inv) {
	for (auto it = prods_ciudad.begin(); it != prods_ciudad.end(); ++it) {
		// Asignamos un id al producto que estamos tratando
		int id_prod = it->first;
		// Asignamos si a cada ciudad le falta o le sobra el producto
		int unidades1 = prods_ciudad[id_prod].first - prods_ciudad[id_prod].second;
		int unidades2 = c.consultar_reserva(id_prod) - c.consultar_faltante(id_prod);
		Producto p = inv.devolver_producto(id_prod);
		
		if (unidades1 > 0 and unidades2 < 0) {
			int venta = unidades1;
			int nueva_reserva2 = c.consultar_reserva(id_prod) + venta;
			
			peso_total -= p.consultar_peso() * venta;
			volumen_total -= p.consultar_vol() * venta;
			prods_ciudad[id_prod].first -= venta;
			
			c.modificar_producto_reserva(p, nueva_reserva2, c.consultar_faltante(id_prod));
		}
		else if (unidades1 < 0 and unidades2 > 0) {
			int compra = unidades2;
			int nueva_reserva2 = c.consultar_reserva(id_prod) - compra;
			
			peso_total += p.consultar_peso() * compra;
			volumen_total += p.consultar_vol() * compra;
			prods_ciudad[id_prod].first += compra;
			
			c.modificar_producto_reserva(p, nueva_reserva2, c.consultar_faltante(id_prod));
		}
	}
}

// Consultoras

string Ciudad::consultar_id_ciudad() const {
    return id_ciudad;
}

int Ciudad::consultar_peso_total() const {
    return peso_total;
}

int Ciudad::consultar_volumen_total() const {
    return volumen_total;
}

bool Ciudad::consultar_producto(int id_prod) {
	if (prods_ciudad.find(id_prod) == prods_ciudad.end()) return false;
	else return true;
}

int Ciudad::consultar_reserva(int id_prod) {
    return prods_ciudad[id_prod].first;
}

int Ciudad::consultar_faltante(int id_prod) {
    return prods_ciudad[id_prod].second;
}

// Lectura y escritura

void Ciudad::leer_inventario_ciudad(Inventario inv) {
	// Desinicializamos el peso, volumen y catálogo de la ciudad
	prods_ciudad.clear();
	peso_total = 0;
	volumen_total = 0;
	// Miramos cuantos productos nuevos entran en la ciudad
	int nprods;
	cin >> nprods;
	int id, tengo, necesito;
	for (int i = 0; i < nprods; ++i) {
		// Lectura de los parámetros de entrada
		cin >> id >> tengo >> necesito;
		prods_ciudad.insert(make_pair(id, make_pair(tengo, necesito)));
		bool error;
		Producto p;
		p = inv.consultar_producto(id, error);
		if (error) cout << "error: no existe el producto" << endl;
		// Actualización del peso y volumen total del p.i.
		else {
			peso_total += tengo * p.consultar_peso();
			volumen_total += tengo * p.consultar_vol();
		}
	}
}

void Ciudad::escribir() {
    for (auto it = prods_ciudad.begin(); it != prods_ciudad.end(); ++it) {
        cout << it->first << " " << prods_ciudad[it->first].first << " " << prods_ciudad[it->first].second << endl;
    }
    cout << peso_total << " " << volumen_total << endl;
}
