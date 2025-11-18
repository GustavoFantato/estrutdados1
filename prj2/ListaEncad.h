#ifndef LISTAENCAD_H
#define LISTAENCAD_H


typedef struct BigInt BigInt;
typedef struct node Node;

struct node{
	int d0; // Digito menos significativo
	int d1; // Digito mais significativo (do bloco)
	Node *next; // next node da lista
	Node *prev; // node anterior da lista
};

Node* createNode(int d0, int d1, Node *next, Node *prev);

int addNodeEnd(BigInt *n, int d0, int d1); // Adiciona um node no fim do BigInt

int removeNodeEnd(BigInt *n); // Remove o ultimo node do BigInt

int addNodeStart(BigInt *n, int d0, int d1); // Adiciona um node no inicio do BigInt -- Usado para parsing e soma


#endif 