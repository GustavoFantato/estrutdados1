#ifndef LISTAENCAD_H
#define LISTAENCAD_H
#include "BigInt.h"

typedef struct node Node;

Node* createNode(int d0, int d1, Node *next, Node *prev);

int addNodeEnd(BigInt *n, int d0, int d1); // Adiciona um node no fim do BigInt

int removeNodeEnd(BigInt *n); // Remove o ultimo node do BigInt

int addNodeStart(BigInt *n, int d0, int d1); // Adiciona um node no inicio do BigInt -- Usado para parsing e soma


#endif 