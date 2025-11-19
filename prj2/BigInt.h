#ifndef BIGINT_H
#define BIGINT_H
#include <stdbool.h>
#include "ListaEncad.h"

#define POS '+'
#define NEG '-'

typedef struct BigInt{ 
    int size;        // quantidade de blocos (cada bloco com 2 dígitos)
    Node *inicio;    // node menos significativo
    Node *final;     // node mais significativo 
    char sinal;      // positivo (POS) ou negativo (NEG)
} BigInt;

BigInt *create(); 
void destruir(BigInt **n); 

int definir(BigInt *n, const char *decimal);

BigInt *soma(const BigInt *a, const BigInt *b);

bool igual(const BigInt *a, const BigInt *b);
bool maior(const BigInt *a, const BigInt *b);
bool menor(const BigInt *a, const BigInt *b);

void printBigInt(const BigInt *n);

#endif // BIGINT_H
