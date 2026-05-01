#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <cstring>

typedef char* type; 
typedef size_t (*hash_ptr)(char*);                                         

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


void list_init (list_t* list, type value);
void list_destroy (list_t* list);
void list_insert (list_t* list, type value);
void list_dump (list_t* list);

char* read_buffer(FILE* text, size_t* amount);

void make_table(table_t* hash_table, char* buffer, size_t number, hash_ptr hash_func);
void table_init(table_t* table, size_t size);
void table_destroy(table_t* hash_table);
void table_dump(table_t* hash_table, FILE* output);

size_t hash_zero(char* word);
size_t hash_first(char* word);
size_t hash_word(char* word);