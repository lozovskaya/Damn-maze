CXX = g++ -Wall -Wextra -Wshadow -std=c++11 -c
LD = g++
DLLS = -lm -lpthread
BUILD_DIRECTORY=build

all: app

COMPILE= $(CXX) $< -o $@

app: $(BUILD_DIRECTORY) build/main.o build/world.o build/net.o build/field.o build/player.o build/point.o \
						build/rand.o build/line.o
	$(LD) build/* $(DLLS) -o app


build/main.o: main.cpp include/world.h
	$(COMPILE)

build/world.o: world.cpp include/world.h include/field.h include/point.h include/player.h include/rand.h
	$(COMPILE)

build/net.o: net.cpp include/net.h include/field.h include/net_includes.h include/util.h
	$(COMPILE)

build/field.o: field.cpp include/field.h include/rand.h
	$(COMPILE)

build/player.o: player.cpp include/point.h include/player.h
	$(COMPILE)

build/line.o: line.cpp include/point.h
	$(COMPILE)

build/point.o: point.cpp include/point.h
	$(COMPILE)

build/rand.o: rand.cpp include/rand.h
	$(COMPILE)

build:
	mkdir -p build
clean:
	rm -rf build/*
	rm -rf app
