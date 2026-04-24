#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <cstring>

typedef char* type;                                            //the lists are on doubles

struct S_LIST { 
    type* data;                                                 //the array with values of the list
    size_t* next;                                               //the array, that looks like: next[i] = j <-> next to the element i is element j
    size_t* prev;                                               //the array, that looks like: prev[i] = j <-> previous to the element is is element j
    size_t free = 1;                                            //the next cell, in which new data can be contained
    size_t size = 0;                                            //the real amount of elements in the arrays 
    size_t amount = 0;                                          //the amount of not service data
};

void list_init (S_LIST* LIST, size_t size);
void list_destroy (S_LIST* LIST);
void list_insert (S_LIST* LIST, size_t anchor, type value);
void list_dump (S_LIST* LIST);
void list_delete (S_LIST* LIST, size_t anchor);
void listg_dump (S_LIST* LIST);

char* read_buffer(FILE* text);
S_LIST* make_list(S_LIST* LIST, char* buffer);