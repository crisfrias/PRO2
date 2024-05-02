/**
* @mainpage Comercio fluvial
*
*/

#ifndef NO_DIAGRAM
#include <iostream>
#include <struct>
using namespace std;
#endif

/** @brief Programa Principal
*/

struct Producto {
	int id;
	int peso;
	int vol;
};

int main() {
    // Inicializar las estructuras

    // Siguientes opciones
    string instr;
    cin >> instr;
    while (instr != "fin") {
        if (instr == "leer_rio" or instr == "lr" ) {
            // Se leerán los identificadores de las ciudades indicando la estructura
            // de la cuenca. No se escribe nada
        }
        else if (instr == "leer_inventario" or instr == "li") {
            /*
            Se leerá el identificador de una ciudad. Si la ciudad no existe
            se escribirá un mensaje de error. Si la ciudad existe, se leerá un número que in-
            dica la cantidad de elementos del inventario y para cada uno de ellos se leerá el
            identificador del producto, cuantas unidades tiene la ciudad y cuantas necesita
            */
        }
        else if (instr == "leer_inventarios" or instr == "ls") {
            /*
            Se leerán los inventarios de ciudades del río. No necesaria-
            mente todas las ciudades tendrán inventario
            */
        }
        else if (instr == "modificar_barco" or instr == "mb") {
            /*
            Se leerá el identificador del producto que se quiere comprar
            y la cantidad, y el identificador del producto que se quiere vender y la cantidad
            Si algún producto no existe, se escribirá un mensaje de error. Si los dos productos
            son el mismo, se escribirá un mensaje de error. Se garantiza que ambas cantidades
            serán no negativas y al menos una de ellas será estrictamente positiva.
            */
        }
        else if (instr == "escribir_barco" or instr == "eb") {
            /*
            Se escriben los cuatro valores mencionados en la anterior ope-
            ración y los viajes realizados, en orden cronológico. Para cada viaje solo se ha de
            escribir la última ciudad visitada de la ruta escogida.
            */
        }
        else if (instr == "consultar_num" or instr == "cn") {
            /*
            Escribe cuantos productos diferentes hay
            */
        }
        else if (instr == "agregar_productos" or instr == "ap") {
            /*
            Se lee el número de productos nuevos, mayor que 0. Sus
            identificadores serán correlativos a partir del último producto existente. Se leerán
            sus pesos y volúmenes respectivos
            */
        }
        else if (instr == "escribir_producto" or instr == "ep") {
            /*
            Se lee el identificador de un producto. Si no existe el pro-
            ducto se escribe un mensaje de error. En caso contrario se escribe el peso y volumen
            del producto
            */
        }
        else if (instr == "escribir_ciudad" or instr == "ec") {
            /*
            Se leerá el identificador de una ciudad. Si la ciudad no existe
            se escribirá un mensaje de error. Si la ciudad existe, se escribirá su inventario, y el
            peso y el volumen total de los productos almacenados
            */
        }
        else if (instr == "poner_prod" or instr == "pp") {
            /*
            Se leerá el identificador de una ciudad, de un producto y las
            unidades que tiene y que quiere.
            Si el producto no existe escribe un mensaje de error
            Si la ciudad no existe, escribe un mensaje de error
            Si el producto ya está en el inventario de la ciudad, escribe un mensaje de error
            Si no hay errores, los datos de ese producto se añaden a la ciudad, modificándose el peso y el volumen total 
            si hace falta. Se escribe el peso y el volumen total
            */
        }
        else if (instr == "modificar_prod" or instr == "mp") {
            /*
            Se leerá el identificador de una ciudad, de un producto y las
            unidades que tienen y que quiere. Si el producto no existe escribe un mensaje de
            error. Si la ciudad no existe, escribe un mensaje de error. Si el producto no está en
            el inventario de la ciudad, escribe un mensaje de error. Si no hay errores, los datos
            de ese producto sustituyen a los que había en la ciudad, modificándose el peso y
            el volumen total si hace falta. Se escribe el peso y el volumen total. El número de
            unidades necesitadas se puede modificar, pero siempre ha de ser mayor que 0.
            */
        }
        else if (instr == "quitar_prod" or instr == "qp") {
            /*
            Se leerá el identificador de una ciudad y de un producto. Si
            el producto no existe escribe un mensaje de error. Si la ciudad no existe, escribe
            un mensaje de error. Si el producto no está en el inventario de la ciudad, escribe
            un mensaje de error. Si no hay errores, se quitan los datos de este producto en la
            ciudad, modificándose el peso y el volumen total si hace falta. Se escribe el peso y
            el volumen total
            */
        }
        else if (instr == "consultar_prod" or instr == "cp") {
            /*
            Se leerá el identificador de una ciudad y de un producto. Si
            el producto no existe escribe un mensaje de error. Si la ciudad no existe, escribe un
            mensaje de error. Si el producto no está en el inventario de la ciudad, escribe un
            mensaje de error. Si no hay errores, se escribe cuantas unidades de ese producto
            tiene y quiere la ciudad.
            */
        }
        else if (instr == "comerciar" or instr == "co") {
            /*
            Se leerán los identificadores de dos ciudades. Si no existen alguna
            de las dos (o las dos), se escribe un mensaje de error. Si las dos ciudades existen se
            intercambian los productos que le sobren a una y necesite la otra
            */
        }
        else if (instr == "redistribuir" or instr == "re") {
            /*
            No se leen datos. La ciudad de la desembocadura comercia con su
            ciudad río arriba a mano derecha y luego con la ciudad río arriba a mano izquierda,
            y así sucesivamente.
            */
        }
        else if (instr == "hacer_viaje" or instr == "hv") {
            /*
            El barco busca la ruta a partir de la desembocadura que le per-
            mita comprar y vender el mayor número posible de productos. En caso que haya
            más de una ruta que lo cumpla, se queda con la más corta, y en caso de que ten-
            gan la misma longitud, se queda con la que viene río arriba a mano derecha. Una
            vez encontrada la ruta, se hace el viaje y se compran y venden los productos a lo
            largo de la ruta, modificándose los inventarios de las ciudades. Se escribe el total
            de unidades de productos compradas y vendidas por el barco.
            */
        }

        cin >> instr;
    }
}
