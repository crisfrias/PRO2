/** @file Ciudad.hh
    @brief Especificación de la clase Ciudad
*/

#ifndef _CIUDAD_HH_
#define _CIUDAD_HH_

#include "Producto.hh"
#include "Inventario.hh"

#ifndef NO_DIAGRAM
#include <string>
#include <map>

#endif

/** @class Ciudad
    @brief Representa una ciudad situada en la unión de dos afluentes del río
*/

class Ciudad 
{
private:

    string id_ciudad;
    int peso_total;
    int volumen_total;
    map<int,pair<int,int>> prods_ciudad;
    Inventario inv_ciudad();

public:
    // Constructoras

    /** @brief Creadora sin identificador
        Se ejecuta al declarar una ciudad vacía
        \pre <em>cierto</em>
        \post El resultado es una ciudad con id=NULL y con peso y volumen total = 0
    */
    Ciudad();

    /** @brief Creadora con identificador
        Se ejecuta al declarar una ciudad con identificador
        \pre id=NULL
        \post El resultado es una ciudad con identificador = id y con peso y volumen total = 0
    */
    Ciudad(string id);

    // Modificadoras
	
	/** @brief Añadir producto a la reserva
        Se añade p a la reserva de productos que tiene la ciudad
        \pre p no está vacío
        \post Se añade el identificador de p a los productos de la ciudad
    */
    void anadir_prod_reserva(const Producto& p);
	
	/** @brief Añadir producto a la lista
        Se añade p a la lista de productos que necesita comprar la ciudad
        \pre p no está vacío
        \post Se añade el identificador de p a los productos que el parámetro 
			  implícito necesita comprar
    */
    void anadir_prod_faltante(const Producto& p);

    // Consultoras

    /** @brief Consultora de identificador
        Devuelve el identificador del parámetro implícitos
        \pre <em>cierto</em>
        \post Devuelve en formato string el identificador del parámetro implícito
    */
    string consultar_id_ciudad() const;
	
	/** @brief Consultora de peso total
        Devuelve el peso total del p.i.
        \pre <em>cierto</em>
        \post Devuelve el peso total del p.i.
    */
    int consultar_peso_total() const;
    
    /** @brief Consultora del volumen total
        Devuelve el volumen total del p.i.
        \pre <em>cierto</em>
        \post Devuelve el volumen total del p.i.
    */
    int consultar_volumen_total() const;

    // Lectura y escritura
	
	/** @brief Lectura del inventario
        Entran por el canal de entrada el inventario del parámetro implícito
        \pre "cierto"
        \post Se ha actualizado el inventario de la ciudad con los identificadores
        de los productos, la cantidad que tiene y necesita, respectivamente
    */
    void leer_inventario_ciudad();
    
    /** @brief Escritura de la ciudad
        Sale por el canal de salida el inventario del parámetro implícito
        \pre "cierto"
        \post Sale por el canal de salida el inventario de la ciudad con su peso 
        y volumen total, respectivamente
    */
    void escribir() const;

};

#endif
