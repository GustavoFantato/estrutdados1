#include "BigInt.h"
#include <stdio.h>
#include <stdlib.h>


struct BigInt{ 
	int size; // quantidade de blocos (cada bloco com 2 dígitos)
	Node *inicio; // node menos significativo
	Node *final; // node mais significativo 
	char sinal; // positivo (POS) ou negativo (NEG)
};

struct node{
	int d0; // Digito menos significativo
	int d1; // Digito mais significativo (do bloco)
	Node *next; // next node da lista
	Node *prev; // node anterior da lista
};













