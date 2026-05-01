#include "hash_table.h"

void list_init (list_t* list, type value) {
    if (list) {
        list->head = (node_t*)calloc (1, sizeof(node_t));
        list->head->data = value;
        list->head->next = NULL;
    }
    else {
        printf ("something is wrong with the given list");
    }
}

void list_destroy (list_t* list) {
    if (list) {
        if (list->head != NULL) {
            for (node_t* ind = list->head; ind != NULL;) {
                node_t* next = ind->next;
                free(ind);
                ind = next;
            } 
        }
        else {
            printf ("list wasn't initialized - error");
        }
    }
    else {
        printf ("Something is wrong with the given list\n");
    }
}

void list_insert (list_t* list, type value) {

    
    if (list) {
        list->amount++;
        node_t* head = list->head;
        node_t* temp = head->next;

        head->next = (node_t*)calloc (1, sizeof(node_t));
        head->next->next = temp;
        head->next->data = value;
        
    }
    else {
        fprintf (stderr, "Something is wrong with the given list\n");
    }
}

void list_dump (list_t* list) {
    size_t temp = 0;
    if (list) {
        printf ("amount = %ld\n", list->amount);

        printf ("\n");

        for (node_t* ind = list->head; ind != NULL ; ind = ind->next) {
            printf ("element[%p] : %s \n",ind, ind->data);
        }

        printf ("\n");
    }
    else {
        printf ("Something is wrong with the given list\n");
    }
}