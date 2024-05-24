/** @file Rio.hh
    @brief Especificación de la clase Rio
*/

#ifndef _RIO_HH_
#define _RIO_HH_

#include "Ciudad.hh"
#include "Inventario.hh"
#include "Producto.hh"
#include "Barco.hh"

#ifndef NO_DIAGRAM
#include "BinTree.hh"
#include <iostream>
#include <string>
#include <stack>
#include <map>
using namespace std;

#endif

/** @class Río
    @brief Representa una cuenca formada por un río y sus afluentes
*/

class Rio 
{
private:

    BinTree<string> cuenca;
    map<string, Ciudad> mapa_cuenca;
    stack<string> ruta;

    /** @brief Lector de ríos en formato de BinTree
        Se ejecuta cuando se lee un río de forma oculta
        \pre "t" y "m" vacíos
        \post El parámetro implícito ya no está vacío y "t" y "m" están sincronizados
    */
    static void leer_cuenca_priv(BinTree<string>& t, map<string, Ciudad>& m);
    
    /** @brief Redistribuir recursivamente
        Es la implementación recursiva de la función redistribuir
        \pre t no está vacío
        \post Se ha realizado la acción de Redistribuir
    */
    static void redistribuir_priv(BinTree<string>& t, Inventario inv, map<string, Ciudad>& m);

    /** @brief Planear ruta sobre la cuenca
        \pre t, b y r no están vacíos
        \post Se ha actualizado q con todas las ciudades que forman la mejor ruta posible
    */
    pair<int,pair<int,int>> planear_viaje(const BinTree<string>& t, const Barco& b, stack<string>& r);

    /** @brief Realización de compra-venta 
        \pre m y q no están vacíos, además los elementos de q están en m representando ciudades
        \post Se ha realizado la compra-venta entre el barco y las ciudades que forman parte de la ruta
    */
    int hacer_viaje_priv(Barco& b, stack<string>& r, Inventario inv);

public:

    // Constructora
	
	/** @brief Creadora por defecto
        \pre "cierto"
        \post Crea un río vacío
    */
    Rio();

    // Modificadoras
    
    /** @brief Actualiza el río
        \pre id_ciudad es el identificador de una ciudad en el río y c 
        no está vacía
        \post Actualiza el nodo de la ciudad con id=id_ciudad a c
    */
    void actualizar_ciudad_rio(const string& id_ciudad, const Ciudad& c);
	
	/** @brief Redistribuir
		A partir de la ciudad de la desembocadura, cada ciudad comerciará con las 
		dos ciudades inmediatamente situadas río arriba, y así hasta llegar a las ciudades
		de los nacimientos
        \pre "cierto"
        \post Se ha realizado el intercambio de productos entre las ciudades del río
    */
	void redistribuir(Inventario inv);

    /** @brief Hacer viaje
		El barco va desde la desembocadura hasta los nacimientos de los afluentes buscando rutas
		para comprar y vender. Seguirá la ruta donde pueda comprar y vender más productos
        \pre "cierto"
        \post Devuelve el número de productos que el barco ha comprado y vendido por la ruta
    */
    int hacer_viaje(Barco& b, Inventario inv);
	
    // Consultoras

    /** @brief Buscadora de ciudades
        Busca si el identificador de la ciudad representa una ciudad existente
        \pre "id_ciudad" no está vacío
        \post El resultado es un booleano que es cierto si la ciudad existe, y es falso si es lo contrario
    */
    Ciudad buscar_ciudad(const string& id_ciudad, bool& error);

    // Lectura y escritura
	
	/** @brief Lectura del río
        \pre id_ciudad es el identificador de una ciudad en el río y c 
        no está vacía
        \post Actualiza el nodo de la ciudad con id=id_ciudad a c
    */
    void leer_cuenca();
    
    /** @brief Lectura de inventarios de las ciudades del río
        \pre Está preparado el canal de entrada para los inventarios de
        las ciudades
        \post Se han añadido los inventarios a las ciudades del p.i.
    */
    void leer_inventarios(Inventario inv);
    
};

#endif
