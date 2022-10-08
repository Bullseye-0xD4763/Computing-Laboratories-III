#ifndef ALLREVIEW_H
#define ALLREVIEW_H

#define BUFFER_SIZE 1048576

#include <glib.h>
#include "review.h"
#include "view.h"

typedef struct all_review *ALLREV;

/*----------Operações allrev------------*/
ALLREV init_allrev();
void insert_rev(ALLREV ar, Review r);
void erase_allrev(ALLREV ar);
GHashTable* get_allrev(ALLREV ar);
/*----- Operação FILE-------*/
int rev_file(const char* path, ALLREV ar);


#endif