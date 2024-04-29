OPCIONS = -D_JUDGE_ -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11 -fno-extended-identifiers

program: Lavadora.o Cubeta.o Prenda.o program.o
	g++ -o program Lavadora.o Cubeta.o Prenda.o program.o

Lavadora.o:  Lavadora.cc Lavadora.hh
	g++ -c Lavadora.cc $(OPCIONS)

Cubeta.o:  Cubeta.cc Cubeta.hh
	g++ -c Cubeta.cc $(OPCIONS)

Prenda.o: Prenda.cc Prenda.hh
	g++ -c Prenda.cc $(OPCIONS)

program.o: program.cc readbool.hh 
	g++ -c program.cc $(OPCIONS)

clean:
	rm *.o
	rm program

tar:
	tar -cvf solucio.tar Lavadora.cc Cubeta.cc Prenda.cc program.cc Makefile
