/** @file Inventario.hh
    @brief Especificación de la clase Inventario
*/

#ifndef _CIUDAD_HH_
#define _CIUDAD_HH_

#include "Producto.hh"

#ifndef NO_DIAGRAM
#include <iostream>
#include <string>
#include <vector>

#endif

/** @class Inventario
    @brief Representa un conjunto de productos
*/

class Inventario 
{
private:
    vector<Producto> catalogo;
    int ultimo_id;
    int tamano_inventario;

public:

    // Constructoras

    Inventario(int n);

    // Modificadoras

    void anadir_producto_nuevo(Producto p);

    void cambiar_producto(Producto p, int peso_nuevo, int volumen_nuevo);

    // Consultoras

    int consultar_ultimo_id();

    bool existe_producto(int id_prod) const;

    // Lectura y escritura

    void leer_inventario();

    void escribir_inventario();

}

#endif