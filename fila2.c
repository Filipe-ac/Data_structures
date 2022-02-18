#include<stdio.h>
#include<stdlib.h>
#include <time.h>

// Definir o no
typedef struct Node_st{
    int valor; //valor atribuido ao no
    struct Node_st *prox; //ponteiro com a posicao do procimo no
    struct Node_st *ante;
} no;

// Definir a fila
typedef struct fila_st //tipo particualr de no.
{   
    no * raiz;
    no * ultimo;
    int lenght; //tamanho da fila

} fila;


//metodo para iniciar uma fila
fila * inicia_fila(){//criar um pointer para a fila

    fila * lst = (fila *) malloc(sizeof(fila)); //aloca a memoria para a fila. lst e POINTER
    
    lst->ultimo = NULL;
    lst->raiz = lst->ultimo;
    lst->lenght = 0;

    return lst;
}

void insert(fila * lst,int valor){
    //criar novo no inicio da fila
    no * novo = (no *) malloc (sizeof(no));
    
    novo->valor = valor;
    //ultimo da fila aponta para o proximo
    novo->prox = lst->raiz;
    lst->raiz = novo;
    if (lst->lenght == 0){
        lst->ultimo = novo;
    } 
    else{
        novo->prox->ante = novo;
    }
    

    lst->lenght = lst->lenght + 1;

}



int remove_fla(fila * lst){

    //salvar o ultimo para retornar seu valor
    no *aux = lst->ultimo;
    if (lst->lenght == 1){//anterior e raiz
        lst->raiz = NULL;
        lst->ultimo = NULL;
    }
    else{//anterior nao e raiz
        aux->ante->prox = NULL;
        lst->ultimo = aux->ante;
    }
    

    lst->lenght = lst->lenght - 1;
    int valor = aux->valor;
    free(aux);
    return valor;
    
}



void print_fila(fila * lst){
    no * elemento = lst->raiz; 
    //printf("as %p\n",elemento->prox);
    if (lst->lenght == 0){
        return;
    }
    while(elemento->prox != NULL){
        printf("%i ",elemento->valor);
        elemento = elemento->prox;
    }
    //printar o ultimo valor
    printf("%i ",elemento->valor);
    printf("\n");
}

void deleta_fila(fila * lst){
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

int main(int argc, char **argv){

    //iniciar o seed
    int seed = time(NULL);
    srand(seed);

    
    fila *fla = inicia_fila();

    if (argv[1] != NULL){
        int N = atoi(argv[1]);
        for (int i = 0; i <= N; i ++){
            insert(fla,rand());
        }

        //testar tempo do insert
        int time1 = time(NULL);
        insert(fla,10);
        int time2 = time(NULL)-time1;
        printf("tempo insert: %i\t%i\n",N,time2);

        //testar tempo do remover
        time1 = time(NULL);
        remove_fla(fla);
        time2 = time(NULL)-time1;
        printf("tempo remove: %i\t%i\n",N,time2);

    }
    else{

        insert(fla,1);
        insert(fla,2);
        insert(fla,3);

        //esperado: 3 2 1
        print_fila(fla);//ok
    
        int i = remove_fla(fla);
        //esperado: removido = 1
        printf("removido %i\n",i);//ok

        i = remove_fla(fla);
        //esperado: removido = 2
        printf("removido %i\n",i);//ok

        //esperado 3
        print_fila(fla);//ok

        deleta_fila(fla);//ok
    }

    return 0;
}
