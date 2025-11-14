#include <stdio.h>
#include <stdlib.h>

#include "ListaEncad.h"
#include "BigInt.h"

struct node{
	int d0; // Digito menos significativo
	int d1; // Digito mais significativo (do bloco)
	Node *next; // next node da lista
	Node *prev; // node anterior da lista
};

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
        return 0;
    }

    Node* newNode = createNode(d0, d1, NULL, n->final); // cria o novo Node 

    if(!newNode){
        return 0; // falha ao criar o novo Node
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
        return 0;
    }

};

int addNodeStart(BigInt *n, int d0, int d1); // Adiciona um node no inicio do BigInt -- Usado para parsing e soma