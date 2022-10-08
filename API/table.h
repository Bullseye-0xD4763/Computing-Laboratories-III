#ifndef TABLE_H
#define TABLE_H


#define Q_245 "|	Business_ID		|			Name			|"
#define Q_3 "|			Name 		|		City		| State | Stars | No_of_Reviews |"
#define Q_68 "|		Business_ID		|			Name			| Stars |"
#define Q_7 "|		User_ID			|"
#define Q_9 "|			Review_ID			| 					Text 					|"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>




typedef struct table *Table;
/*------Operações table------------*/
Table init_Table();
void erase_Table(Table t);
void add_line_Table(Table t, char *s);
void sort_Table(Table t);
/*--------Gets------------*/
char* get_Head(Table t);
GPtrArray* get_Lines(Table t);
guint get_Size(Table t);
int get_intdata(Table t);
float get_floatdata(Table t);
char get_chardata(Table t);
char* get_strdata(Table t);
/*-------Sets---------*/
void set_intdata(Table t, int data);
void set_floatdata(Table t, float data);
void set_chardata(Table t, char data);
void set_strdata(Table t, char *data);
/*--------Misc--------------*/
static gint cmp(gconstpointer a, gconstpointer b);
void load_Head(Table t, int query);

#endif 
