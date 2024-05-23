OPCIONS = -D_JUDGE_ -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11 -fno-extended-identifiers

program.exe: program.o Ciudad.o Rio.o Barco.o Producto.o Inventario.o
	g++ -o program.exe *.o

program.o: program.cc Rio.hh Ciudad.hh Inventario.hh Producto.hh Barco.hh
	g++ -c program.cc $(OPCIONS)

Rio.o: Rio.cc Rio.hh BinTree.hh Ciudad.hh Inventario.hh
	g++ -c Rio.cc $(OPCIONS)
	
Barco.o: Barco.cc Barco.hh
	g++ -c Barco.cc $(OPCIONS)

Ciudad.o: Ciudad.cc Ciudad.hh Producto.hh Inventario.hh
	g++ -c Ciudad.cc $(OPCIONS)

Inventario.o: Inventario.cc Inventario.hh Producto.hh
	g++ -c Inventario.cc $(OPCIONS)

Producto.o: Producto.cc Producto.hh
	g++ -c Producto.cc $(OPCIONS)

clean:
	rm *.o
	rm *.exe

tar: program.cc Ciudad.cc Ciudad.hh Barco.cc Barco.hh Rio.cc Rio.hh Producto.cc Producto.hh Inventario.cc Inventario.hh Makefile
	tar -cvf practica.tar program.cc Makefile Ciudad.cc Ciudad.hh Barco.cc Barco.hh Rio.cc Rio.hh Producto.cc Producto.hh Inventario.cc Inventario.hh
