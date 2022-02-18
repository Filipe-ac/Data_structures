#include<stdio.h>
#include<stdlib.h>
#include <time.h>

/*
    permite inserir/buscar/deletar em O log(n) (melhor caso)

*/


// Definir o no
typedef struct Node_st{
    int valor; //valor atribuido ao no
    struct Node_st *direita; //ponteiro com a posicao do proximo no
    struct Node_st *esquerda;
    struct Node_st *parent;
} no;

// Definir a abb
typedef struct abb_st //tipo particualr de no.
{   
    no * raiz;//apenas aponta para a raiz
    int lenght; //tamanho da abb

} abb;



//metodo para iniciar uma abb
abb * inicia_abb(){//criar um pointer para a abb

    abb * lst = (abb *) malloc(sizeof(abb)); //aloca a memoria para a abb. lst e POINTER
    lst->raiz = NULL;
    lst->lenght = 0;

    return lst;
}

no * busca_rec(no * atual, int valor){

    //busca recursivamente por um no com determinado valor embaixo do no atual

    if (atual->valor == valor){
        return atual;
    }

    if (atual->direita != NULL && valor > atual->valor){
        busca_rec(atual->direita,valor);
    }
    else if (atual->esquerda != NULL &&  valor <= atual->valor){
        busca_rec(atual->esquerda,valor);
    }
    else{
        return atual;
    }
}

no * busca(abb * lst, int valor){
    //chama a funcao busca_rec a partir do no raiz
    if (lst->raiz == NULL){
        return lst->raiz;
    }
    else{
        return busca_rec(lst->raiz,valor);
    }
}


//busca a folha apropriada a partir de determinado no (usado na funcao insert)
no * busca_folha_rec(no * atual, int valor){
    
    
    if (atual->direita != NULL && valor > atual->valor){
        busca_folha_rec(atual->direita,valor);
    }
    else if (atual->esquerda != NULL &&  valor <= atual->valor){
        busca_folha_rec(atual->esquerda,valor);
    }
    else{
        return atual;
    }
}
//chama a funcao  busca_folha_rec a partir da raiz
//ou insere o primeiro elemento
no * busca_folha(abb * lst, int valor){
    if (lst->raiz == NULL){
        return lst->raiz;
    }
    else{
        return busca_folha_rec(lst->raiz,valor);
    }
}

no * busca_minimo(no * atual){
    //caminhar sempre para a esquerda ate achar a folha
    if (atual->esquerda != NULL){
        atual = busca_minimo(atual->esquerda);
    }
    return atual;
}

//deleta (se existir) o primeiro no encontrado com determinado valor
void delet(abb * lst,int valor){
    if (lst->raiz == NULL){
        return;
    }
    no * deletar = busca_rec(lst->raiz,valor);
    if (deletar->valor == valor){

        //decidir se esta a direita (pos = 1) ou esquerda (pos = 0) do parent
        int pos;
        if (deletar->valor > deletar->parent->valor){
            pos = 1;
        }
        else{
            pos = 0;
        }
        //caso em que e folha
        if(deletar-> esquerda == NULL && deletar -> direita == NULL){
            if (pos == 1){
                deletar->parent->direita = NULL;
            }
            else{
                deletar->parent->esquerda = NULL;
            }
        }
        //dois filhos Definicao: substituir pelo menor elemento da sub arvore a direita do elemento a ser deletado
        else if (deletar -> esquerda != NULL && deletar -> direita != NULL){
            no * substituto = busca_minimo(deletar->direita);
            //checar se nao e o mesmo
            if (deletar->esquerda != substituto){
                substituto->esquerda = deletar->esquerda;
            } 
            else{
                substituto->esquerda = NULL;
            }
            if (deletar->direita != substituto){
                substituto->direita = deletar->direita;
            }
            else{
                substituto->direita = NULL;
            }
            //se for a raiz
            if (lst->raiz == deletar){
                lst->raiz = substituto;
            }
            else{
                substituto->parent = deletar->parent;
                //referenciar a direita ou esquerda do pai
                if (pos == 1){
                    substituto->parent->direita = substituto;
                }
                else{
                    substituto->parent->esquerda = substituto;
                }
            }

        }   
        //um filho
        else{
            
            if(deletar->esquerda != NULL){
                if(pos == 1){
                    deletar->parent->direita = deletar->esquerda;
                }
                else{
                    deletar->parent->esquerda = deletar->esquerda;
                }
            }
            if(deletar->direita != NULL){
                if(pos == 1){
                    deletar->parent->direita = deletar->direita;
                }
                else{
                    deletar->parent->esquerda = deletar->direita;
                }
            }
        }
        
    free(deletar);
    }
    
}

//inserir elemento no lugar adequado
void insert(abb * lst,int valor){

    //criar novo no inicio da abb
    no * novo = (no *) malloc (sizeof(no));
    novo->valor = valor;
    novo->esquerda = NULL;
    novo->direita = NULL;

    if (lst->raiz == NULL){
        lst->raiz = novo;
        novo -> parent = lst->raiz;
    }

    else{
        no * parent = busca_folha(lst,valor); //encontrar a folha certa
        if (valor > parent->valor){
            parent->direita = novo;
        }
        else{
            parent->esquerda = novo;
        }
        novo->parent = parent;
    }
    lst->lenght = lst->lenght + 1;
 
}

//funcao auxiliar para imprimir recursivamente a partir de dado no
void print_no(no * atual,int h,int pos){
    
    if (pos >= 0){
        printf("coluna: %i, h: %i ",pos,h);
    }
    else{
        printf("coluna: %i, h: %i ",pos,h);
    }
    printf("%i\n",atual->valor);

    if (atual->direita != NULL){
        print_no(atual->direita,h+1,pos + 1);
    }
    if (atual->esquerda != NULL)
    {   
        print_no(atual->esquerda,h+1,pos - 1);
    }

    
}

//chama a funcao print_no a partir da raiz
void print_abb(abb * lst){
    
    if (lst->raiz == NULL){
        return;
    }
    int h = 0; //altura (raiz = 0)
    int pos = 0; //coluna (raiz = 0), apenas para saber se a arvore esta certa
    print_no(lst->raiz,h,pos);
    printf("\n");
}


void esq_dir(no * atual,int h){
    /*
    printa recursivamente primeiro os da esquerda e depois direita
    */
    printf("h: %i = %i\n",h,atual->valor);
    if (atual->esquerda != NULL){
        esq_dir(atual->esquerda,h+1);
    }
    if (atual->direita != NULL){
        esq_dir(atual->direita,h+1);
    }
}


void dir_esq(no * atual,int h){
    /*
    printa recursivamente primeiro os da direita e depois esquerda
    */
    printf("h: %i = %i\n",h,atual->valor);
    if (atual->direita != NULL){
        dir_esq(atual->esquerda,h+1);
    }
    if (atual-> esquerda!= NULL){
        dir_esq(atual->direita,h+1);
    }
}


void pre_ordem(abb * lst){
    /*
    raiz,esquerda,direita
    */
   int h = 0;
   printf("h:0 = %i\n",lst->raiz->valor);
   if (lst->raiz->esquerda != NULL){
       esq_dir(lst->raiz->esquerda,h+1);
   }
   if (lst->raiz->direita != NULL){
       esq_dir(lst->raiz->direita,h+1);
   }   
}



void ordem(abb * lst){
    /*
    esquerda,raiz,direita
    */
   int h = 0;
   
   if (lst->raiz->esquerda != NULL){
       esq_dir(lst->raiz->esquerda,h+1);
   }
   printf("h:0 = %i\n",lst->raiz->valor);
   if (lst->raiz->direita != NULL){
       esq_dir(lst->raiz->direita,h+1);
   }   
}

void pos_ordem(abb * lst){
    /*
    esquerda,direita,raiz
    */

   int h = 0;
   
   if (lst->raiz->esquerda != NULL){
       esq_dir(lst->raiz->esquerda,h+1);
   }
   
   if (lst->raiz->direita != NULL){
       esq_dir(lst->raiz->direita,h+1);
   }   
   printf("h:0 = %i\n",lst->raiz->valor);
}


//deleta recursivamente os nos. Auxiliar para a funcao deleta_abb
void deleta_abb_recursivo(no * atual){
    if (atual->direita != NULL){
        deleta_abb_recursivo(atual->direita);
    }
    if (atual->esquerda != NULL){
        deleta_abb_recursivo(atual->esquerda);
    }
    free(atual);
}

//deleta a arvore toda
void deleta_abb(abb * lst){
    //deleta a lista e todas as entradas
    deleta_abb_recursivo(lst->raiz);
    free(lst);
}

int main(int argc, char **argv){

    //iniciar a arvore
    abb *lst = inicia_abb();

    //iniciar o seed
    int seed = time(NULL);
    srand(seed);

    if (argv[1] != NULL){
        int N = atoi(argv[1]);
        for (int i = 0; i <= N; i ++){
            insert(lst,rand());
        }

        //testar tempo do insert
        int time1 = time(NULL);
        insert(lst,165542);
        int time2 = time(NULL)-time1;
        printf("tempo insert: %i\t%i\n",N,time2);

        //testar tempo do remover
        time1 = time(NULL);
        delet(lst,165542);
        time2 = time(NULL)-time1;
        printf("tempo remove: %i\t%i\n",N,time2);

    }

    else{
        
        insert(lst,5);
        insert(lst,3);
        insert(lst,2);
        insert(lst,4);
        insert(lst,7);
        insert(lst,6);
        insert(lst,8);

        /*esperado:
            c-2 c-1 c0 c1 c2
        h=0            5
        h=1         3      7
        h=2      2    4 6     8 
        */
        print_abb(lst);//ok
        


        pre_ordem(lst);//ok
        /*esperado:
        5 3 2 4 7 6 8
        */
        printf("\n\n");
        
        ordem(lst);//ok
        /*esperado:
        3 2 4 5 7 6 8
        */
        printf("\n\n");

        pos_ordem(lst);//ok
        /*esperado:
        3 2 4 7 6 8 5
        */ 
        printf("\n\n");
        

        //testar funcao delet (retirar valores)

        //retirar uma folha
        delet(lst,2);
        /*esperado:
            c-2 c-1 c0 c1 c2
        h=0            5
        h=1         3      7
        h=2           4 6     8 
        */
        print_abb(lst);//ok

        
        //retirar no com 1 filho
        printf("\n");
        delet(lst,3);
        /*esperado:
            c-2 c-1 c0 c1 c2
        h=0            5
        h=1         4      7
        h=2             6     8 
        */
        print_abb(lst);//ok

        

        //teste para deletar a raiz: Espera-se que o 7 substitua a raiz
        delet(lst,7);
        /*esperado:
            c-2 c-1 c0 c1 c2
        h=0            5
        h=1         4      8
        h=2                   6 
        */    
        print_abb(lst);//ok


        //exluir toda a arvore
        deleta_abb(lst);
    }
    return 0;
}
