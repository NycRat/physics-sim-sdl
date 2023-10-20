.PHONY: all release debug run clean

release:
	mkdir -p bin/release
	g++ src/main.cpp -std=c++17 -Wall -o bin/release/application -I include -L lib -l SDL2-2.0.0 -l SDL2_image-2.0.0 -l SDL2_ttf-2.0.0
      
debug:
	mkdir -p bin/debug
	g++ src/main.cpp -std=c++17 -Wall -g -o bin/debug/application -I include -L lib -l SDL2-2.0.0 -l SDL2_image-2.0.0 -l SDL2_ttf-2.0.0

run:
	./bin/release/application

clean:
	rm -r bin/*
