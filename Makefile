CC = gcc
FLAGS_C = -g -fsanitize=address -I include
FLAGS_G = -Tjpg

INPUT = DUMP_inf/g.gv
OUTPUT = DUMP_inf/g.jpg

SRC = src
BUILD = build
OBJ = build/hash_table.o build/read_buffer.o build/hash.o build/make_list.o
TARGET = bin/test

DUMP_INF = DUMP_inf/g.gv DUMP_inf/g.jpg

$(TARGET) : $(OBJ)
	$(CC) $(FLAGS_C) $(OBJ) -o $(TARGET)

$(BUILD)/%.o : $(SRC)/%.cpp
	$(CC) $(FLAGS_C) -c $< -o $@

graph:
	dot $(FLAGS_G) $(INPUT) > $(OUTPUT)
clean:
	rm -f $(OBJ) $(TARGET) $(DUMP_INF)