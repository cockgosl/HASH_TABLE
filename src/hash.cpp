#include <stdio.h>
#include "hash_table.h"

void make_table(table_t* hash_table, char* buffer, size_t number, hash_ptr hash_func) {

    char* pointer = buffer;  

    for (size_t counter = 0; counter < number ; counter++) {
        size_t flag = 0;
        size_t hash = hash_func(pointer);
        if (hash > hash_table->size) {
            hash = hash % hash_table->size;
        }

        for (node_t* ind = hash_table->table[hash].head; ind != NULL; ind = ind->next) {
            if (strcmp(pointer, ind->data) == 0) {
                flag = 1;
                break;
            }
        }
        if (flag == 0) { 
            list_insert(&(hash_table->table[hash]), pointer);
        }
        pointer = strchr (pointer, '\0') + 1;
    }

}

int search(table_t* hash_table, char* word) {
    return 0;
}

void table_dump(table_t* hash_table, FILE* output) {
    for (size_t ind = 0; ind < hash_table->size; ind++) {
        fprintf (output, "%ld %ld\n", ind, hash_table->table[ind].amount);
    }
}

void table_init(table_t* table, size_t size) {
    table->table = (list_t*)calloc (size, sizeof(list_t));
    table->size = size;
    char* zero = (char*)"zero";
    for (size_t ind = 0; ind < table->size; ind++) {
        list_init(&(table->table[ind]), zero );
    }
}

void table_destroy(table_t* hash_table) {
    for (size_t ind = 0; ind < hash_table->size; ind++) {
        list_destroy(&(hash_table->table[ind]));
    }
    free (hash_table->table);
}


size_t hash_zero(char* word) {
    return 0;
}

size_t hash_first(char* word) {
    return word[0];
}

size_t hash_word(char* word) {
    size_t sum = 0;
    size_t len = strlen(word);
    for (size_t ind = 0; ind < len; ind++, sum+=word[ind]);
    return sum;
}