CC = g++
FLAGS_C = -g -fsanitize=address -I include
FLAGS_G = -Tjpg

INPUT = Dump_inf/g.gv
OUTPUT = Dump_inf/g.jpg

SRC = src
BUILD = build
OBJ = build/list_func.o build/read_buffer.o build/hash.o build/main.o
TARGET = bin/test

Dump_inf = Dump_inf/g.gv Dump_inf/g.jpg Dump_inf/graph.png
IMAGES = images/graph.png

$(TARGET) : $(OBJ)
	mkdir -p bin/
	$(CC) $(FLAGS_C) $(OBJ) -o $(TARGET)

$(BUILD)/%.o : $(SRC)/%.cpp
	mkdir -p build/
	$(CC) $(FLAGS_C) -c $< -o $@

graph:
	mkdir -p Dump_inf
	dot $(FLAGS_G) $(INPUT) > $(OUTPUT)
clean:
	rm -f $(OBJ) $(TARGET) $(Dump_inf) $(IMAGES)