#include "../API/controller.h"

int controllerStart(){
	char buffer[128]; int option;
	clock_t start, end; double cpu_time;
	Model m = load_Model(DEF_USER, DEF_BUS, DEF_REV);

	if (m == NULL){
		prompt_Error(); 
		option = 1;
		goto model_fail;
	}

	do{
		clean();
		clean();
		menu();
		fgets(buffer, 128, stdin);
		option = atoi(buffer);
		model_fail:

		start = clock();

		switch(option){
			case 1:
				erase_Model(m); //Se m == NULL nada se passa
				query_1(&m);
				break;
			case 2:
				query_2(m);
				break;
			case 3:
				query_3(m);
				break;
			case 4:
				query_4(m);
				break;
			case 5:
				query_5(m);
				break;	
			case 6:
				query_6(m);
				break;	
			case 7:
				query_7(m);
				break;	
			case 8:
				query_8(m);
				break;
			case 9:
				query_9(m);
				break;	
			case 10:
				break;			
			default:
				print_Msg("Escolha novamente.");
				printf(":$ ");			
		}
		end = clock();
		cpu_time = ((double)(end-start)) / CLOCKS_PER_SEC;
		printf("Time of execution %d: %lf ", option , cpu_time);
		while (getchar() != '\n');
	}
	while (option != 10);
    
    erase_Model(m);
    print_Msg("Até à próximaaaa.");
    return 0;
}


/*-------Execução das Queries*/
/* Query 1: Dado o path para os 3 ficheiros, 
 ler o seu conteudo e carregar as estruturas de dados. 
*/
static void query_1(Model *m){
    char *user = malloc(sizeof *user * 1024);
    char *bus = malloc(sizeof *bus * 1024);
    char *rev = malloc(sizeof *rev * 1024);
    
    print_Msg("\033[2J");
    print_Msg("\033[5m" "\033[1m" "Loading.....\n" "\033[0m");
    print_Msg("\x1B[?25l");
    clean();
    
    print_Msg("Path of 'Users' file ?");
    printf(":$ ");
    fgets(user, 1024, stdin);
    strtok(user, "\n");

    print_Msg("Path of 'Business' file ?");
    printf(":$ ");
    fgets(bus, 1024, stdin);
    strtok(bus, "\n");
    
    print_Msg("Path of 'Reviews' file");
    printf(":$ ");
    fgets(rev, 1024, stdin);
    strtok(rev, "\n");

    *m = load_Model(user, bus, rev);

    free(user);
    free(bus);
    free(rev);
    print_Msg("\x1B[?25h");
    acess_Menu();
}
/*Query 2:Determinar list a de nomes de negócios e numero de negócios 
cujo nome começa com uma determinada letra (Not case sensitive)
*/
static void query_2(Model m){
    char letra;
    Table res;
    print_Msg("Insira a letra");
    printf(":$ ");
    letra = fgetc(stdin);
    res = bus_started_by_letter(m,letra);
    showQuery2(res);
    erase_Table(res);
    acess_Menu();
}
/*Query 3 - Dado um id de negócio, determinar a sua informação
*/
static void query_3(Model m){
    char buf[128];
    Table info;
    print_Msg("Insira um id");
    printf(":$ ");
    fgets(buf,128,stdin);
    strtok(buf, "\n");
    info = bus_data(m,buf);
    showQuery3(info);
    erase_Table(info);
    acess_Menu();
} 
/*Query 4- Dado um id de user, determinar a lista de 
nefócios aos quais fez review (com id e nome)
*/
static void query_4(Model m){
    char buf[128];
    Table list;
    print_Msg("Insira um id");
    printf(":$ ");
    fgets(buf,128,stdin);
    strtok(buf, "\n");
    list = bus_reviewed(m,buf);
    showQuery4(list);
    erase_Table(list);
    acess_Menu();
}
/*Query 5 - Dado um numero de estrelas e uma cidade, determinar a lista 
de negocios com n ou mais estrelas na cidade (id e nome)
*/
static void query_5(Model m){
    float stars;
    char bufS[4], buf[128];
    Table aval;
    print_Msg("Insira um número de stars");
    printf(":$ ");
    stars = atof(fgets(bufS,4,stdin));
    print_Msg("Insira a cidade");
    printf(":$ ");
    fgets(buf,128,stdin);
    strtok(buf, "\n");
    aval = bus_with_stars_and_city(m,stars,buf);
    showQuery5(aval);
    erase_Table(aval);
    acess_Menu();
}
/*Query 6 - Dado um numero , determinar a lista dos top n negócios 
(tendo em conta o numero medio de estrelas), em cada cidade 
(id , nome , numero de estrelas)
*/
static void query_6(Model m){
    int n;
    char topn[128];
    Table top;
   	print_Msg("Insire o número inteiro para determinar o top");
    printf(":$ ");
    n = atoi(fgets(topn,100,stdin));
    top = top_bus_by_city(m,n);
    showQuery6(top);
    erase_Table(top);
    acess_Menu();

}
/*Query 7 - Determinar lista de ids de utilizadores e 
o numero total de users que vistaram mais que um estado
*/
static void query_7(Model m){
    Table inter;
    inter = international_users(m);
    showQuery7(inter);
    erase_Table(inter);
    acess_Menu();
}
/*Query 8 - Dado um numero n  e uma categoria, calcular os 
top n negocios (media de estrelas), de uma categoria (id, nome, n estrelas)
*/
static void query_8(Model m){
    int num;
    char bufS[36], buf[128];
    Table evaluation;
    print_Msg("Insira um número inteiro");
    printf(":$ ");
    num = atof(fgets(bufS,36,stdin));
    print_Msg("Insira a categoria");
    printf(":$ ");
    fgets(buf,128,stdin);
    strtok(buf, "\n");
    evaluation = top_bus_by_category(m,num,buf);
    showQuery8(evaluation);
    erase_Table(evaluation);
    acess_Menu();
}
/*Query 9 - Dada uma palavra, determinar a lista de ids 
de review que a referem no campo text
*/
static void query_9(Model m){
    char buf[32];
    Table search;
    print_Msg("Insira a palavra");
    printf(":$ ");
    fgets(buf,32,stdin);
    strtok(buf, "\n");
    search = word_in_reviews(m,buf);
    showQuery9(search);
    erase_Table(search);
    acess_Menu();
}
