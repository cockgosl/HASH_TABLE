#include "hash_table.h"

S_LIST* make_list(S_LIST* LIST, char* buffer) {
    assert (LIST);
    assert (buffer);
    size_t in = 0;
    while (buffer[in] != '\0') { 
        if (buffer[in] == '\n' || buffer[in] == ' ') {
            while (buffer[in] == '\n' || buffer[in] == ' ') {
                in++;
            }
            (LIST->size)++; 
            if (buffer[in] == '\0') {
                break;
            }
            buffer[in] = '\0';
        }
        in++;
    }

    list_init(LIST, LIST->size);
    char* pointer = buffer;  

    for (unsigned int counter = 0; counter < LIST->size ; counter++) {
        size_t flag = 0;
        for (size_t ind = 1; ind <= LIST->amount; ind++) {
            if (strcmp(pointer, LIST->data[ind]) == 0) {
                flag = 1;
                break;
            }
        }
        if (flag == 0) { 
            list_insert(LIST, LIST->amount, pointer);
        }
        pointer = strchr (pointer, '\0') + 1;
    }
    return LIST;
}