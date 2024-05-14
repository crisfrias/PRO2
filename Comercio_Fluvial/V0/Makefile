OPCIONS = -D_JUDGE_ -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11 -fno-extended-identifiers

program.exe: program.o Ciudad.o Rio.o Barco.o Producto.o Inventario.cc
	g++ -o program.exe *.o

program.o: program.cc
	g++ -c program.cc

Rio.o: Rio.cc Rio.hh BinTree.hh
	g++ -c Rio.cc
	
Barco.o: Barco.cc Barco.hh
	g++ -c Barco.cc

Ciudad.o: Ciudad.cc Ciudad.hh
	g++ -c Ciudad.cc

Inventario.o: Inventario.cc Inventario.hh
	g++ -c Inventario.cc

Producto.o: Producto.cc Producto.hh
	g++ -c Producto.cc

clean:
	rm *.o
	rm *.tar
	rm program

tar:
	tar -cvf program.tar program.cc Ciudad.cc Ciudad.hh Barco.cc Barco.hh Rio.cc Rio.hh Producto.cc Producto.hh Inventario.cc Inventario.hh
