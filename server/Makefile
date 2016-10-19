CXX = g++ -Wall -Wextra -Wshadow -std=c++11 -c
LD = g++ -lm

all: app

app: build/main.o build/net.o build/field.o
	$(LD) build/main.o build/net.o build/field.o -o app

build/main.o: main.cpp build/net.o build/field.o
	$(CXX) main.cpp -o build/main.o
build/net.o: net.cpp include/net.h include/field.h include/net_includes.h
	$(CXX) net.cpp -o build/net.o
build/field.o: field.cpp include/field.h
	$(CXX) field.cpp -o build/field.o

clean:
	rm build/*
	rm app
