/** @file Rio.hh
    @brief Especificación de la clase Rio
*/

#ifndef _RIO_HH_
#define _RIO_HH_

#include "Ciudad.hh"
#include "Barco.hh"
#include "Inventario.hh"

#ifndef NO_DIAGRAM
#include "BinTree.hh"
#include <string>

#endif

/** @class Río
    @brief Representa una cuenca formada por un río y sus afluentes
*/

class Rio 
{
private:
    BinTree<string> cuenca;
    map<string, Ciudad> mapa_cuenca;

    /** @brief Lector de ríos en formato de BinTree
        Se ejecuta cuando se lee un río de forma oculta
        \pre "t" y "m" vacíos
        \post El parámetro implícito ya no está vacío y "t" y "m" están sincronizados
    */
    static void leer_cuenca_priv(BinTree<string>& t, map<string, Ciudad>& m);

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
    void actualizar_ciudad_rio(string id_ciudad, const Ciudad& c);

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
    void leer_inventarios();
    
};

#endif
