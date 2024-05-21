/** @file Ciudad.hh
    @brief Especificación de la clase Ciudad
*/

#ifndef _CIUDAD_HH_
#define _CIUDAD_HH_

#include "Producto.hh"
#include "Inventario.hh"

#ifndef NO_DIAGRAM
#include <iostream>
#include <string>
#include <map>
using namespace std;

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
    
    /** @brief Quitar producto de la reserva
        p deja de estar en los productos de la ciudad
        \pre p no está vacío
        \post Se ha quitado p de los registros de la ciudad
    */
    void quitar_prod_reserva(const Producto& p);
	
	/** @brief Añadir producto a la lista
        Se añade p a la lista de productos que necesita comprar la ciudad
        \pre p no está vacío
        \post Se añade el identificador de p a los productos que el parámetro 
			  implícito necesita comprar
    */
    void anadir_prod_faltante(const Producto& p);

    /** @brief Modificar producto de la ciudad
        El producto p es modificador de las listas de unidades que la ciudad tiene
        y también de las que la ciudad quiere
        \pre p no está vacío y existe, reserva y lista son positivos y al menos uno de ellos es 
        estrictamente positivo
        \post Se han modificado los valores de prods_ciudad
    */
    void modificar_producto_reserva(const Producto& p, int reserva, int lista);
    
     /** @brief Actualizar ciudad
		Elimina todos los productos que esten en reserva
        \pre "cierto"
        \post Se han borrado todos los productos inexistentes de prods_ciudad
    */
    void actualizar_ciudad();
    
     /** @brief Comerciar
		Una ciudad le dara a la otra todos los productos que le sobren hasta alcanzar
		si es posible los que la otra necesite, y viceversa
        \pre s1 y s2 son ciudades inicializadas en el río
        \post Se ha realizado el intercambio de productos entre las dos ciudades
    */
    void comerciar(Ciudad& c, Inventario inv);

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
    
    /** @brief Consultora de productos
        Devuelve si el producto está en el catalogo de la ciudad
        \pre <em>cierto</em>
        \post Devuelve true si el producto está en la ciudad, y false si no está
    */
    bool consultar_producto(int id_prod);

    /** @brief Consultora de cantidad de productos en reserva
        \pre id_prod hace referencia a un producto que está en la ciudad
        \post Devuelve la cantidad de ese producto en reserva
    */
    int consultar_reserva(int id_prod);

    /** @brief Consultora de la cantidad de productos necesitados
        \pre id_prod hace referencia a un producto que está en la ciudad
        \post Devuelve la cantidad de producto que necesita
    */
    int consultar_faltante(int id_prod);

    // Lectura y escritura
	
	/** @brief Lectura del inventario
        Entran por el canal de entrada el inventario del parámetro implícito
        \pre "cierto"
        \post Se ha actualizado el inventario de la ciudad con los identificadores
        de los productos, la cantidad que tiene y necesita, respectivamente, además 
        de sustituir el peso y volumen totales con los nuevos productos
    */
    void leer_inventario_ciudad(Inventario inv);
    
    /** @brief Escritura de la ciudad
        Sale por el canal de salida el inventario del parámetro implícito
        \pre "cierto"
        \post Sale por el canal de salida el inventario de la ciudad con su peso 
        y volumen total, respectivamente
    */
    void escribir();

};

#endif
