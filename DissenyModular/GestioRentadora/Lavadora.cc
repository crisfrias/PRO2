#include "Lavadora.hh"

// Constructoras

Lavadora::Lavadora() {
	ini = false;
	pes = 0;
}

// Modificadoras

void Lavadora::inicializar(int pmax, bool col) {
	pesmax = pmax;
	this->col = col;
}

void Lavadora::anadir_prenda(const Prenda& p) {
	prendas.push_back(p);
	pes += p.consul_peso();
}

void Lavadora::lavado() {
	ini = false;
	pes = 0;
	pesmax = 0;
	list<Prenda> aux;
	prendas = aux;
}

// Consultoras

bool Lavadora::esta_inicializada() const {
	return ini;
}

bool Lavadora::consultar_color() const {
	return col;
}

int Lavadora::consultar_peso() const {
	return pes;
}

int Lavadora::consultar_peso_maximo() const {
	return pesmax;
}

// Escritura

void Lavadora::escribir() const {
	if (pesmax == 0) {
		cout << "Lavadora no inicializada" << endl;
	}
	else {
		cout << "Lavadora de ";
		
		if (col == false) cout << "blanco,";
		else cout << "color,";
		
		cout << " con peso actual de " << pes << " y peso maximo " << pesmax << "; ";
		cout << "sus prendas son" << endl;
		
		if (prendas.empty()) return;
		for (auto it = prendas.begin(); it != prendas.end(); ++it) {
			it->escribir();
		}
	}
}
