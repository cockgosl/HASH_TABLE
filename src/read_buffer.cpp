#include "hash_table.h"

char* read_buffer(FILE* text) {
    assert (text);
    struct stat statistic = {};

    char* buffer = NULL;
    int descriptor = fileno(text); 
    fstat (descriptor, &statistic);    

    size_t size = statistic.st_size;;
    buffer = (char*) calloc(sizeof (char), size + 1);
    if (buffer) {
        buffer[size] = '\0';
        fread (buffer, sizeof(char), size, text);
    }
    else {
        printf ("memory cannot be allocated");
    }
    
    return buffer;   
}