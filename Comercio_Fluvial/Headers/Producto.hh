/** @file Producto.hh
    @brief Especificación de la clase Producto
*/

#ifndef _PRODUCTO_HH_
#define _PRODUCTO_HH_

#ifndef NO_DIAGRAM
#include <iostream>
#include <string>
#endif

/** @class Producto
    @brief Representa un producto con identificador único, peso y volúmen
*/

class Producto 
{
private:
    int id;
    int peso;
    int vol;

public:

    // Constructoras

    Producto();

    Producto(int id_prod);

    // Modificadoras

    void cambiar_peso(int p);

    void cambiar_volumen(int v);

    // Consultoras

    int consultar_id() const;

    int consultar_peso() const;

    int consultar_vol() const;

    // Lectura y escritura
    
    void leer();

    void escribir() const;
};
#endif