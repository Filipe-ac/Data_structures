#include<stdio.h>
#include<stdlib.h>
#include <time.h>

// Definir o no
typedef struct Node_st{
    int valor; //valor atribuido ao no
    struct Node_st *ante;
} no;

// Definir a pilha
typedef struct pilha_st //tipo particualr de no.
{   
    no * raiz;
    int lenght; //tamanho da pilha

} pilha;



//metodo para iniciar uma pilha
pilha * inicia_pilha(){//criar um pointer para a pilha

    pilha * lst = (pilha *) malloc(sizeof(pilha)); //aloca a memoria para a pilha. lst e POINTER
    lst->raiz = NULL;

    lst->lenght = 0;

    return lst;
}

void insert(pilha * lst,int valor){
    //criar novo no inicio da pilha
    no * novo = (no *) malloc (sizeof(no));
    
    //assinalar o valor do no
    novo->valor = valor;
    
    novo->ante = lst->raiz;
    lst->raiz = novo;

    lst->lenght = lst->lenght + 1;
}



int remove_pla(pilha * lst){

    //salvar o ultimo para retornar seu valor
    no *aux = lst->raiz;

    lst->raiz = aux->ante;

    lst->lenght = lst->lenght - 1;
    int valor = aux->valor;
    free(aux);
    return valor;
    
}



void print_pilha(pilha * lst){
    no * elemento = lst->raiz; 
    //printf("as %p\n",elemento);
    if (elemento == NULL){//se for pilha vazia
        return;
    }
    while(elemento->ante != NULL){
        printf("%i ",elemento->valor);
        elemento = elemento->ante;
    }
    printf("%i ",elemento->valor);
    printf("\n");
}

//deleta toda a pilha
void deleta_pilha(pilha * lst){
    no * atual = lst->raiz; 
    no * aux = atual;

    while(atual->ante != NULL){
        aux = atual-> ante;
        free(atual);
        atual = aux;
    }
    free(atual);
    free(lst);
}

int main(int argc, char **argv){

    //iniciar o seed
    int seed = time(NULL);
    srand(seed);
    
    pilha *pla = inicia_pilha();

    if (argv[1] != NULL){
        int N = atoi(argv[1]);
        for (int i = 0; i <= N; i ++){
            insert(pla,rand());
        }

        //testar tempo do insert
        int time1 = time(NULL);
        insert(pla,10);
        int time2 = time(NULL)-time1;
        printf("tempo insert: %i\t%i\n",N,time2);

        //testar tempo do remover
        time1 = time(NULL);
        remove_pla(pla);
        time2 = time(NULL)-time1;
        printf("tempo remove: %i\t%i\n",N,time2);

    }

    else{

        insert(pla,1);
        insert(pla,2);
        insert(pla,3);

        //esperado: 3 2 1
        
        print_pilha(pla);//ok
        
        int i = remove_pla(pla);
        //esperado removido = 3
        printf("removido %i\n",i);//ok

        //esperado: 2 1
        print_pilha(pla);//ok

        insert(pla,10);
        //esperado 10 2 1
        print_pilha(pla);//ok

        deleta_pilha(pla);//
    }

    return 0;

}
