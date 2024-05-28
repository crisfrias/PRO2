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
    int tamano_inv_ciudad;
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
        \post El resultado es una ciudad con identificador="id" y con peso_total=0 y volumen_total=0
    */
    Ciudad(const string& id);

    // Modificadoras
	
	/** @brief Añadir productos a la reserva
        \pre "p" existe dentro del inventario del p.i. y unidades>0
        \post Se añaden las unidades correspondientes del producto "p" al inventario de la ciudad, 
			  añadiéndoles el peso y volumen respectivos al p.i
    */
    void anadir_prod_reserva(const Producto& p, int unidades);
    
    /** @brief Quitar productos a la reserva
        \pre "p" existe dentro del inventario del p.i. y unidades>0
        \post Se borran las unidades correspondientes del producto "p" en el inventario de la ciudad,
			  quitándoles el peso y volumen respectivos al p.i
    */
    void quitar_prod_reserva(const Producto& p, int unidades);
    
    /** @brief Eliminar producto de la reserva
        \pre "p" existe en el inventario del p.i.
        \post Se ha quitado "p" del inventario de la ciudad, además del peso y volúmen que ocupaba éste 
			  en la ciudad
    */
    void eliminar_prod_reserva(const Producto& p);

    /** @brief Modificar producto de la ciudad
        El producto p es modificador de las listas de unidades que la ciudad tiene
        y también de las que la ciudad quiere
        \pre "p" no está vacío y existe en el inventario del p.i, reserva y lista son positivos
			  y al menos uno de ellos es estrictamente positivo
        \post Se han modificado los valores del inventario de la ciudad con los que tiene=reserva
			  y los que necesita=lista
    */
    void modificar_producto_reserva(const Producto& p, int reserva, int lista);
    
     /** @brief Actualizar ciudad
		Elimina todos los productos que esten en el inventario del p.i. que no tengan 
		valores válidos, como por ejemplo que la reserva y los que faltan sean 0 los dos
        \pre "cierto"
        \post Se han borrado todos los productos inexistentes o inválidos del p.i.
    */
    void actualizar_ciudad();
    
     /** @brief Comerciar
		Una ciudad le dara a la otra todos los productos que le sobren hasta alcanzar
		si es posible los que la otra necesite, y viceversa
        \pre c es una ciudad válida e inicializada, inv tiene al menos 1 elemento
        \post Se ha realizado el intercambio de productos entre el p.i. y c
    */
    void comerciar(Ciudad& c, const Inventario& inv);

    // Consultoras

    /** @brief Consultora de identificador
        Devuelve el identificador del parámetro implícitos
        \pre <em>cierto</em>
        \post Devuelve en formato string el identificador del p.i.
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
        \pre id_prod hace referencia a un producto que tiene el p.i.
        \post Devuelve true si el producto está en la ciudad, y false si no está
    */
    bool consultar_producto(int id_prod);

    /** @brief Consultora de cantidad de productos en reserva
        \pre id_prod hace referencia a un producto que tiene el p.i.
        \post Devuelve la cantidad de ese producto en reserva
    */
    int consultar_reserva(int id_prod);

    /** @brief Consultora de la cantidad de productos necesitados
        \pre "id_prod" hace referencia a un producto que tiene el p.i.
        \post Devuelve la cantidad de producto que necesita
    */
    int consultar_faltante(int id_prod);
    
    /** @brief Consultora del tamaño del inventario de la ciudad
        \pre "Cierto"
        \post Devuelve la cantidad de productos diferentes válidos que tiene el p.i. en su inventario
    */
    int consultar_tamano_inv_ciudad() const;

    // Lectura y escritura
	
	/** @brief Lectura del inventario
        Entra por el canal de entrada el inventario del parámetro implícito
        \pre Todos los productos que entrarán por el canal de entrada se encuentran en "inv"
        \post Se ha actualizado el inventario de la ciudad con los identificadores
        de los productos, la cantidad que tiene y necesita, respectivamente, además 
        de sustituir el peso y volumen totales con los de nuevos productos
    */
    void leer_inventario_ciudad(const Inventario& inv);
    
    /** @brief Escritura de la ciudad
        Sale por el canal de salida el inventario del p.i.
        \pre "cierto"
        \post Sale por el canal de salida el inventario de la ciudad con su peso 
        y volumen total, respectivamente
    */
    void escribir();

};

#endif
