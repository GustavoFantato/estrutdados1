#include <stdio.h>
#include <stdlib.h>

#include "ListaEncad.h"
#include "BigInt.h"

Node* createNode(int d0, int d1, Node *next, Node *prev) {

    Node* newNode = malloc(sizeof(Node)); // aloca espaco pro node

    if (!newNode){
        return NULL; // falha ao alocar
    }

    // Inicializando todas variaveis
    newNode->d0 = d0;
    newNode->d1 = d1;
    newNode->next = next;
    newNode->prev = prev;

    return newNode;
}

int addNodeEnd(BigInt *n, int d0, int d1){ // Adiciona um node no fim do BigInt

    if(!n){
        return -1;
    }

    Node* newNode = createNode(d0, d1, NULL, n->final); // cria o novo Node 

    if(!newNode){
        return -1; // falha ao criar o novo Node
    }

    // Caso 1: Lista vazia
    // Quando a lista esta vazia, o primeiro node dela sera justamente esse que estamos adicionando 

    if(n->inicio == NULL){
        n->inicio = newNode;
        n->final = newNode;
        n->size = 1; // Um novo bloco
        return 1;
    }

    // Caso 2 (já temos um ou mais nodes):
    
    newNode->next = NULL;
    n->final->next = newNode;
    newNode->prev = n->final;
    n->final = newNode;
    n->size++;
    return 1;


}

int removeNodeEnd(BigInt *n){  // Remove o ultimo node do BigInt

    if(!n){
        return -1;
    }   

    // Caso 1: Lista vazia
    if(n->inicio == NULL){
        return 0; // nao eh possivel remover nodes de listas vazias
    }

    Node *ultimo = n->final;

    // Caso 2: só tem 1 elemento
    if(ultimo->prev == NULL){ // se o ultimo prev é NULL, eh pq ele eh o unico node da lista
        n->inicio = NULL;
        n->final = NULL;
        free(ultimo);
        n->size = 0;
        return 1;
    }


    // Caso geral: lista com dois o mais elementos
    
    n->final = ultimo->prev; // joga o final do BigInt para o anterior do atual ultimo n->inicio = newNode;
    n->final->next = NULL;  // como eh o ultimo elemento, aponta para NULL
    free(ultimo);
    n->size--;

    return 1;
}

int addNodeStart(BigInt *n, int d0, int d1){ // Adiciona um node no inicio do BigInt -- Usado para parsing e soma

    if(!n){
        return -1; 
    }

    Node *newNode = createNode(d0, d1, NULL, NULL); // cria o novo node e atribui d0 e d1
    if (!newNode) return -1;

    // Caso 1: lista vazia  (inicio = NULL quer dizer lista vazia)
    if(n->inicio == NULL){
        n->inicio = newNode;
        n->final  = newNode;
        n->size++;
        return 1;
    }
    
    // Caso 2: um ou mais elementos
    newNode->next = n->inicio;
    n->inicio->prev = newNode;
    n->inicio = newNode;
    n->size++;
    return 1;
} 