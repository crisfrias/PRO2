OPCIONS = -D_JUDGE_ -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11 -fno-extended-identifiers

program: program.o Ciudad.o Rio.o Barco.o Producto.o Inventario.cc
	g++ -o program *.o

program.o: program.cc
	g++ -c program.cc

Ciudad.o: Ciudad.cc Ciudad.hh
	g++ -c Ciudad.cc

Rio.o: Rio.cc Rio.hh
	g++ -c Rio.cc

Barco.o: Barco.cc Barco.hh
	g++ -c Barco.cc

Inventario.o: Inventario.cc Inventario.hh
	g++ -c Inventario.cc

Producto.o: Producto.cc Producto.hh
	g++ -c Producto.cc

clean:
	rm *.o
	rm *.tar
	rm program

tar_files:
	tar -cvf program.tar program.cc Ciudad.cc Ciudad.hh Barco.cc Barco.hh Rio.cc Rio.hh Producto.cc Producto.hh Inventario.cc Inventario.hh

tar_execute:
	tar -cvf program_exec.tar program program.o Ciudad.o Barco.o Rio.o Producto.o Inventario.o
