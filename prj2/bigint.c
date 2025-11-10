#include "BigInt.h"
#include <stdio.h>
#include <stdlib.h>


struct BigInt{
	int len; // quantidade de dígitos utilizados
	int cap; // capacidade máxima de dígitos
	int *head; // ponteiro para o array de dígitos
	char sinal; // positivo ou negativo
};









