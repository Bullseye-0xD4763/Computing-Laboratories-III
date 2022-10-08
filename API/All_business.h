#ifndef ALLBUSINESS_H
#define ALLBUSINESS_H

#define BUFFER_SIZE 1048576 //160587 linhas

#include <glib.h>
#include "business.h"
#include "view.h"

typedef struct all_business *ALLBUS;


/*----------Operações allbus------------*/
ALLBUS init_allbus();
void insert_bus(ALLBUS ab, Business b);
void erase_allbus(ALLBUS ab);
/*--------Gets--------*/
char* get_trash(ALLBUS ab);
GHashTable* get_allbus(ALLBUS ab);
/*-----Set-----*/
void set_trash(ALLBUS ab, char* trash);

/*----Input------*/
int bus_file(const char *path, ALLBUS ab);
#endif