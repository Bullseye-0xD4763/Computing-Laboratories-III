#include "../API/All_business.h"


struct all_business {
	GHashTable* all;
	char *trash;
};


/*----------Operações allbus------------*/
ALLBUS init_allbus(){
	ALLBUS new = malloc(sizeof *new);
	new->all = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, (GDestroyNotify) eraseBus);
	new->trash = NULL;
	return new;
}


void insert_bus(ALLBUS ab, Business b){
	g_hash_table_insert(ab->all, get_BusID(b), b);
}

void erase_allbus(ALLBUS ab){
	if (ab == NULL) return;
	g_hash_table_destroy(ab->all);
	free(ab);
}
/*--------Gets--------*/
char* get_trash(ALLBUS ab){
	return ab->trash;
}
GHashTable* get_allbus(ALLBUS ab){
	return ab->all;
}
/*-----Set-----*/
void set_trash(ALLBUS ab, char* trash){
	ab->trash = trash;
}

/*----Input------*/

int bus_file(const char *path, ALLBUS ab){
	char buffer[BUFFER_SIZE];

	FILE* f = fopen(path,"r");
	if(f == NULL) return -1;

	fgets(buffer, BUFFER_SIZE, f); //Sem isto não lê a primeira linha ?

	while(fgets(buffer, BUFFER_SIZE, f)){
		Business new = initBus();
		set_BusID(new, strtok(buffer, ";")); //strtok funciona como regex
		set_BusName(new, strtok(NULL, ";")); //só se faz referencia ao buffer na primeira invocação
		set_BusCity(new, strtok(NULL, ";"));
		set_BusState(new, strtok(NULL,";"));
		set_BusCategories(new, strtok(NULL, "\0\n\r")); //byte a 0, newline, ou return 
		insert_bus(ab, new);
	}

	fclose(f);
	return 0;
}