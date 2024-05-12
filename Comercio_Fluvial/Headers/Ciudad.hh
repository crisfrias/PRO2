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
    map<int, int> prods_reserva;
    map<int, int> prods_faltantes;

public:
    // Constructoras

    /** @brief Creadora sin identificador
        Se ejecuta al declarar una ciudad vacía
        \pre <em>cierto</em>
        \post El resultado es una ciudad con id=NULL
    */
    Ciudad();

    /** @brief Creadora con identificador
        Se ejecuta automáticamente al declarar una ciudad
        \pre <em>cierto</em>
        \post El resultado es una ciudad con su identificador
    */
    Ciudad(string id);

    // Modificadoras

    void anadir_prod_reserva(Producto p);

    void anadir_prod_faltante(Producto p);

    void modificar_producto_reserva(Producto p);

    // Consultoras

    /** @brief Creadora sin identificador
        Se ejecuta al declarar una ciudad vacía
        \pre <em>cierto</em>
        \post El resultado es una ciudad con id=NULL
    */
    string consultar_id_ciudad() const;

    int consultar_peso_total() const;

    void leer_inventario(string id_ciudad) const;

    // Lectura y escritura

    void leer();

    void escribir() const;

};

#endif
