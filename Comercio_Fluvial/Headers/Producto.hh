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

	/** @brief Creadora sin identificador
        Se ejecuta al declarar un producto vacío
        \pre <em>cierto</em>
        \post El resultado es un producto con id=-1 (sin inicializar)
    */
    Producto();
    
	/** @brief Creadora con identificador
        Se ejecuta al declarar un producto con identificador
        \pre id == -1 y id_prod >= 1
        \post El resultado es una ciudad con id=id_prod
    */
    Producto(int id_prod);

    // Modificadoras

	/** @brief Modificar peso
        Cambia el peso del parámetro implícito
        \pre p > 0
        \post Se ha actualizado el peso del parámetro implícito
    */
    void cambiar_peso(int p);

	/** @brief Modificar volumen
        Cambia el volumen del parámetro implícito
        \pre p > 0
        \post Se ha actualizado el volumen del parámetro implícito
    */
    void cambiar_volumen(int v);

    // Consultoras

	/** @brief Consultar ID
        Retorna el identificador único del parámetro implícito
        \pre "cierto"
        \post id>=1
    */
    int consultar_id() const;

	/** @brief Consultar peso
        Retorna el peso del parámetro implícito
        \pre "cierto"
        \post peso>0
    */
    int consultar_peso() const;
	
	/** @brief Consultar volumen
        Retorna el volumen del parámetro implícito
        \pre "cierto"
        \post vol>0
    */
    int consultar_vol() const;

    // Lectura y escritura
    
    /** @brief Lectura del Producto
        Entran por el canal de entrada los atributos del parámetro implícito
        \pre Se prepara el canal de entrada para peso y volúmen, respectivamente
        \post Se actualizan los atributos peso y volumen del parámetro implícito
    */
    void leer();
	
	/** @brief Escritura del Producto
        Se imprime en el canal de salida los atributos del parámetro implícito
        \pre "cierto"
        \post Se imprime el identificador, el peso y el volúmen separados por un espacio, respectivamente
    */
    void escribir() const;
};

#endif
