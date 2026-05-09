CC = g++
FLAGS_C = -g -no-pie -I include
FLAGS_G = -Tjpg

INPUT = Dump_inf/g.gv
OUTPUT = Dump_inf/g.jpg

SRC = src
BUILD = build
OBJ = build/list_func.o build/read_buffer.o build/hash.o build/main.o build/my_strcmp.o
TARGET = bin/test

Dump_inf = Dump_inf/g.gv Dump_inf/g.jpg Dump_inf/graph.png
IMAGES = images/graph.png

$(TARGET) : $(OBJ)
	mkdir -p bin/
	$(CC) $(FLAGS_C) $(OBJ) -o $(TARGET)

build/my_strcmp.o : src/my_strcmp.asm
	mkdir -p build/
	nasm -f elf64 src/my_strcmp.asm -o build/my_strcmp.o

$(BUILD)/%.o : $(SRC)/%.cpp
	mkdir -p build/
	$(CC) $(FLAGS_C) -c $< -o $@

graph_plot:
	./bin/test
	mkdir -p images
	gnuplot csv/plot.plt
benchmark:
	make -B GLAGS_C="-02 -g -Wall -Wextra -Wpedantic -Wconversion -I include"
	./bin/test
	valgrind --tool=cachegrind --cache-sim=yes --branch-sim=yes --cachegrind-out-file=cache_grind/cg_new.out ./bin/test
	cg_annotate --show-percs=yes --show=Ir,Dr,Dw --sort=Ir --threshold=0.1 cache_grind/cg_new.out > cache_grind/bench_new.txt
clean:
	rm -f $(OBJ) $(TARGET) $(Dump_inf) 