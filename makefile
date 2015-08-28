all: autoTester

autoTester: src/input.o src/practica.o
	g++ src/input.o src/practica.o /usr/local/lib/libyaml-cpp.a -o bin/autoTester -g

Input.o: src/input.cpp src/input.h
	g++ -c src/input.cpp

practica.o: src/practica.cpp src/input.h
	g++ -c src/practica.cpp
bin:
	mkdir bin

clean:
	rm -rf src/*.o bin/autoTester
run: autoTester
	./bin/autoTester examples/file.yml
