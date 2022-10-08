#include "../API/review.h"

struct review {
	char *review_id;
	char *user_id;
	char *business_id;
	float stars;
	int useful;
	int funny;
	int cool;
	char *date;
	char *text;
};

/*--------------Inits e Erases--------------------*/
Review initRev(){
	Review r = calloc(1, sizeof *r);
	return r;
}

void eraseRev(Review r){
	if (r == NULL) return;
	free(r->review_id);
	free(r->user_id);
	free(r->business_id);
	free(r->date);
	free(r->text);
	free(r);
}

/* -----------------Gets-------------------*/
char* get_Rev_ID(Review r){return strdup(r->review_id);}
char* get_Rev_userID(Review r){return strdup(r->user_id);}
char* get_Rev_businessID(Review r){return strdup(r->business_id);}
float get_Rev_stars(Review r){return r->stars;}
int get_Rev_useful(Review r){return r->useful;}
int get_Rev_funny(Review r){return r->funny;}
int get_Rev_cool(Review r){return r->cool;}
char* get_Rev_date(Review r){return strdup(r->date);}
char* get_Rev_text(Review r){return strdup(r->text);}

/*--------------Sets--------------------*/
void set_Rev_ID(Review r, const char* id){
	free(r->review_id);
	r->review_id = strdup(id);
}

void set_Rev_userID(Review r, const char* id){
	free(r->user_id);
	r->user_id = strdup(id);
}
void set_Rev_businessID(Review r, const char* id){
	free(r->business_id);
	r->business_id = strdup(id);
}

void set_Rev_stars(Review r, const float f){r->stars = f;}
void set_Rev_useful(Review r, const int i){r->useful = i;}
void set_Rev_funny(Review r, const int i){r->funny = i;}
void set_Rev_cool(Review r, const int i){r->cool = i;}

void set_Rev_date(Review r, const char* date){
	free(r->date);
	r->date = strdup(date);
}

void set_Rev_text(Review r, const char* text){
	free(r->text);
	r->text = strdup(text);
}

/*----------------Output---------------*/
char* output_Rev_ID_and_text(const Review r, const char* c){
	char data[256];
	snprintf(data, 256, "| %s | %.30s ... | " ,r->review_id, c); //coloca a info no buffer data
	return strdup(data);
}
