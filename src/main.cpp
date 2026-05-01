#include "hash_table.h"

int main() {
    size_t amount = 0;
    FILE* fp = fopen("txt/Pride_and_Prejustice.txt", "rb");
    FILE* data = fopen("csv/data.csv", "wr");
    char* buffer = read_buffer(fp, &amount);
    table_t table = {};
    table_init(&table, 2000);
    make_table(&table, buffer, amount);
    table_dump(&table, data);
    table_destroy(&table);
    free(buffer);
    return 0;
}