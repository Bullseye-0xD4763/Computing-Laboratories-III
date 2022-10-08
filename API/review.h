#ifndef REVIEW_H
#define REVIEW_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct review *Review;

//Inits e Erases
Review initRev();
void eraseRev(Review r);

//Gets
char* get_Rev_ID(Review r);
char* get_Rev_userID(Review r);
char* get_Rev_businessID(Review r);
float get_Rev_stars(Review r);
int get_Rev_useful(Review r);
int get_Rev_funny(Review r);
int get_Rev_cool(Review r);
char* get_Rev_date(Review r);
char* get_Rev_text(Review r);

//Sets
void set_Rev_ID(Review r, const char* id);
void set_Rev_userID(Review r, const char* id);
void set_Rev_businessID(Review r, const char* id);
void set_Rev_stars(Review r, const float f);
void set_Rev_useful(Review r, const int i);
void set_Rev_funny(Review r, const int i);
void set_Rev_cool(Review r, const int i);
void set_Rev_date(Review r, const char* date);
void set_Rev_text(Review r, const char* text);



//Output
char* output_Rev_ID_and_text(const Review r, const char* c);


#endif