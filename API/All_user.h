#ifndef ALLUSER_H
#define ALLUSER_H

#define BUFFER_SIZE 1048576

#include <glib.h>
#include "user.h"
#include "view.h"

typedef struct all_user *ALLUSR;

/*-------Operações Alluser-------------*/
ALLUSR init_allusr();
void insert_USR(ALLUSR au, User u);
void erase_ALLUSR(ALLUSR au);
/*-----------get------------*/
GHashTable* get_ALLUSR(ALLUSR au);
/*---------FILE-------------*/
int USR_file(const char *path, ALLUSR au);
#endif