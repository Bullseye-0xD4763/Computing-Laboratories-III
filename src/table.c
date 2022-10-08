#include "../API/table.h"


struct table{
	char head[128];
	GPtrArray* lines;
	//Dados adicionais
	int intdata;
	float floatdata;
	char chardata;
	char *strdata;
};

/*------Operações table------------*/
Table init_Table(){
	Table new = malloc(sizeof *new);
	new->lines = g_ptr_array_new_with_free_func(g_free);
	return new;
}

void erase_Table(Table t){
	if (t == NULL) return;
	g_ptr_array_free(t->lines, TRUE);
	free(t);
}

void add_line_Table(Table t, char *s){
	 g_ptr_array_add(t->lines, s);
}

void sort_Table(Table t){
	 g_ptr_array_sort(t->lines, (GCompareFunc) cmp);
}
/*--------Gets------------*/
char* get_Head(Table t){return strdup(t->head);}
GPtrArray* get_Lines(Table t){return t->lines;}
guint get_Size(Table t){return t->lines->len;} //g unsigned int 
int get_intdata(Table t){return t->intdata;}
float get_floatdata(Table t){return t->floatdata;}
char get_chardata(Table t){return t->chardata;}
char* get_strdata(Table t){return t->strdata;}
/*----------Sets-----------*/
void set_intdata(Table t, int data){
	t->intdata = data;
}
void set_floatdata(Table t, float data){
	t->floatdata = data;
}
void set_chardata(Table t, char data){
	t->chardata = data;
}
void set_strdata(Table t, char *data){
	t->strdata = data;
}

/*---------Misc----------*/
static gint cmp (gconstpointer a, gconstpointer b){
    const char* arga = *((char **) a);
    const char* argb = *((char **) b);

    return strcmp(arga, argb);
}

void load_Head(Table t, int query){
	switch(query){
		case 2:
			strcpy(t->head, Q_245);
			break;
		case 3:
			strcpy(t->head, Q_3);
			break;
		case 4:
			strcpy(t->head, Q_245);
			break;
		case 5:
			strcpy(t->head, Q_245);
			break;
		case 6:
			strcpy(t->head, Q_68);
			break;
		case 7:
			strcpy(t->head, Q_7);
			break;
		case 8:
			strcpy(t->head, Q_68);
			break;
		case 9:
			strcpy(t->head, Q_245);
			break;
		default:
			printf("\nError loading head\n");
			break;
	}
}
