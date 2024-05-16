/** @file Barco.hh
    @brief Especificación de la clase barco
*/

#ifndef _BARCO_HH_
#define _BARCO_HH_

#include "Rio.hh"
#include "Ciudad.hh"

#ifndef NO_DIAGRAM
#include <iostream>
#include <string>
#include <list>

#endif

class Barco {
private:
	
	pair<int,int> prod_compra;
	pair<int,int> prod_vender;
	list<string> historial;

public:

    // Constructoras
	
	/** @brief Creadora sin identificador
        \pre <em>cierto</em>
        \post El resultado es un barco sin inicializar
    */
    Barco();

    // Modificadoras

    /** @brief Modificar barco
        \pre id_compra y id_venta son válidos, y tanto peso_compra como peso_venta son positivos,
        siendo mínimo uno de ellos estrictamente positivo
        \post Se han actualizado los productos que el barco necesita comprar y vender
    */
    void modificar_barco(int id_compra, int peso_compra, int id_venta, int peso_venta);
    
    /** @brief Reiniciar barco
        \pre <em>cierto</em>
        \post Se ha vaciado el historial, el resto de atributos no se han modificado
    */
    void reiniciar_barco();
    
    /** @brief Hacer viaje
		El barco va desde la desembocadura hasta los nacimientos de los afluentes buscando rutas
		para comprar y vender. Seguirá la ruta donde pueda comprar y vender más productos
        \pre "cierto"
        \post Devuelve el número de productos que el barco ha comprado y vendido por la ruta
    */
    int hacer_viaje();

    // Consultoras

    // Lectura y escritura
	
	/** @brief Lectura del p.i
        \pre El p.i. no está inicializado 
        \post El p.i. está inicializado con un producto para comprar y otro para vender
    */
	void leer();
	
	/** @brief Escritura del p.i
        \pre "cert"
        \post Sale por el canal estándar de salida el id del producto que se quiere comprar, el id
        del producto que se quiere vender y el historial de viajes realizados
    */
	void escribir() const;
	
};

#endif
