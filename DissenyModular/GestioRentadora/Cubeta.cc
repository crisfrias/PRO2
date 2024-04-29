#include "Cubeta.hh"

// Constructuras

Cubeta::Cubeta() {
    stack<Prenda> aux;
    ropablanca = aux;
    ropacolor = aux;
}

Cubeta::Cubeta(const Cubeta& c) {
    this->ropablanca = c.ropablanca;
    this->ropacolor = c.ropacolor;
}

// Modificadoras

void Cubeta::anadir_prenda(const Prenda& p) {
    if (p.consul_color() == false) {
        ropablanca.push(p);
    }
    else {
        ropacolor.push(p);
    }
}

void Cubeta::completar_lavadora(Lavadora& lav) {
    int pesoColor = 0;
    stack<Prenda> auxColor = ropacolor;
    while (not auxColor.empty() and pesoColor <= lav.consultar_peso_maximo()) {
        Prenda p = auxColor.top();
        pesoColor += p.consul_peso();
        auxColor.pop();
    }
    int pesoBlanco = 0;
    stack<Prenda> auxBlanco = ropablanca;
    while (not auxBlanco.empty() and pesoBlanco <= lav.consultar_peso_maximo()) {
        Prenda p = auxBlanco.top();
        pesoBlanco += p.consul_peso();
        auxBlanco.pop();
    }
    if (pesoColor >= pesoBlanco and lav.consultar_color() == true) {
		while (not auxColor.empty()) {
			lav.anadir_prenda(auxColor.top());
			auxColor.pop();
		}
	}
    else if (pesoBlanco >= pesoColor and lav.consultar_color() == false){
		while (not auxBlanco.empty()) {
			lav.anadir_prenda(auxBlanco.top());
			auxBlanco.pop();
		}
	}
    
}

// Escritura

void Cubeta::escribir() const {
    cout << "Ropa de color de la cubeta: " << endl;
    stack<Prenda> aux = ropacolor;
    while (not aux.empty()) {
        Prenda p = aux.top();
        p.escribir();
        aux.pop();
    }
    cout << "Ropa blanca de la cubeta: " << endl;
    aux = ropablanca;
    while (not aux.empty()) {
        Prenda p = aux.top();
        p.escribir();
        aux.pop();
    }
}
