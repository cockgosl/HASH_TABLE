#include "hash_table.h"

int main() {
    S_LIST* hash_table = (S_LIST*) calloc (4000, sizeof(S_LIST));
    S_LIST LIST = {};
    FILE* fp = fopen("txt/Pride_and_Prejustice.txt", "r");
    char* buffer = read_buffer(fp);
    make_list(&LIST, buffer);
    make_table(&LIST, hash_table);
    table_destroy (hash_table);
    free (hash_table);
    list_destroy(&LIST);
    free (buffer);
}
/*-------------------------------------------------------------------------------------------------*/
/*The function initializes new list with capacity = size. It allocates memory for 3 arrays: data,  */
/* next and prev. Next is built according to the rule: initially, the first free cell is [1], the  */
/* index of the next one is stored in [1], so next[1] = 2 <-> the next free is the second cell.    */
/* Also, next[i] = 0 <-> there are no more free cells                                              */
/* prev is initialized with -1, to make sure, that ties work correctly(prev[i]=-1 <-> i wasn't     */
/* initialized.                                                                                    */
/*-------------------------------------------------------------------------------------------------*/

void list_init (S_LIST* LIST, size_t size) {
    if (LIST) {
        LIST->free = 1;
        LIST->data = (type*)calloc (size + 1, sizeof (type));           /*size+1 - because the first cell in every */
        LIST->next = (size_t*)calloc (size + 1, sizeof (size_t));       /*array is a service cell                  */
        LIST->prev = (size_t*)calloc (size + 1, sizeof (size_t));

        assert(LIST->data);
        assert(LIST->next);
        assert(LIST->prev);
        
        LIST->size = size;

        for (int i = 1; i < LIST->size; i++) {  
            LIST->next[i] = i + 1;
        }
        for (int j = 1; j < LIST->size; j++) {
            LIST->prev[j] = -1;
        }

        LIST->next[LIST->size] = 0;                                     /*it's a mark, that there are no more free cells*/
    }
    else {
        printf ("something is wrong with the given list");
    }
}

/*---------------------------------------------------*/
/*The function is made to free memory from the arrays*/
/*---------------------------------------------------*/

void list_destroy (S_LIST* LIST) {
    if (LIST) {
        if (LIST->data && LIST->prev && LIST->next) {
            free (LIST->data);
            free (LIST->next);
            free (LIST->prev); 
        }
        else {
            printf ("List wasn't initialized - error");
        }
    }
    else {
        printf ("Something is wrong with the given list\n");
    }
}

/*-------------------------------------------------------------------------------------------------*/
/*This function is made to insert new elements in the array. Anchor - is the index of the element, */
/*after which user wants to insert a new one. If there is some free space - it puts the old        */
/*next[anchor] in a free cell. After these appropriate changes in next and prev are being made.    */
/*-------------------------------------------------------------------------------------------------*/



void list_insert (S_LIST* LIST, size_t anchor, type value) {

    size_t temp1 = 0;
    size_t temp2 = 0;

    if (LIST) {

        if (anchor > LIST->amount) {
            fprintf (stderr, "There is no such anchor\n");    
        }
        else if (LIST->size > LIST->amount) {
            LIST->amount++;
            temp1 = LIST->free;
            temp2 = LIST->next[anchor];
            LIST->free = LIST->next[temp1];
            LIST->data[temp1] = value;

            LIST->next[temp1] = LIST->next[anchor];
            LIST->next[anchor] = temp1;

            LIST->prev[temp1] = anchor;
            LIST->prev[temp2] = temp1;

            LIST->prev[LIST->next[0]] = 0;
            LIST->next[LIST->prev[0]] = 0;
        }
        else {
            fprintf (stderr, "the list is filled\n");
        }
    }
    else {
        fprintf (stderr, "Something is wrong with the given list\n");
    }
}

void list_delete (S_LIST* LIST, size_t anchor) {
    size_t temp = 0;
    if (LIST) {
        if (LIST->amount == 0) {
            fprintf (stderr, "There is nothing to delete\n");
        }
        else if (anchor == 0 || LIST->prev[anchor] == -1) {
            fprintf (stderr, "There is no such anchor\n");    
        }
        else {
            LIST->amount--;
            temp = LIST->free;
            LIST->free = anchor;
            LIST->data[anchor] = 0;
            LIST->next[LIST->prev[anchor]] = LIST->next[anchor];
            LIST->prev[LIST->next[anchor]] = LIST->prev[anchor];
            LIST->prev[anchor] = -1;
            LIST->next[anchor] = temp;
            
            LIST->prev[LIST->next[0]] = 0;
            LIST->next[LIST->prev[0]] = 0;
        }
    }
    else {
        printf ("something is wrong with the given list\n");
    }
}

void list_dump (S_LIST* LIST) {
    size_t temp = 0;
    if (LIST) {
        printf ("free = %ld\n", LIST->free);
        printf ("size = %ld\n", LIST->size);
        printf ("amount = %ld\n", LIST->amount);

        printf ("\n");

        for (size_t i = LIST->next[0]; i != 0 ; i = LIST->next[i]) {
            printf ("%s ", LIST->data[i]);
        }

        printf ("\n");
        printf ("from the tail\n\n");

        for (size_t i = LIST->prev[0]; i != 0; i = LIST->prev[i]) {
            printf ("element%ld: %s\n", i, LIST->data[i]);
        }
        printf ("\n");
        for (size_t i = 0; i <= LIST->size ; i++) {
            printf ("next[%ld]: %ld\n", i, LIST->next[i]);
        }
        for (size_t i = 0; i <= LIST->size ; i++) {
            printf ("prev[%ld]: %ld\n", i, LIST->prev[i]);
        }
    }
    else {
        printf ("Something is wrong with the given LIST\n");
    }
}

void listg_dump (S_LIST* LIST) {
    size_t previous = 0;
    FILE *output = fopen("Dump_inf/g.gv", "w");
    fprintf (output,"digraph G{\n   rankdir=LR;\n   edge [color = \"blue\"];\n   node [color = \"red\"];");

    for (size_t i = LIST->next[0], counter = 0; i != 0 && counter < LIST->size; i = LIST->next[i], counter++ ) {
        fprintf (output, "\n");
        if (LIST->prev[i] == previous) {
            fprintf (output, "   %ld [shape = record, color = \"black\", label=\" index = %ld \\n| value = %s \\n | {prev =%ld | next = %ld }\"];",i ,i , LIST->data[i], LIST->prev[i], LIST->next[i]);
        }
        else {
            fprintf (output, "   %ld;", i);
        }
        previous = i;
    }

    for (size_t i = LIST->free, counter = 0; i != 0 && counter < LIST->size; i = LIST->next[i] , counter++) {
        fprintf (output, "\n");
        if (LIST->data[i] == 0 && LIST->next[LIST->next[i]] != i ) {
            fprintf (output, "   \"%ldf\" [shape = record, color = \"black\", label=\" index = %ld \\n| value = %s \\n | {prev =%ld | next = %ld }\"];",i ,i , LIST->data[i], LIST->prev[i], LIST->next[i]);
        }
        else {
            if (i != 0) {
                fprintf (output, "   \"%ldf\";", i);
                fprintf (output, "   \"%ldf\";", LIST->next[i]);
            }
            break;
        }
    }

    fprintf (output, "\n");
    fprintf (output, "   ");

    for (size_t j = LIST->next[0], counter = 0; j != 0 && counter < LIST->size; j = LIST->next[j], counter++ ) {
        if (LIST->next[j] != 0) {
            fprintf (output, "%ld->", j);
        }
        else {
            fprintf (output, "%ld", j);
        }
    }

    fprintf (output, "\n");
    fprintf (output, "   ");

    for (size_t j = LIST->free, counter = 0; j != 0 && counter < LIST->size; j = LIST->next[j], counter++ ) {
        if (LIST->next[j] != 0 && counter < LIST->size && LIST->next[LIST->next[j]] != j) {
            fprintf (output, "\"%ldf\"->", j);
        }
        else {
            if (LIST->next[j] != 0) {
                fprintf (output, "\"%ldf\"->\"%ldf\"", j, LIST->next[j]);
            }
            else {
                fprintf (output, "\"%ldf\"", j);
            }
            break;
        }
    }
    fprintf (output, "\n}");
    fclose (output);
}