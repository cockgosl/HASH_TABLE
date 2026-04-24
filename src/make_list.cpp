#include "hash_table.h"

S_LIST* make_list(S_LIST* LIST, char* buffer) {
    assert (LIST);
    assert (buffer);
    size_t in = 0;
    while (buffer[in] != '\0') { 
        if (buffer[in] == '\n' || buffer[in] == ' ') {
            (LIST->size)++; 
            buffer[in] = '\0';
        }
        in++;
        if (buffer[in] == '\0') {
            (LIST->size)++;
        }
    }

    list_init(LIST, LIST->size);
    char* pointer = buffer;  

    for (unsigned int counter = 0; counter < LIST->size ; counter++) {
        list_insert(LIST, 0, pointer);
        pointer = strchr (pointer, '\0') + 1;
    }
    return LIST;
}