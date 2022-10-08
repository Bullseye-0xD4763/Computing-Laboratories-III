#ifndef BUSINESS_H
#define BUSINESS_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct business *Business;


/*--------------Inits e Erases--------------------*/
Business initBus();
void eraseBus(Business b);
/* -----------------Gets-------------------*/
char* get_BusID(Business b);
char* get_BusName(Business b);
char* get_BusCity(Business b);
char* get_BusState(Business b);
char* get_BusCategories(Business b);

/*--------------Sets--------------------*/
void set_BusID(Business b, const char* s);
void set_BusName(Business b, const char* s);
void set_BusCity(Business b, const char* s);
void set_BusState(Business b, const char* s);
void set_BusCategories(Business b, const char* s);
/*-----------------Output---------------------*/
char* output_BusID_and_Name(const Business b);
char* output_Bus_Data(const Business b, const float stars, const float n_of_reviews);
char* output_Bus_Data_Param(const char* id, const char* name, const float stars);
char* output_Bus_City(const char* city);

#endif