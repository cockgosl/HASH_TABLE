#include <stdio.h>
#include "hash_table.h"

size_t hash_table[4000];

void make_table(S_LIST* LIST) {
    size_t max = 0;
    FILE* fp = fopen("csv/data.csv", "wr");
    for (size_t ind = LIST->next[0]; ind != 0; ind = LIST->next[ind]) {
        size_t hash = hash_word(LIST->data[ind]);
        if (hash > max) {
            max = hash;
        }
        if (hash < 4000) {
            hash_table[hash] += 1;
        }
    }
    if (max > 4000) {
        max = 2000;
    }
    for (size_t ind = 0; ind < max; ind++) {
        fprintf (fp, "%ld %ld\n", ind, hash_table[ind]);
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