#include "hash_table.h"

char* read_buffer(FILE* text, size_t* amount) {
    assert (text);
    struct stat statistic = {};

    char* buffer = NULL;
    int descriptor = fileno(text); 
    fstat (descriptor, &statistic);    

    size_t size = statistic.st_size;;

    buffer = (char*) calloc(sizeof (char), size + 1);
    assert(buffer);

    if (buffer) {
        buffer[size] = '\0';
        fread (buffer, sizeof(char), size, text);
    }
    else {
        printf ("memory cannot be allocated");
    }

    size_t number = 0;

    for (size_t in = 0; buffer[in] != '\0';) {
        if (buffer[in] == '\n' || buffer[in] == ' ' || buffer[in] == '\r') {
            while (buffer[in] == '\n' || buffer[in] == '\r' || buffer[in] == ' ') {
                in++;
            }
            if (buffer[in] == '\0') {
                break;
            }
        }
        while (buffer[in] != '\0' && buffer[in] != ' ' && buffer[in] != '\n' && buffer[in] != '\r') {
            in++;
        }

        number++;
        
        if (buffer[in] != '\0') {
            buffer[in] = '\0';
            in++;
        }
    }

    *amount = number;
    
    return buffer;   
}