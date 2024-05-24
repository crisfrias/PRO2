/** @file Barco.hh
    @brief Especificación de la clase barco
*/

#ifndef _BARCO_HH_
#define _BARCO_HH_

#include "Ciudad.hh"

#ifndef NO_DIAGRAM
#include <iostream>
#include <string>
#include <list>
using namespace std;

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
    void modificar_barco(int id_compra, int unidades_compra, int id_venta, int unidades_venta);

    void comprar_prod(int unidades_compra);

    void vender_prod(int unidades_venta);
    
    /** @brief Reiniciar barco
        \pre <em>cierto</em>
        \post Se ha vaciado el historial, el resto de atributos no se han modificado
    */
    void reiniciar_barco();

    /** @brief Añadir ciudad al historial de viajes
        \pre <em>cierto</em>
        \post s se ha añadido al final del historial de viajes del barco
    */
    void anadir_ciudad_historial(const string& s);

    // Consultoras

    int consultar_id_prod_compra() const;

    int consultar_prod_compra() const;
    
    int consultar_id_prod_venta() const;

    int consultar_prod_venta() const;

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
