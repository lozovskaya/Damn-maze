CXX = g++ -Wall -Wextra -Wshadow -std=c++14 -c
CXX_DEBUG = g++ -g -Wall -Wextra -Wshadow -std=c++11 -c
LD = g++
DLLS = -lm -lpthread -lws2_32
BUILD_DIRECTORY=build build/field_generators

all: app

debug: *
	g++ -std=c++11 -g *.cpp */*.cpp $(DLLS) -o app_debug
COMPILE= $(CXX) $< -o $@

app: $(BUILD_DIRECTORY) $(BUILD_DIRECTORY) build/main.o build/world.o build/net.o build/field.o build/player.o build/point.o \
						build/rand.o build/line.o build/field_generators/blank.o \
						build/field_generators/random.o build/field_generators/room-filled.o \
						build/field_generators/dfs-ed.o
	$(LD) build/*.o build/*/*.o $(DLLS) -o app
#	find build/ -type f -printf '%p ' | xargs -d \  -i $(LD) {} $(DLLS) -o app


build/main.o: main.cpp include/world.h
	$(COMPILE)

build/world.o: world.cpp include/world.h include/field.h include/point.h include/player.h include/rand.h
	$(COMPILE)

build/net.o: net.cpp include/net.h include/field.h include/net_includes.h include/util.h
	$(COMPILE)

build/field.o: field.cpp include/field.h
	$(COMPILE)

build/field_generators/%.o: field_generators/%.cpp include/field.h include/rand.h
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
build/field_generators:
	mkdir -p build/field_generators
clean:
	rm -rf build/*
	rm -rf app
