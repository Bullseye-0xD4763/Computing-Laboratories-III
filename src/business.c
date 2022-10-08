#include "../API/business.h"


struct business {
	char *business_id;
	char *name;
	char *city;
	char *state;
	char *categories;
};


/*--------------Inits e Erases--------------------*/
Business initBus(){ 
    Business b = calloc(1, sizeof *b); //calloc em vez de malloc, pois calloc coloca memória em 0
    return b;
}

void eraseBus(Business b){
    if (b == NULL) return;
    free(b->business_id);
    free(b->name);
    free(b->city);
    free(b->state);
    free(b->categories);
    free(b);
}

/* -----------------Gets-------------------*/
char* get_BusID(Business b){return strdup(b->business_id);}
char* get_BusName(Business b){return strdup(b->name);}
char* get_BusCity(Business b){return strdup(b->city);}
char* get_BusState(Business b){return strdup(b->state);}
char* get_BusCategories(Business b){return strdup(b->categories);}

/*--------------Sets--------------------*/
void set_BusID(Business b, const char* s){
    free(b->business_id);
    b->business_id = strdup(s);
}

void set_BusName(Business b, const char* s){
    free(b->name);
    b->name = strdup(s);
}

void set_BusCity(Business b, const char* s){
    free(b->city);
    b->city = strdup(s);
}

void set_BusState(Business b, const char* s){
    free(b->state);
    b->state = strdup(s);
}

void set_BusCategories(Business b, const char* s){
    free(b->categories);
    b->categories = strdup(s);
}


/*-----------------Output---------------------*/
char* output_BusID_and_Name(const Business b){
    char data[256];
    snprintf(data, 256, "| %s | %-32.32s |" ,b->business_id, b->name);
    return strdup(data);
}

char* output_Bus_Data(const Business b, const float stars, const float n_of_reviews){
    char data[512];
    snprintf(data, 512, "| %-32.32s | %-16.16s | %-8.8s | %.1f | %0*d " /*0xd ?*/
                        ,b->business_id ,b->name ,b->city, b->state, stars, n_of_reviews);
    return strdup(data);
}

char* output_Bus_Data_Param(const char* id, const char* name, const float stars){
    char data[512];
    snprintf(data, 512, "| %s | %-30.30s | %.1f   |", id, name, stars);
    return strdup(data);
}

char* output_Bus_City(const char* city){
    char data[256];
    snprintf(data, 256, "| \t%-64.64s |" ,city);
    return strdup(data);
}