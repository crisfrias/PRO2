/** @file Barco.hh
    @brief Especificación de la clase barco
*/

#ifndef _BARCO_HH_
#define _BARCO_HH_

#include "Rio.hh"

#ifndef NO_DIAGRAM

#endif

class Barco {
private:

public:

    // Constructoras

    Barco();

    // Modificadoras

    /*
    Se leerá el identificador del producto que se quiere comprar
    y la cantidad, y el identificador del producto que se quiere vender y la cantidad
    Si algún producto no existe, se escribirá un mensaje de error. Si los dos productos
    son el mismo, se escribirá un mensaje de error. Se garantiza que ambas cantidades
    serán no negativas y al menos una de ellas será estrictamente positiva.
    */
    void modificar_barco(int id_compra, int peso_compra, int id_venta, int peso_venta, bool& error) {

    }

    // Consultoras

    // Lectura y escritura

};
#endif
