/** @file Ciudad.hh
    @brief Especificación de la clase Ciudad
*/

#ifndef _CIUDAD_HH_
#define _CIUDAD_HH_

#ifndef NO_DIAGRAM
#include <string>
#endif

/** @class Ciudad
    @brief Representa una ciudad situada en la unión de dos afluentes del río
*/

class Ciudad 
{
private:
    string id;
    list<int> prods;

public:
    // Constructoras

    /** @brief Creadora por defecto
        Se ejecuta automáticamente al declarar una ciudad
        \pre <em>cierto</em>
        \post El resultado es una ciudad con su identificador
    */
    Ciudad(string id_ciudad);

    // Modificadoras

    // Consultoras
    string consultar_id_ciudad() const;
    void leer_inventario(string id_ciudad);

    // Lectura y escritura
    void leer();
    void escribir() const;

};

#endif
