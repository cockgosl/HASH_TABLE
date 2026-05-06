#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <cstring>
#include <stdint.h>
#include <stddef.h>

typedef char* type; 
typedef size_t (*hash_ptr)(char*); 

enum error_t {
    CORRECT = 1,
    INCORRECT = 0,
};

struct node_t {
    type data;
    node_t* next;
};

struct list_t {
    node_t* head; 
    size_t amount = 0;                                          //the amount of not service data
};


struct table_t {
    list_t* table;
    size_t size = 0;
};


error_t list_init (list_t* list, type value);
error_t list_destroy (list_t* list);
error_t list_insert (list_t* list, type value);
error_t list_dump (list_t* list);

char* read_buffer(FILE* text, size_t* amount);

error_t make_table(table_t* hash_table, char* buffer, size_t number, hash_ptr hash_func);
error_t table_init(table_t* table, size_t size);
error_t table_destroy(table_t* hash_table);
error_t table_dump(table_t* hash_table, FILE* output);
int search(table_t* hash_table, char* word, hash_ptr hash_func);

size_t hash_zero(char* word);
size_t hash_first(char* word);
size_t hash_word(char* word);
size_t hash_xor(char* word);
size_t hash_xor_reversed(char* word);
size_t crc32(char* word);