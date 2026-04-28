#include <stdio.h>
#include "hash_table.h"

S_LIST hash_table[4000] = {};

void make_table(S_LIST* LIST) {
    size_t max = 0;
    char* word = NULL;
    FILE* fp = fopen("csv/data.csv", "wr");
    for (size_t ind = LIST->next[0]; ind != 0; ind = LIST->next[ind]) {
        word = LIST->data[ind];
        size_t hash = hash_word(word);
        if (hash > max) {
            max = hash;
        }
        if (hash < 4000) {
            if (hash_table[hash].size == 0) {
                list_init(&hash_table[hash], 4000);
            }
            list_insert(&hash_table[hash], 0, word);
        }
    }
    if (max > 4000) {
        max = 4000;
    }
    for (size_t ind = 0; ind < max; ind++) {
        fprintf (fp, "%ld %ld\n", ind, hash_table[ind].amount);
    }
}

void table_destroy(void) {
    for (size_t ind = 0; ind < 4000; ind++) {
        S_LIST* list = &hash_table[ind];
        if (list->size != 0) {
            list_destroy(list);
        }
    }
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