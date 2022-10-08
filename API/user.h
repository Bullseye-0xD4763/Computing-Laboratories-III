#ifndef USER_H
#define USER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct user *User;

/*---------Init and Erases------*/
User initUSR();
User eraseUSR(User u);
/*------------Gets----------*/
char* get_USR_userID(User u);
char* get_USR_name(User u);
char* get_USR_friends(User u);
/*----------Sets-------*/
void set_USR_userID(User u, const char* s);
void set_USR_name(User u, const char* s);
void set_USR_friends(User u, const char* s);
/*--------Misc-----------*/
char* outputUSR(const char *s);

#endif