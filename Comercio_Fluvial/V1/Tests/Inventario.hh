/** @file Inventario.hh
    @brief Especificación de la clase Inventario
*/

#ifndef _INVENTARIO_HH_
#define _INVENTARIO_HH_

#include "Producto.hh"

#ifndef NO_DIAGRAM
#include <vector>
using namespace std;

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

    /** @brief Búsqueda dicotómica en el inventario

        \pre v no está vacío y está ordenado crecientemente, esq <= 0 y dre <= tamaño de v,
        id_prod no está vacío
        \post Si id_prod está en el vector, devuelve la posición dondé está. Sino devuelve la
        que tendría que ocupar
    */
    static int busqueda_elemento(const vector<Producto>& v, int esq, int dre, int id_prod);

public:

    // Constructoras
    
    /** @brief Creadora de un inventario 
        Se ejecuta al declarar un inventario vacío
        \pre <em>cierto</em>
        \post Se crea un inventario con ultimo_id = 1 y tamaño = 0
    */
    Inventario();
	
	/** @brief Creadora de un inventario 
        Se ejecuta al declarar un inventario de n elementos
        \pre <em>cierto</em>
        \post El resultado es una inventario de tamaño = n
    */
    Inventario(int n);

    // Modificadoras

	/** @brief Añade un producto al inventario 
        \pre p no está vacío
        \post Se añade p al p.i actualizando el último id y incrementando
        en 1 el tamaño del inventario
    */
    void anadir_producto_nuevo(const Producto& p);

	/** @brief Modifica un producto del inventario
        \pre p está inicializado y existe dentro del p.i y peso_nuevo y volumen_nuevo >= 0
        \post Se actualiza el inventario con los nuevos atributos de p
    */
    void cambiar_producto(Producto p, int peso_nuevo, int volumen_nuevo);

    // Consultoras
	
	/** @brief Consultar identificador
        \pre <em>cierto</em>
        \post Devuelve el id del último producto añadido
    */
    int consultar_ultimo_id() const;
    
    /** @brief Consultar tamaño inventario
        \pre <em>cierto</em>
        \post Devuelve el tamaño del p.i
    */
    int consultar_tamano_inventario() const;
	
	/** @brief Consultar producto 
        Busca si el producto con identificador id_prod existe, y si es así lo
        devuelve, sino devuelve un producto vacío
        \pre id_prod >= 1
        \post Retorna el producto si el id_prod está en el p.i y error=false, 
        sino retorna un producto vacío y error=true 
    */
    Producto consultar_producto(int id_prod, bool& error);

    // Lectura y escritura
	
	/** @brief Leer inventario
        \pre El canal de entrada espera n productos con su peso y volúmen respectivo
        \post Se actualiza el p.i. con el peso y volúmen de n productos
    */
    void leer_inventario();
    
};

#endif
