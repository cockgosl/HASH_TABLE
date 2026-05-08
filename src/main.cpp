#include "hash_table.h"

int main() {
    size_t amount = 0;
    FILE* fp = fopen("txt/Game_of_thrones.txt", "rb");
    FILE* data = fopen("csv/data.csv", "wr");
    assert(fp);
    assert(data);
    char* buffer = read_buffer(fp, &amount);
    table_t table = {};
    table_init(&table, 10000);
    make_table(&table, buffer, amount, hash_ror);
    table_dump(&table, data);
    for (size_t ind = 0; ind < 1000000; ind++) {
        char* word = (char*)"and";
        search(&table, word, hash_rol);
    }
    table_destroy(&table);
    free(buffer);
    return 0;
}