#include "../API/view.h"



/*----------Menu da funcão de paginação*/
static char proxPag(){
    char c;
    printf("\033[1m""Next Page       (P)\n""\033[0m");
    printf("\033[1m""Anterior Page       (A)\n""\033[0m");
    printf("\033[1m""Back to MeNU        (M)\n""\033[0m");
    printf("\033[1m""Go to Page      (E)\n""\033[0m");
    printf("\033[1m"":$ ""\033[0m");
    do{c = toupper(getchar());} while((c!='P')&&(c!='A')&&(c!='M')&&(c!='E'));
    while (!getchar());
    return c;
}

/*-----------Função de paginação--------*/
void listDivider (GPtrArray* l, guint N, char* message, char* header, int q) {
    printf("\033[2J");
    
    int pages = N/10;
    if ((N%10)!=0) pages++;

    int j=1, temp1 = 0, temp2 = 0; guint k = 0, t = 0, n; char ch;
    
    while(j<=pages&&t<N){

    jump:
        temp1=t;
        printf("\033[1m""%s\n\n""\033[0m", message);
        print_Line(q);
        printf("\033[1m""\t       %s\n""\033[0m",header);
        for(n=0; n<10; n++, t++){
            if(k+n>=N) break;
            else{
                print_Line(q);
                printf("\t%0*d. %s\n",5, n+k+1, (char*) g_ptr_array_index(l, k+n));
            }
        }
        print_Line(q);
        temp2=k;
        k+=10;
        printf("\033[1m""\nPage <%d/%d> \n\n""\033[0m",j ,pages);
        j++;
        
        ch=proxPag();

        if(ch=='P'){
            if(j==pages+1){
                j=1; t=0; k=0;
                printf("You are already on the last page!\nPress C to return to the first page\n> ");
                while (getchar()!='c' && getchar()!='C');
                printf("\033[2J");
                goto jump;
            }
            else printf("\033[2J");
        }
        else if(ch=='M') break;
        else if(ch=='A'){
                if(j!=2){
                    printf ("\033[2J");
                    k = temp2-10; j = j-2; t = temp1-10;
                    goto jump;
                }
                else {
                    printf("You are already on the first page!\nPress C to continue\n> "); 
                    while (getchar()!='c' && getchar()!='C');
                    printf("\033[2J");
                }
            }
        else if(ch=='E'){
            printf("Escolha o número da pagina:\n:$ ");
            char buf[30]; int f;

            jump2:
                fgets(buf, 30, stdin);
                f = atoi(buf);

                if(f < 1 || f > pages){
                    printf("Página Inválida. Insira uma pagina entre 1 e %d.\n",pages);
                    goto jump2;
                }
                else{
                    k=(f*10)-10;
                    j = f;
                    t = f*10;
                    printf("\033[2J");
                    goto jump;
                }
            }
        }
}

void showQuery2(Table p){
    char* head = get_Head(p);
    listDivider(get_Lines(p), get_Size(p),"Bussiness started by letter", head, 2);
    free(head);
}
void showQuery3(Table info){
    char* head = get_Head(info);
    listDivider(get_Lines(info), get_Size(info), "Info about a business", head, 3);
    free(head);
}
void showQuery4(Table list){
    char* head = get_Head(list);
    listDivider(get_Lines(list), get_Size(list),"Reviews made by this user", head, 4);
    free(head);
}
void showQuery5(Table aval){
    char* head = get_Head(aval);
    listDivider(get_Lines(aval), get_Size(aval),"Best businesses in this city", head, 5);
    free(head);

}
void showQuery6(Table top){
    char* head = get_Head(top);
    listDivider(get_Lines(top), get_Size(top),"Top 'n' businesses", head, 6);
    free(head);
}
void showQuery7(Table inter){
    char* head = get_Head(inter);
    listDivider(get_Lines(inter), get_Size(inter),"List of International People", head, 7);
    free(head);
}
void showQuery8(Table avaliac){
    char* head = get_Head(avaliac);
    listDivider(get_Lines(avaliac), get_Size(avaliac),"Top businesses within this category", head, 8);
    free(head);
}
void showQuery9(Table search){
    char* head = get_Head(search);
    listDivider(get_Lines(search), get_Size(search),"Search for a word", head, 9);
    free(head);
}

/*-----------------Menu-----------------*/
void menu(){				   
        printf("\033[0;33m""\n ----------------------------------------------------------------""\033[0m");
        printf("\033[1m""\n                        Menu: Escolha uma opção                    ""\033[0m");
        printf("\033[0;33m"" \n ----------------------------------------------------------------*""\033[0m");
        printf("\n Option 1- Ler os ficheiros de input ");
        printf("\n ---------------------------------------------------------------- ");
        printf("\n Option 2- Negócios que começam com X letra");
        printf("\n ---------------------------------------------------------------- ");
        printf("\n Option 3 - Informação sobre um negócio específico");
        printf("\n ---------------------------------------------------------------- ");
        printf("\n Option 4- Negócios que um determinado utilizador fez review a");
        printf("\n ---------------------------------------------------------------- ");
        printf("\n Option 5 - Negócios na Cidade Y com N estrelas");
        printf("\n ---------------------------------------------------------------- ");
        printf("\n Option 6 - Os melhores N negócios");
        printf("\n ---------------------------------------------------------------- ");
        printf("\n Option 7 - Utilizadores que deram reviews em vários estados");
        printf("\n ---------------------------------------------------------------- ");
        printf("\n Option 8- Os melhores N negócios | Numa respetiva categoria ");
        printf("\n ---------------------------------------------------------------- ");
        printf("\n Option 9 - Palavra que ocorre numa review");
        printf("\n ---------------------------------------------------------------- ");
        printf("\n Option 10 - EXIT");
        printf("\n ---------------------------------------------------------------- ");
        printf("\n:$  ");	
}

/*O que aparece após cada query*/
void acess_Menu(){
    printf ("\033[0;33m""----------------------------------------------------------------\n""\033[0m");
    printf ("\033[1m""           	ENTER : Voltar ao Menu principal             \n""\033[0m");
    printf ("\033[0;33m""----------------------------------------------------------------\n""\033[0m");
    printf("\033[0;33m"":$ ""\033[0m");
    while(getchar()!='\n');
    clean();
}

/* Limpar o ecrã */
void clean(){
    printf("\e[2J\e[h");
}
/*Para imprimir strings*/
void print_Msg(char *string){
    printf(" %s\n", string);
}

/*Para imprimir uma linha*/
void print_Line(int i){
    switch(i){
        case 2:
            printf("\t        %s\t\n", SEP2_4_5);
            break;
        case 3:
            printf("\t        %s\t\n", SEP3);
            break;
        case 4:
            printf("\t        %s\t\n", SEP2_4_5);
            break;
        case 5:
            printf("\t        %s\t\n", SEP2_4_5);
            break;
        case 6:
            printf("\t        %s\t\n", SEP6_8);
            break;
        case 7:
            printf("\t        %s\t\n", SEP7);
            break;
        case 8:
            printf("\t        %s\t\n", SEP6_8);
            break;
        case 9:
            printf("\t        %s\t\n", SEP9);
            break; 
        default:
            break;
    }
}

void prompt_Error(){
    print_Msg("ERROR: Couldn't load model using default paths. Please specify new paths.");
    printf("ENTER to continue.\n:$ ");
    while(getchar() != '\n');
    clean();
}