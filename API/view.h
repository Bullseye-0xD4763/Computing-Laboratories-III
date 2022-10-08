#ifndef VIEW_H
#define VIEW_H
	
#define SEP2_4_5 "-----------------------------------------------"	
#define SEP3 "---------------------------------------------------------------------------"
#define SEP6_8 "-------------------------------------------------------------"
#define SEP7 "-----------------------"
#define SEP9 "---------------------------------------------------------------------------"

#include <glib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "table.h"



/*------Paginação-------*/
static char proxPag();
void listDivider (GPtrArray* l, guint N, char* message, char* header, int q);
/*----------Queries--------*/
void showQuery2(Table p);
void showQuery3(Table info);
void showQuery4(Table list);
void showQuery5(Table list);
void showQuery6(Table top);
void showQuery7(Table inter);
void showQuery8(Table avaliac);
void showQuery9(Table search);
/*------Menu------*/
void menu();
void acess_Menu();
void clean();
void print_Msg(char *string);
void print_Line(int i);
void prompt_Error();

#endif

