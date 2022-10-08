#include "../API/user.h"


struct user {
	char *user_id;
	char *name;
	char *friends;
};

/*-----------Init and Erases*/
User initUSR(){
	User u = calloc(1, sizeof *u);
	return u;
}

User eraseUSR(User u){
	if (u == NULL) return;
	free(u->user_id);
	free(u->name);
	free(u->friends);
	free(u);
}
/*------------Gets----------*/
char* get_USR_userID(User u){return strdup(u->user_id);}
char* get_USR_name(User u){return strdup(u->name);}
char* get_USR_friends(User u){return strdup(u->friends);}

/*----------Sets-------*/
void set_USR_userID(User u, const char* s){
	//free(u->user_id);//This shit stupid
	u->user_id = strdup(s);

}

void set_USR_name(User u, const char* s){
	//free(u->name);//This shit stupid
	u->name = strdup(s);
}

void set_USR_friends(User u, const char* s){
	//free(u->friends);//This shit stupid
	u->friends = strdup(s);
}

/*--------Misc-----------*/
char* outputUSR(const char *s){
	char id[64];
	snprintf(id, 64, "| %s |", s);
	return strdup(id);
}
