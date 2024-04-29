/**
 * @mainpage Ejemplo de diseño modular:  Gestión de una lavadora.
 
En este ejemplo se construye un programa modular que ofrece un menú de opciones para gestionar una lavadora. Se introducen las clases <em>Lavadora</em>, <em>Cubeta</em> y <em>Prenda</em>.

Sólo se documentan elementos públicos. En una próxima sesión se verá un ejemplo
de proyecto completamente documentado, incluyendo los elementos privados.
*/

/** @file pro2_s8.cc
    @brief Programa principal para el ejercicio <em>Gestión de una lavadora</em>.
*/

// para que el diagrama modular quede bien se han escrito includes redundantes;
// en los ficheros .hh de la documentación de las clases ocurre lo mismo.
#include "Prenda.hh"
#include "Lavadora.hh"
#include "Cubeta.hh"
#ifndef NO_DIAGRAM // explicado en Prenda.hh
#include "readbool.hh"
#endif

/** @brief Programa principal para el ejercicio <em>Gestión de una lavadora</em>.
*/
int main ()
{
    Lavadora l;
    Cubeta c;
    int opcion;
    cin >> opcion;
    while (opcion != 8) {    
        if (opcion == -1) // inicializar lavadora (datos: peso máximo y color)
        {
            int pesoMax;
            string color;
            cin >> pesoMax >> color;
            if (color == "true") l.inicializar(pesoMax, true);
            else l.inicializar(pesoMax, false);
        }
        else if (opcion == -2) // añadir una prenda a la lavadora (datos: peso  y color de la prenda)
        {
            int peso;
            string color;
            cin >> peso >> color;
            Prenda p;
            if (color == "true") p.modificar(peso, true);
            else p.modificar(peso, false);
            l.anadir_prenda(p);
        }
        else if (opcion == -3) // añadir una prenda a la cubeta (datos: peso  y color de la prenda)
        {
            int peso;
            string color;
            cin >> peso >> color;
            Prenda p;
            if (color == "true") p.modificar(peso, true);
            else p.modificar(peso, false);
            c.anadir_prenda(p);
        }
        else if (opcion == -4) // completar la lavadora
        {
            c.completar_lavadora(l);
        }
        else if (opcion == -5) // realizar un lavado
        {
            l.lavado();
        }
        else if (opcion == -6) // escribir el contenido de la cubeta
        {
            cout << "   Cubeta: " << endl;
            c.escribir();
            cout << endl;
        }
        else if (opcion == -7) // escribir el contenido de la lavadora
        {
            cout << "   Lavadora: " << endl;
            l.escribir();
        }
        cin >> opcion;
  }
  return 0;
}
