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
        \post El p.i. ya no está vacío y "t" y "m" están sincronizados
    */
    static void leer_cuenca_priv(BinTree<string>& t, map<string, Ciudad>& m);
    
    /** @brief Redistribuir recursivamente
        Es la implementación recursiva de la función redistribuir
        \pre "t" y "m" no están vacíos
        \post Se ha comerciado recursivamente entre todas las ciudades del árbol "t"
    */
    static void redistribuir_priv(BinTree<string>& t, const Inventario& inv, map<string, Ciudad>& m);

    /** @brief Planear ruta sobre la cuenca
        \pre "t" y "b" no están vacíos, "r" está vacío, compra_barco >= 0, venta_barco >= 0
        \post Se han añadido a "r" el nombre de las ciudades con las que el barco ha de comprar y vender productos,
			  además de devolver el número de nodos que ha de visitar la ruta
    */
    int planear_viaje(const BinTree<string>& t, const Barco& b, stack<string>& r, int& compra_barco, int& venta_barco);
    
    /** @brief Realización de compraventa 
        \pre "b" está inicializado y "r" contiene la ruta por la que ha de comprar y vender con el barco
        \post Se han añadido o eliminado unidades de los productos que compra o vende el barco si ha sido posible,
			  "r" se ha quedado vacío
    */
    int hacer_viaje_priv(Barco& b, stack<string>& r, const Inventario& inv);

public:

    // Constructora
	
	/** @brief Creadora por defecto
        \pre "cierto"
        \post Crea un río vacío
    */
    Rio();

    // Modificadoras
    
    /** @brief Actualiza el río
        \pre "id_ciudad" es el identificador único de "c"
        \post Borra del inventario de c todos los productos que no se necesiten ni estén en reserva
    */
    void actualizar_ciudad_rio(const string& id_ciudad, const Ciudad& c);
	
	/** @brief Redistribuir
		A partir de la ciudad de la desembocadura, cada ciudad comerciará con las 
		dos ciudades inmediatamente situadas río arriba, y así hasta llegar a las ciudades
		de los nacimientos
        \pre "cierto"
        \post Se ha realizado el intercambio de productos entre las ciudades del río
    */
	void redistribuir(const Inventario& inv);

    /** @brief Hacer viaje
		El barco va desde la desembocadura hasta los nacimientos de los afluentes buscando rutas
		para comprar y vender. Seguirá la ruta donde pueda comprar y vender más productos
        \pre "cierto"
        \post Devuelve el número de productos que el barco ha comprado y vendido por la ruta
    */
    int hacer_viaje(Barco& b, const Inventario& inv);
	
    // Consultoras

    /** @brief Buscadora de ciudades
        Busca si el identificador de la ciudad representa una ciudad existente
        \pre "id_ciudad" no está vacío
        \post El resultado es un booleano que es cierto si la ciudad existe, y es falso si es lo contrario.
        Si error=false devuelve una ciudad vacía, sino devuelve la ciudad con identificador=id_ciudad
    */
    Ciudad buscar_ciudad(const string& id_ciudad, bool& error);

    // Lectura y escritura
	
	/** @brief Lectura del río
        \pre Entran por el canal de entrada strings con el nombre de las ciudades, siendo '#' el carácter
			 utilizado para indicar que no tiene más ciudades río arriba
        \post Se han añadido correctamente las ciudades introducidas en el río
    */
    void leer_cuenca();
    
    /** @brief Lectura de inventarios de las ciudades del río
        \pre Está preparado el canal de entrada para los inventarios de
			 las ciudades
        \post Se han añadido los inventarios a las ciudades del p.i.
    */
    void leer_inventarios(const Inventario& inv);
    
};

#endif
