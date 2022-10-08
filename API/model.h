#ifndef MODEL_H
#define MODEL_H

#ifndef _GNU_SOURCE //Para lower level stuff, go-to's n shit
#define _GNU_SOURCE
#endif
/*Default paths*/
#define DEF_USER "input/users.csv"
#define DEF_BUS "input/business.csv"
#define DEF_REV "input/reviews.csv"



#include "All_business.h"
#include "All_review.h"
#include "All_user.h"
#include "table.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> //testing

typedef struct model *Model;
typedef struct business_data *Data, *Stars;


/*-----------Model operations-------------*/
Model init_Model();
void erase_Model(Model m);
void erase_Stars(Stars s);
/*--------------Queries--------------*/
//#1
Model load_Model(char *users, char *business, char *reviews);
//#2 com aux
//static void auxQ2(char *key, Business b, Table t);
Table bus_started_by_letter(Model m, char letter);
//#3 com aux
static void countStars(char *key, Review r, GHashTable *h);
Table bus_data(Model m, char *BusinessID);
//#4
Table bus_reviewed(Model m, char *userID);
//#5 com aux
//static void auxQ5(char *key, Stars s, Table t);
//static void countStars_Q5(char* key, Review r, GHashTable *h);
Table bus_with_stars_and_city(Model m, float stars, char *city);
//#6 com aux
//static void extraData(char *key, Stars s, GHashTable *Bus);
//static void IDs_from_city(char *key, Business b, GHashTable *cities);
//static gint sort_Q6(gconstpointer x, gconstpointer y);
//static void stars_by_City(char *key, GPtrArray *val, GHashTable *rating)
//static void to_Table(char *key, GPtrArray *val, Table t);
Table top_bus_by_city(Model m, int top);
//#7 com aux
//static void auxQ7_1(char *key, Review r, GHashTable *h);
//static void auxQ7_2(char *key, GPtrArray *val, GHashTable *Bus);
//static void auxQ7_3(char *key, GPtrArray *val, Table t);
Table international_users(Model m);
//#8 com aux
//static gboolean auxQ8(char *key, Stars val, ALLBUS ab);
//static void to_Array(char *key, Stars val, GPtrArray *arr);
//static gint sort_by_stars(gconstpointer x, gconstpointer y);
Table top_bus_by_category(Model m, int top, char *category);
//#9 com aux
//static void auxQ9(char *key, Review r, Table t);
Table word_in_reviews(Model m, char *word);


#endif

/*
struct business_data{
	char *ID, *name;
	int n_of_revs;
	float stars;
}

*/