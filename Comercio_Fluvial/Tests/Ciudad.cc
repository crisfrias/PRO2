#include "Ciudad.hh"

// Constructoras

Ciudad::Ciudad() {
    id_ciudad = "NULL";
    peso_total = 0;
    volumen_total = 0;
}

Ciudad::Ciudad(const string& id) {
    id_ciudad = id;
    peso_total = 0;
    volumen_total = 0;
}

// Modificadoras

void Ciudad::anadir_prod_reserva(const Producto& p, int unidades) {
    prods_ciudad[p.consultar_id()].first += unidades;
    peso_total += p.consultar_peso() * unidades;
    volumen_total += p.consultar_vol() * unidades;
}

void Ciudad::quitar_prod_reserva(const Producto& p, int unidades) {
	prods_ciudad[p.consultar_id()].first -= unidades;
    peso_total -= p.consultar_peso() * unidades;
    volumen_total -= p.consultar_vol() * unidades;
}

void Ciudad::eliminar_prod_reserva(const Producto& p) {
	int id_prod = p.consultar_id();
	peso_total -= prods_ciudad[id_prod].first * p.consultar_peso();
	volumen_total -= prods_ciudad[id_prod].first * p.consultar_vol();
	prods_ciudad.erase(id_prod);
}

void Ciudad::modificar_producto_reserva(const Producto& p, int reserva, int lista) {
	// Primero quitamos el peso y volumen que ocupaba el producto p en el inventario
	peso_total -= p.consultar_peso() * prods_ciudad[p.consultar_id()].first;
	volumen_total -= p.consultar_vol() * prods_ciudad[p.consultar_id()].first;
	// Actualizamos cantidad de producto que tiene y que necesita, además del peso y volumen que ocupan
    prods_ciudad[p.consultar_id()] = make_pair(reserva, lista);
    peso_total += reserva * p.consultar_peso();
    volumen_total += reserva * p.consultar_vol();
}

void Ciudad::actualizar_ciudad() {
	for (auto it = prods_ciudad.begin(); it != prods_ciudad.end(); ) {
		// Si la reserva y lo que necesita = 0, entonces lo borra
		if (prods_ciudad[it->first].first == 0 and prods_ciudad[it->first].second == 0) {
            it = prods_ciudad.erase(it); 
        } else {
			// Sino, pasa al siguiente
            ++it;
        }
	}
}

void Ciudad::comerciar(Ciudad& c, const Inventario& inv) {
	for (auto it = prods_ciudad.begin(); it != prods_ciudad.end(); ++it) {
		// Asignamos un id al producto que estamos tratando
		int id_prod = it->first;
		// Asignamos si a cada ciudad le falta o le sobra el producto
		int unidades1 = prods_ciudad[id_prod].first - prods_ciudad[id_prod].second;
		int unidades2 = c.consultar_reserva(id_prod) - c.consultar_faltante(id_prod);
		Producto p = inv.devolver_producto(id_prod);
		
		if (unidades1 > 0 and unidades2 < 0) {
			// Multiplicamos por -1 para obtener el valor absoluto de las unidades
			unidades2 = -1 * unidades2;
			int venta;
			// Si necesita más de las que puede dar, da todas las que puede, sino da todas las que necesita
			if (unidades1 < unidades2) venta = unidades1;
			else venta = unidades2;
			
			peso_total -= p.consultar_peso() * venta;
			volumen_total -= p.consultar_vol() * venta;
			prods_ciudad[id_prod].first -= venta;
			
			c.anadir_prod_reserva(p, venta);
		}
		else if (unidades1 < 0 and unidades2 > 0) {
			// Repetimos el proceso anterior pero cambiando unidades1 por unidades2
			unidades1 = -1 * unidades1;
			int compra;
			if (unidades2 < unidades1) compra = unidades2;
			else compra = unidades1;
			
			peso_total += p.consultar_peso() * compra;
			volumen_total += p.consultar_vol() * compra;
			prods_ciudad[id_prod].first += compra;
			
			c.quitar_prod_reserva(p, compra);
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
	else if (prods_ciudad[id_prod].first == 0 or prods_ciudad[id_prod].second == 0) {
		// Actualizamos ciudad por si acaso, ya que si la condición de arriba lo cumplen los dos se tiene que actualizar
		actualizar_ciudad();
		return false;
	}
	else return true;
}

int Ciudad::consultar_reserva(int id_prod) {
    return prods_ciudad[id_prod].first;
}

int Ciudad::consultar_faltante(int id_prod) {
    return prods_ciudad[id_prod].second;
}

// Lectura y escritura

void Ciudad::leer_inventario_ciudad(const Inventario& inv) {
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
	// Escribimos el inventario de la ciudad
    for (auto it = prods_ciudad.begin(); it != prods_ciudad.end(); ++it) {
		cout << it->first << " " << prods_ciudad[it->first].first << " " << prods_ciudad[it->first].second << endl;
    }
    // Escribimos el peso y volumen total
    cout << peso_total << " " << volumen_total << endl;
}
