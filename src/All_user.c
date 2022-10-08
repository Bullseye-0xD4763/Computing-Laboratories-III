#include "../API/All_user.h"

struct all_user{
	GHashTable* all;
};

/*-------Operações Alluser-------------*/

ALLUSR init_allusr(){
	ALLUSR new = malloc(sizeof *new);
	new->all = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, (GDestroyNotify) eraseUSR);
	return new;
}	

void insert_USR(ALLUSR au, User u){
	g_hash_table_insert(au->all, get_USR_userID(u), u);
}

void erase_ALLUSR(ALLUSR au){
	if (au == NULL) return;
	g_hash_table_destroy(au->all);
	free(au);
}

/*-----------get------------*/
GHashTable* get_ALLUSR(ALLUSR au){
	return au->all;
}
/*---------FILE-------------*/
int USR_file(const char *path, ALLUSR au){
	char buffer[BUFFER_SIZE];

	FILE* f = fopen(path, "r");
	if(f == NULL) return -1;

	fgets(buffer, BUFFER_SIZE, f); //Once again primeira linha

	while(fgets(buffer, BUFFER_SIZE, f)){
		User new = initUSR();
		set_USR_userID(new, strtok(buffer, ";"));
		set_USR_name(new, strtok(NULL, ";"));
		set_USR_friends(new, strtok(NULL, "\0\n\r"));
		insert_USR(au, new);
	}
	fclose(f);
	return 0;
}
