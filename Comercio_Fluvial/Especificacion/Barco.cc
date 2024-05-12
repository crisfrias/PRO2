#include "Barco.hh"

// Constructoras

Barco::Barco();

// Modificadoras

void Barco::modificar_barco(int id_compra, int peso_compra, int id_venta, int peso_venta, bool& error);

// Consultoras

// Lectura y escritura

void Barco::leer();

void Barco::escribir() const;
