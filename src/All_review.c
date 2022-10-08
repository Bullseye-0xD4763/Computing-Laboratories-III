#include "../API/All_review.h"

struct all_review{
	GHashTable* all;
};

/*----------Operações allrev------------*/
ALLREV init_allrev(){
	ALLREV new = malloc(sizeof *new);
	new->all = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, (GDestroyNotify) eraseRev);
	return new;
}

void insert_rev(ALLREV ar, Review r){
	g_hash_table_insert(ar->all, get_Rev_ID(r), r);
}

void erase_allrev(ALLREV ar){
	if (ar == NULL) return;
	g_hash_table_destroy(ar->all);
	free(ar);
}

GHashTable* get_allrev(ALLREV ar){
    return ar->all;
}

/*----- Operação FILE-------*/
int rev_file(const char* path, ALLREV ar){
	char *buffer = malloc(sizeof * buffer * BUFFER_SIZE);
	char *start = buffer;

	FILE* f = fopen(path, "r");
	if (f == NULL) return -1;

	fgets(buffer, BUFFER_SIZE, f);//Again, primeira linha

	while(fgets(buffer, BUFFER_SIZE, f)){
		Review new = initRev();
		set_Rev_ID(new, strtok(buffer, ";"));
		set_Rev_userID(new, strtok(NULL, ";"));
		set_Rev_businessID(new, strtok(NULL, ";"));
		set_Rev_stars(new, atof(strtok(NULL, ";")));
		set_Rev_useful(new, atoi(strtok(NULL, ";")));
		set_Rev_funny(new, atoi(strtok(NULL, ";")));
		set_Rev_cool(new, atoi(strtok(NULL, ";")));
		set_Rev_date(new, strtok(NULL, ";"));
		set_Rev_text(new, strtok(NULL, "\0\n\r"));
		insert_rev(ar, new);
		buffer = start;
	}

	fclose(f);
	free(buffer);	
	return 0;
}