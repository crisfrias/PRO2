/** @file Rio.hh
    @brief Especificación de la clase Rio
*/

#ifndef _RIO_HH_
#define _RIO_HH_

#include "Ciudad.hh"
#include "Barco.hh"

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

    // Constructoras

    Rio();

    // Modificadoras

    // Consultoras

    /** @brief Buscadora de ciudades
        Busca si el identificador de la ciudad representa una ciudad existente
        \pre "id_ciudad" no está vacío
        \post El resultado es un booleano que es cierto si la ciudad existe, y es falso si es lo contrario
    */
    bool existe_ciudad(string id_ciudad) const;

    Ciudad buscar_ciudad(Ciudad c) const;

    void leer_inventario_ciudad(string id_ciudad, bool& error);

    /*
    Se leerán los inventarios de ciudades del río. No necesaria-
    mente todas las ciudades tendrán inventario
    */
    void leer_inventarios();

    // Lectura y escritura

    void leer_cuenca();
    
};
#endif
