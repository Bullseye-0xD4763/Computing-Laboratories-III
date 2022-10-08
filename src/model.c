#include "../API/model.h"


struct model{
	ALLUSR user;
	ALLBUS business;
	ALLREV review;
};

struct business_data{
	char *ID, *name;
	int n_of_revs;
	float stars;
};

/*-------Model operations-----------*/
Model init_Model(){
	Model m = malloc(sizeof *m);
	m->user = init_allusr();
	m->business = init_allbus();
	m->review = init_allrev();
	return m;
}

void erase_Model(Model m){
	if (m == NULL) return;
	erase_ALLUSR(m->user);
	erase_allbus(m->business);
	erase_allrev(m->review);	
	free(m);
}

void erase_Stars(Stars s){
	if (s == NULL) return;
	free(s->ID);
	free(s->name);
	free(s);
}
/*---------Queries------------*
/* Query 1: Dado o path para os 3 ficheiros, 
 ler o seu conteudo e carregar as estruturas de dados. 
*/
Model load_Model(char *users, char *business, char *reviews){
	Model new = init_Model(); int n;

	n = USR_file(users, new->user);
	if (n) goto fail;

	n = bus_file(business, new->business);
	if (n) goto fail;

	n = rev_file(reviews, new->review);
	if (n) goto fail;

	return new;

fail:
	erase_Model(new);
	return NULL;	 
}
/*Query 2:Determinar list a de nomes de negócios e numero de negócios 
cujo nome começa com uma determinada letra (Not case sensitive)
*/


//Aux Query 2, permite simplificar, menos trabalho
static void auxQ2(char *key, Business b, Table t){
	char letter = get_chardata(t), *aux = get_BusName(b), *str_maker;

	if (tolower(*aux) == tolower(letter)){
		str_maker = output_BusID_and_Name(b);
		add_line_Table(t, str_maker);
	}

	free(aux);
}


Table bus_started_by_letter(Model m, char letter){
	Table new = init_Table();
	set_chardata(new, letter);
	load_Head(new, 2);

	g_hash_table_foreach(get_allbus(m->business), (GHFunc)auxQ2, new);

	sort_Table(new);
	return new;
}

/*Query 3 - Dado um id de negócio, determinar a sua informação
*/
//usada em múltiplas queries
static void countStars(char *key, Review r, GHashTable *h){
	char *BusID = get_Rev_businessID(r);

	Stars aux = (Stars) g_hash_table_lookup(h, BusID);

	Stars new = malloc(sizeof *new);
	new->ID = new->name = NULL;
	new-> n_of_revs = 1;
	new->stars = get_Rev_stars(r);

	if (aux != NULL){
		new->n_of_revs += aux->n_of_revs;
		new->stars += aux->stars;
		free(aux);
	}
	g_hash_table_insert(h, BusID, new);
}

Table bus_data(Model m, char *BusinessID){
	Table new = init_Table();
	load_Head(new, 3);

    GHashTableIter iter; gpointer val;
    float stars = 0; int n_of_revs = 0;

    g_hash_table_iter_init(&iter, get_allrev(m->review));

    while(g_hash_table_iter_next(&iter, NULL, &val)){
    	char* BusID = get_Rev_businessID((Review) val);

    	if(!(strcmp(BusID, BusinessID))){
    		n_of_revs++;
    		stars += get_Rev_stars((Review) val);
    	}
    	free(BusID);
    }

    stars /= n_of_revs;
    Business b = (Business) g_hash_table_lookup(get_allbus(m->business), BusinessID);

    if (b != NULL) add_line_Table(new, output_Bus_Data(b, stars, n_of_revs));
    return new;
}
/*Query 4- Dado um id de user, determinar a lista de 
nefócios aos quais fez review (com id e nome)
*/
Table bus_reviewed(Model m, char *userID){
	Table new = init_Table();
	load_Head(new, 4);

	GHashTableIter iter; gpointer val;

	g_hash_table_iter_init(&iter, get_allrev(m->review));

	while (g_hash_table_iter_next(&iter, NULL, &val)){
		char *USR_ID = get_Rev_userID((Review) val);

		if(!(strncmp(USR_ID, userID, strlen(USR_ID)))){
			char* BusID = get_Rev_businessID((Review) val);
			Business b = (Business) g_hash_table_lookup(get_allbus(m->business), BusID);

			if(b != NULL) add_line_Table(new, output_BusID_and_Name(b));
			free(BusID);
		}
		free(USR_ID);
	} 
	sort_Table(new);
	return new;
}

/*Query 5 - Dado um numero de estrelas e uma cidade, determinar a lista 
de negocios com n ou mais estrelas na cidade (id e nome)
*/

//Aux Q5
static void auxQ5(char *key, Stars s, Table t){
	s->stars /= s->n_of_revs; float f = get_floatdata(t);

	if (s->stars >= f) add_line_Table(t, strdup(key));
}

static void countStars_Q5(char* key, Review r, GHashTable *h){
	char *BusID = get_Rev_businessID(r);
	Stars aux = (Stars) g_hash_table_lookup(h, BusID);

	Stars new = malloc(sizeof *new);
	new->ID = new->name = NULL;
	new-> n_of_revs = 1;
	new->stars = get_Rev_stars(r);

	if (aux != NULL){
		new->n_of_revs += aux->n_of_revs;
		new->stars += aux->stars;
	}

	g_hash_table_insert(h, BusID, new);
}

Table bus_with_stars_and_city(Model m, float stars, char *city){
	Table new = init_Table();
	set_floatdata(new, stars);
	load_Head(new, 5);

	GHashTable *aux = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, g_free);
	g_hash_table_foreach(get_allrev(m->review), (GHFunc)countStars_Q5, aux);
    g_hash_table_foreach(aux, (GHFunc)auxQ5, new);

    const unsigned int N = get_Size(new);
    unsigned int count = 0;
    char *BusID, *str_maker, *cidade;

    for (count = 0; count < N; count++){
    	BusID = g_ptr_array_index(get_Lines(new), 0);
    	Business auxBUS = g_hash_table_lookup(get_allbus(m->business), BusID);
    	cidade = get_BusCity(auxBUS);

    	if (!(strcmp(cidade, city))){
    		str_maker = output_BusID_and_Name(auxBUS);
    		add_line_Table(new, str_maker);
    	}
    	g_ptr_array_remove_index(get_Lines(new), 0);
    	free(cidade);
    }

    g_hash_table_destroy(aux);
    sort_Table(new);
    return new;
}
/*Query 6 - Dado um numero , determinar a lista dos top n negócios 
(tendo em conta o numero medio de estrelas), em cada cidade 
(id , nome , numero de estrelas)
*/
//Auxs

static void extraData(char *key, Stars s, GHashTable *Bus){
	s->name = get_BusName((Business) g_hash_table_lookup(Bus, key));
	s->ID = strdup(key);
	s->stars /= s->n_of_revs;
}

static void IDs_from_city(char *key, Business b, GHashTable *cities){
	char *city = get_BusName((Business) g_hash_table_lookup(b, key));
	GPtrArray *aux = g_hash_table_lookup(cities, city);

	if (aux == NULL){
		 GPtrArray *new = g_ptr_array_new_with_free_func(g_free);
		 g_ptr_array_add(new, strdup(key));
		 g_hash_table_insert(cities, city, new);
	}
	else  g_ptr_array_add(aux, strdup(key));
}

static gint sort_Q6(gconstpointer x, gconstpointer y){
	Stars sx = *(Stars *) x, sy = *(Stars *) y;

	if (sx == NULL) return -1;
	if (sy == NULL) return -1;

    if((sx->stars - sy->stars) > 0) return 1;
    if((sx->stars - sy->stars) < 0) return -1;
    return 0;
}

static void stars_by_City(char *key, GPtrArray *val, GHashTable *rating){
	const int N = val->len; Stars aux;

	 for (int i = 0; i < N; i++){
        aux = (Stars) g_hash_table_lookup(rating, g_ptr_array_index(val, 0));
        g_ptr_array_remove_index(val, 0);
        g_ptr_array_add(val, aux);
    }
    g_ptr_array_sort(val, (GCompareFunc)sort_Q6);
    g_ptr_array_set_free_func(val, (GDestroyNotify) erase_Stars);
}

static void to_Table(char *key, GPtrArray *val, Table t){
	const guint len = val->len;
    const guint top = ((guint)get_intdata(t) < len) ? (guint)get_intdata(t) : len;
    char *str_maker; gboolean b = FALSE; gboolean c = TRUE;

    for (guint i = len-1; i > (len-top-1); i--){
        Stars aux = (Stars)g_ptr_array_index(val, i);
        if(aux != NULL){
            if(c){
            	add_line_Table(t, output_Bus_City(key));
                c = !c;
            }
            str_maker = output_Bus_Data_Param(aux->ID, aux->name, aux->stars);
            add_line_Table(t, str_maker);
            b = !b;
        }
    }
    g_ptr_array_free(val, b);
}

Table top_bus_by_city(Model m, int top){
	Table new = init_Table();
	load_Head(new, 6);

	top = (top > 0) ? 0 : top;
	set_intdata(new, top);

	GHashTable *rating = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, NULL);
	GHashTable *cities = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, NULL);

	//1º Associar estrelas a cada negócio
	g_hash_table_foreach(get_allrev(m->review), (GHFunc)countStars, rating);
	//2º Associar a cada struct "Stars" o nome de negócio e fazer média
	g_hash_table_foreach(rating, (GHFunc)extraData, get_allbus(m->business));
	//3º Associar lista de IDs de business a cada cidade
	g_hash_table_foreach(get_allbus(m->business), (GHFunc)IDs_from_city, cities);
	//4º Em cada cidade, Substituir ID por informação do negócio
	g_hash_table_foreach(cities, (GHFunc)stars_by_City, rating);
	//5º Pegar nos top negócios e colocar em Table
	g_hash_table_foreach(cities, (GHFunc)to_Table, new);

	g_hash_table_destroy(rating);
    g_hash_table_destroy(cities);
    return new;
}

/*Query 7 - Determinar lista de ids de utilizadores e 
o numero total de users que vistaram mais que um estado
*/
static void auxQ7_1(char *key, Review r, GHashTable *h){
	char *USR_ID = get_Rev_userID(r), *BusID = get_Rev_businessID(r);
    GPtrArray *aux = g_hash_table_lookup(h, USR_ID);

    if (aux == NULL){
    	GPtrArray *new = g_ptr_array_new_with_free_func(g_free);
        g_ptr_array_add(new, BusID);
        g_hash_table_insert(h, USR_ID, new);
    }
    else g_ptr_array_add(aux, BusID);
}

static void auxQ7_2(char *key, GPtrArray *val, GHashTable *Bus){
	const unsigned int N = val->len; char *state;

	for (unsigned int i = 0; i < N; i++){
        state = get_BusState((Business)g_hash_table_lookup(Bus, g_ptr_array_index(val, 0)));
        g_ptr_array_remove_index(val, 0);
        g_ptr_array_add(val, state);
    }
}

static void auxQ7_3(char *key, GPtrArray *val, Table t){
    const unsigned int N = val->len; unsigned int i = 0, j;
	
	for (; i < N - 1; i++){
        for (j = i + 1; j < N; j++){
            if (strcmp(g_ptr_array_index(val, i), g_ptr_array_index(val, j))){
                add_line_Table(t, outputUSR(key));
                goto exit;
            }
        }
    }
exit:
    g_ptr_array_free(val, TRUE);
}

Table international_users(Model m){
	Table new = init_Table();
	load_Head(new, 7);

	GHashTable *users_and_business = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, NULL);

	 //1º Associar IDs de reviews aos users
	g_hash_table_foreach(get_allrev(m->review), (GHFunc)auxQ7_1, users_and_business);
	 //2º Associar uma lista de states a cada user
	g_hash_table_foreach(users_and_business, (GHFunc)auxQ7_2, get_allbus(m->business));
	//3º Adicionar os internacionais a uma table
    g_hash_table_foreach(users_and_business, (GHFunc)auxQ7_3, new);

    g_hash_table_destroy(users_and_business);
    sort_Table(new);

    return new;
}

/*Query 8 - Dado um numero n  e uma categoria, calcular os 
top n negocios (media de estrelas), de uma categoria (id, nome, n estrelas)
*/
static gboolean auxQ8(char *key, Stars val, ALLBUS ab){
	GHashTable *allbus = get_allbus(ab);
	char *begin = get_BusCategories(g_hash_table_lookup(allbus, key));

	if(begin == NULL) return 1;

	char *word = get_trash(ab), *ptr = begin;
	int i = 1; size_t N = strlen(word);

	while (i && (ptr = strcasestr(ptr, word))){
		if ((ptr == begin || !isalnum(*(ptr - 1))) && !isalnum(*(ptr + N))){
            val->stars /= val->n_of_revs;
            val->name = get_BusName(g_hash_table_lookup(allbus, key));
            val->ID = strdup(key);
            i=0;
        }
        else
            ptr += N;
	}
	free(begin);
	return i;
}

static void to_Array(char *key, Stars val, GPtrArray *arr){
    g_ptr_array_add(arr, val);	
}

static gint sort_by_stars(gconstpointer x, gconstpointer y){
    Stars sx = *(Stars *) x;
    Stars sy = *(Stars *) y;

    if((sx->stars - sy->stars) > 0) return 1;
    if((sx->stars - sy->stars) < 0) return -1;

    return 0;
}


Table top_bus_by_category(Model m, int top, char *category){
	Table new = init_Table();
	load_Head(new, 8);

	GHashTable *aux = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, NULL);

	//1º Associar estrelas a cada negócio
	g_hash_table_foreach(get_allrev(m->review), (GHFunc)countStars, aux);
	//2º Filtrar as que não pertencem à categoria
    set_trash(m->business, category);
    g_hash_table_foreach_remove(aux, (GHRFunc)auxQ8, m->business);
    //3º Converter a hashtable em array
    GPtrArray *array = g_ptr_array_new_with_free_func((GDestroyNotify)erase_Stars);
    g_hash_table_foreach(aux, (GHFunc)to_Array, array);
    //4º Destruir a hashtable
    g_hash_table_destroy(aux);
    //5º Ordernar por estrelas
    g_ptr_array_sort(array, (GCompareFunc)sort_by_stars);


    top = (top < 0) ? 0 : top;
    const int len = array->len;
    top = (len < top) ? len : top;

    for (int i = len-1; i > (len-top-1); i--){
        Stars auxS = (Stars)g_ptr_array_index(array, i);
        add_line_Table(new, output_Bus_Data_Param(auxS->ID, auxS->name, auxS->stars));
    }

    g_ptr_array_free(array, TRUE);
    return new;
}

/*Query 9 - Dada uma palavra, determinar a lista de ids 
de review que a referem no campo text
*/
static void auxQ9(char *key, Review r, Table t){
	char *begin = get_Rev_text(r), *word = get_strdata(t);
	char *ptr = begin, *str_maker;
    int i = 1;
	size_t N = strlen(word);

	 while (i && (ptr = strcasestr(ptr, word))){

        if ((ptr == begin || !isalnum(*(ptr - 1))) && !isalnum(*(ptr + N))){
            str_maker = output_Rev_ID_and_text(r, ptr);
            add_line_Table(t, str_maker);
            i = 0;
        }
        else
            ptr += N;
    }
    free(begin); 
}

Table word_in_reviews(Model m, char *word){
	Table new = init_Table();
	load_Head(new, 9);
	set_strdata(new, word);
	g_hash_table_foreach(get_allrev(m->review), (GHFunc)auxQ9, new);
	sort_Table(new);
	return new;
}