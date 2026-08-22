#include <stdio.h>
#include "hash_table.h"

//sdsa

error_t make_table(table_t* hash_table, char* buffer, size_t number, hash_ptr hash_func) {
    if (hash_table == NULL || buffer == NULL) {
        printf ("something is wrong with the given data\n");
        return INCORRECT;
    }
    char* pointer = buffer;  

    for (size_t counter = 0; counter < number ; counter++) {
        size_t flag = 0;
        size_t hash = hash_func(pointer);
        if (hash >= hash_table->size) {
            hash = hash % hash_table->size;
        }
        
        for (node_t* ind = hash_table->table[hash].head; ind != NULL; ind = ind->next) {
            if (ind->data && strcmp(pointer, ind->data) == 0) {
                flag = 1;
                break;
            }
        }
        if (flag == 0) { 
            list_insert(&(hash_table->table[hash]), pointer);
        }
        pointer = strchr (pointer, '\0') + 1;
    }
    return CORRECT;
}

int search(table_t* hash_table, char* word, hash_ptr hash_func) {
    if (hash_table == NULL || word == NULL) {
        printf ("something is wrong with the given data\n");
        return INCORRECT;
    }
    int flag = -1;
    size_t hash = hash_func(word);
    if (hash >= hash_table->size) {
        hash = hash % hash_table->size;
    }
    size_t in = 0;
    for (node_t* ind = hash_table->table[hash].head; ind != NULL; ind = ind->next) {
        if (in && strcmp(ind->data, word) == 0) {
            flag = (int)hash;
            break;
        }
        in++;
    }
    return flag;
}

double table_dump(table_t* hash_table, size_t amount, FILE* output) {
    if (hash_table == NULL || output == NULL) {
        printf ("something is wrong with the given data\n");
        return INCORRECT;
    }
    double measure = 0;
    size_t size = hash_table->size;
    for (size_t ind = 0; ind < size; ind++) {
        size_t amount_i = hash_table->table[ind].amount;
        if (amount_i >= 1) {
            double diff = (double)amount_i - 1;
            measure += (diff)*(diff)/double(size);
        }
        fprintf (output, "%zu %zu\n", ind, amount_i); 
    }
    return sqrt(measure); //мера отклонения от полностью равномерного распределения
}

error_t table_init(table_t* table, size_t size) {
    if (table == NULL) {
        printf ("something is wrong with the given data\n");
        return INCORRECT;
    }
    table->table = (list_t*)calloc (size, sizeof(list_t));
    table->size = size;
    for (size_t ind = 0; ind < table->size; ind++) {
        list_init(&(table->table[ind]), NULL);
    }
    return CORRECT;
}

error_t table_destroy(table_t* hash_table) {
    if (hash_table == NULL ) {
        printf ("something is wrong with the given data\n");
        return INCORRECT;
    }
    if (hash_table == 0) {
        return INCORRECT;
    }
    for (size_t ind = 0; ind < hash_table->size; ind++) {
        list_destroy(&(hash_table->table[ind]));
    }
    free (hash_table->table);
    return CORRECT;
}


size_t hash_zero(char* word) {
    if (word == NULL) {
        printf ("something is wrong with the given data\n");
        return INCORRECT;
    }
    word++;
    return 0;
}

size_t hash_first(char* word) {
    if (word == NULL) {
        printf ("something is wrong with the given data\n");
        return INCORRECT;
    }
    return word[0];
}

size_t hash_word(char* word) {
    if (word == NULL) {
        printf ("something is wrong with the given data\n");
        return INCORRECT;
    }
    size_t sum = 0;
    size_t len = strlen(word);
    for (size_t ind = 0; ind < len; sum+=word[ind], ind++);
    return sum;
}

size_t hash_xor(char* word) {
    if (word == NULL) {
        printf ("something is wrong with the given data\n");
        return INCORRECT;
    }

    char* bytes = word;
    size_t length = strlen(word);
    char hash = bytes[0];


    for (size_t ind = 1; ind < length; ind++) {
        hash ^= bytes[ind];
    }

    return (size_t)hash;
}

size_t hash_xor_reversed(char* word) {
    if (word == NULL) {
        printf ("something is wrong with the given data\n");
        return INCORRECT;
    }

    unsigned char* bytes = (unsigned char*)word;
    size_t length = strlen(word);
    unsigned char hash = (unsigned char)bytes[length - 1];


    for (int ind = length - 1; ind > 0 ;) {
        ind--;
        hash ^= bytes[ind];
    }

    return (size_t)hash;
}

size_t hash_rol(char* word) {

    if (word == NULL) {
        printf("something is wrong with the given data\n");
        return INCORRECT;
    }

    size_t length = strlen(word);

    if (length == 0) {
        return 0;
    }

    uint32_t hash = 0;

    for (size_t i = 0; i < length; ++i) {
        hash = (hash << 1) | (hash >> 31);  // ROL на 1 бит
        hash ^= (unsigned char)word[i];
    }

    return (size_t)hash;
}

size_t hash_ror(char* word) {

    if (word == NULL) {
        printf("something is wrong with the given data\n");
        return INCORRECT;
    }

    size_t length = strlen(word);

    if (length == 0) {
        return 0;
    }

    uint32_t hash = 0;

    for (size_t i = 0; i < length; ++i) {
        hash = (hash >> 1) | (hash << 31);  // ROL на 1 бит
        hash ^= (unsigned char)word[i];
    }

    return (size_t)hash;
}


size_t crc32(char* word)
{
    if (word == NULL) {
        printf ("something is wrong with the given data\n");
        return INCORRECT;
    }

    char* bytes = word;
    uint32_t crc = 0xFFFFFFFFu;

    size_t length = strlen(word);

    for (size_t i = 0; i < length; i++) {
        crc ^= bytes[i];

        for (int bit = 0; bit < 8; bit++) {
            if (crc & 1) {
                crc = (crc >> 1) ^ 0xEDB88320u;
            } 
            else {
                crc >>= 1;
            }
        }
    }
    return (size_t)(~crc);
}