#include<stdio.h>
#include<stdlib.h>
#include <time.h>

// Definir o no
typedef struct Node_st{
    int valor; //valor atribuido ao no
    struct Node_st *prox; //ponteiro com a posicao do procimo no
} no;

// Definir a lista
typedef struct lista_st //tipo particualr de no.
{   
    no * raiz;
    int lenght; //tamanho da lista

} lista;

//(lista *) = cast

//metodo para iniciar uma lista
lista * inicia_lista(){//criar um pointer para a lista

    lista * lst =  (lista *)malloc(sizeof(lista)); //aloca a memoria para a lista. lst e POINTER
    lst->raiz = NULL; //agora o pointer raiz da lista aponta para NULL
    lst->lenght = 0; //tamanho e 0. Nenhum no associado
    return lst;
}

//funcao auxiliar para tratar o caso de inserir o primeiro elemento da lista
void insert0(lista * lst,int valor){
    //criar novo no
    no * novo = (no *) malloc (sizeof(no));
    //assinalar o valor do no
    novo->valor = valor;
    //apontar o prox do novo como o proximo da raiz
    novo->prox = lst->raiz;
    //apontar a raiz para o novo
    lst->raiz = novo;
    //aumntar o valor do tamanho da lista
    lst->lenght = lst->lenght + 1;
}

void print_lista(lista * lst){
    no * elemento = lst->raiz; 
    //printf("as %p\n",elemento->prox);
    while(elemento->prox != NULL){
        printf("%i ",elemento->valor);
        elemento = elemento->prox;
    }
    //printar o ultimo valor
    printf("%i ",elemento->valor);
    printf("\n");
}

//funcao para retornar um no em dada posicao
no * get_no(lista * lst, int pos){
    if (pos >= lst->lenght){
        printf("elemento maior que tamanho da lista\n"); //colocar erro??
    }
    no * elemento = lst->raiz;
    for (int i = 0; i < pos; i ++){
        elemento = elemento->prox; //vai indo para o novo elemento
        //printf("a %i\n",elemento.valor);

    }
    return elemento;
}

//retorna o valor de uma posicao
int get_valor(lista * lst,int pos){
    return get_no(lst,pos)->valor;
}

//insere elemento em dada posiscao
void insert(lista * lst,int pos,int valor){
    if (pos == 0){
        insert0(lst,valor);
    }
    else{
        no * anterior = get_no(lst,pos-1);
        no * novo = (no *) malloc (sizeof(no));
        novo->prox = anterior->prox;
        anterior->prox = novo; 
        novo->valor = valor;
        lst->lenght = lst->lenght + 1;
    }
}

//remove elemento da lista
void remove_lst(lista * lst, int pos){
    no * no_anterior;
    if (pos == 0){
        no_anterior = lst->raiz;
    }
    else{
        no_anterior = get_no(lst,pos-1);
    }
    no * aux = no_anterior->prox;
    no_anterior->prox = aux->prox;
    free(aux);
    
}

void deleta_lista(lista * lst){
    no * elemento = lst->raiz; 
    no * aux = elemento;

    while(elemento->prox != NULL){
        aux = elemento->prox;
        free(elemento);
        elemento = aux;
    }
    free(elemento);
    free(lst);
}

/*
double rm = RAND_MAX;

int rand01 fill_random(int list[],int n){
    for (int i = 0; i < n; i++){
        list[i] = rand()/rm * n * 2;
        }
    }
*/

int main(int argc, char **argv){

    //iniciar o seed
    int seed = time(NULL);
    srand(seed);


    lista *lst = inicia_lista();

    //se der um valor pela linha de comando
    //criar lista com dimensao N preenchida com numeros aleatorios

    if (argv[1] != NULL){
        int N = atoi(argv[1]);
        for (int i = 0; i <= N; i ++){
            insert(lst,0,rand());
        }
    //testar tempo do insert no fim
    int time1 = time(NULL);
    insert(lst,N-1,10);
    int time2 = time(NULL)-time1;
    printf("tempo insert: %i\t%i\n",N,time2);

    //testar tempo de buscar no fim
    time1 = time(NULL);
    int a = get_valor(lst,N);
    time2 = time(NULL)-time1;
    printf("tempo get_valor: %i\t%i\n",N,time2);


    deleta_lista(lst);

    }
    //senao, testar alguns casos
    else{
        
        insert(lst,0,23);
        insert(lst,0,12);
        insert(lst,0,34);

        
        //espeardo 34 12 23
        print_lista(lst);//ok
        
        //espeardo 34 12 23
        printf("%i %i %i\n",get_valor(lst,0),get_valor(lst,1),get_valor(lst,2));//ok


        insert(lst,2,45);
        //esperado 34 12 45 23
        print_lista(lst);//ok


        remove_lst(lst,2);
        //esperado 34 12 34
        print_lista(lst);//ok

        deleta_lista(lst);//ok

    }

    return 0;
}
