#ifndef BIGINT_H
#define BIGINT_H
#include <stdbool.h>

#define POS '+'
#define NEG '-'

typedef struct BigInt{ 
	int size; // quantidade de blocos (cada bloco com 2 dígitos)
	Node *inicio; // node menos significativo
	Node *final; // node mais significativo 
	char sinal; // positivo (POS) ou negativo (NEG)
}BigInt;

BigInt *create(int digitos); // Cria um BigInt com capacidade 'digitos'

int definir(BigInt *n, const char *decimal); // Define o valor do BigInt a partir de uma string decimal. Retorna 1 se sucesso, 0 se falhar

BigInt *soma(const BigInt *a, const BigInt *b); // Soma dois BigInts (novo BigInt) e retorna esse novo BigInt

bool maior(const BigInt *a, const BigInt *b); // Compara se maior, retorna true ou false

bool menor(const BigInt *a, const BigInt *b); // Compara se menor, retorna true ou false

bool igual(const BigInt *a, const BigInt *b); // Compara se igual, retorna true ou false

void destruir(BigInt **n); // Desalocar o BigInt

void printBigInt(const BigInt *n); // Printar o BigInt


#endif // BIGINT_H