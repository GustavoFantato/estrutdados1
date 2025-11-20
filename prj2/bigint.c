#include "BigInt.h"
#include "ListaEncad.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Criacao e destruicao

BigInt *create() { // cria o BigInt e inicializa campos
    BigInt *bi = malloc(sizeof(BigInt)); // bi = bigint
    if (!bi) return NULL;

    bi->inicio = NULL; // lista vazia
    bi->final  = NULL;
    bi->size   = 0;
    bi->sinal  = POS;  // padrao eh positivo

    return bi;
}

void destruir(BigInt **n) { // libera todos os nodes e a struct
    if (!n || !(*n)) return;

    BigInt *temp = *n;

    while (temp->size > 0)
        removeNodeEnd(temp); // removendo bloco por bloco

    free(temp);  // libera struct
    *n = NULL;  // evita ponteiro solto
}


// Parsing (string pra BigInt)

int definir(BigInt *n, const char *decimal) { // converte string pra BigInt
    if (!n || !decimal) return -1;

    // limpa antes
    while (n->size > 0)
        removeNodeEnd(n);

    int len = strlen(decimal);
    int i = 0;

    // trata sinal
    if (decimal[0] == '-') {
        n->sinal = NEG;
        i++;
    } else {
        n->sinal = POS;
        if (decimal[0] == '+') i++;
    }

    // monta blocos de 2 digitos (de tras pra frente)
    int pos = len - 1;

    while (pos >= i) {
        int d0 = decimal[pos] - '0'; // menos significativo
        pos--;

        int d1 = 0;
        if (pos >= i) {
            d1 = decimal[pos] - '0'; // mais significativo
            pos--;
        }

        if (!addNodeEnd(n, d0, d1))
            return 0;
    }

    return 1;
}


// Impressao

void printBigInt(const BigInt *n) { // imprime o BigInt
    if (!n || n->size == 0) {
        printf("0");
        return;
    }

    if (n->sinal == NEG)
        printf("-");

    Node *atual = n->final; // comeca pelo mais significativo

    // ignora blocos 00 do topo
    while (atual->prev != NULL && atual->d1 == 0 && atual->d0 == 0)
        atual = atual->prev;

    int primeiro = 1;

    // imprime bloco por bloco
    while (atual != NULL) {
        int valor = atual->d1 * 10 + atual->d0;

        if (primeiro) {
            printf("%d", valor); // primeiro sem padding
            primeiro = 0;
        } else {
            printf("%02d", valor); // outros sempre com 2 digitos
        }

        atual = atual->prev; // vai pro menos significativo
    }
}


// Comparacao auxiliar

static int comparaEmModulo(const BigInt *a, const BigInt *b) {
    Node *noA = a->final;
    Node *noB = b->final;

    int sizeA = a->size;
    int sizeB = b->size;

    // remove blocos 00 do topo de A
    while (sizeA > 1 && noA->d1 == 0 && noA->d0 == 0) {
        noA = noA->prev;
        sizeA--;
    }

    // remove blocos 00 do topo de B
    while (sizeB > 1 && noB->d1 == 0 && noB->d0 == 0) {
        noB = noB->prev;
        sizeB--;
    }

    // compara tamanhos reais
    if (sizeA > sizeB) return 1;
    if (sizeA < sizeB) return -1;

    // mesmo tamanho: compara bloco a bloco
    while (noA && noB) {
        if (noA->d1 > noB->d1) return 1;
        if (noA->d1 < noB->d1) return -1;

        if (noA->d0 > noB->d0) return 1;
        if (noA->d0 < noB->d0) return -1;

        noA = noA->prev;
        noB = noB->prev;
    }

    return 0;
}


// Comparacoes publicas

bool igual(const BigInt *a, const BigInt *b) {
    if (!a || !b) return false;
    if (a->sinal != b->sinal) return false;
    return comparaEmModulo(a, b) == 0;
}

bool maior(const BigInt *a, const BigInt *b) {
    if (!a || !b) return false;

    // sinais diferentes
    if (a->sinal == POS && b->sinal == NEG) return true;
    if (a->sinal == NEG && b->sinal == POS) return false;

    int mag = comparaEmModulo(a, b);

    if (a->sinal == POS)
        return mag == 1; // positivos: maior modulo ganha
    else
        return mag == -1; // negativos: menor modulo ganha
}

bool menor(const BigInt *a, const BigInt *b) {
    if (!a || !b) return false;

    if (a->sinal == POS && b->sinal == NEG) return false;
    if (a->sinal == NEG && b->sinal == POS) return true;

    int mag = comparaEmModulo(a, b);

    if (a->sinal == POS){
        return mag == -1; // positivos: menor modulo eh menor
    } else {
        return mag == 1;  // negativos: maior modulo eh menor
    }
}


// Soma

BigInt *soma(const BigInt *a, const BigInt *b) {
    if (!a || !b) return NULL;

    // Caso 1: sinais iguais (soma normal)
    if (a->sinal == b->sinal) {

        BigInt *result = create(0);
        if (!result) return NULL;
        result->sinal = a->sinal;

        Node *numA = a->inicio; // menos significativo
        Node *numB = b->inicio;

        int carry = 0;

        while (numA != NULL || numB != NULL || carry != 0) {
            int da = 0, db = 0;

            if (numA){
                da = numA->d0 + numA->d1 * 10;
                numA = numA->next;
            }

            if (numB){
                db = numB->d0 + numB->d1 * 10;
                numB = numB->next;
            }

            int soma = da + db + carry;
            carry = soma / 100;  // base 100
            soma = soma % 100;

            int d0 = soma % 10;
            int d1 = soma / 10;

            addNodeEnd(result, d0, d1);
        }

        // remove zeros do topo (lado mais significativo)
        while (result->size > 1 && result->final->d0 == 0 && result->final->d1 == 0)
        {
            removeNodeEnd(result);
        }

        return result;
    }

    // Caso 2: sinais diferentes -> vira subtracao

    int cmp = comparaEmModulo(a, b);

    // |a| = |b| -> resultado eh zero
    if (cmp == 0) {
        BigInt *res = create(0);
        addNodeEnd(res, 0, 0);
        return res;
    }

    // decide quem eh maior em modulo
    const BigInt *maior;
    const BigInt *menor;

    if (cmp == 1) {
        maior = a;
        menor = b;
    } else {
        maior = b;
        menor = a;
    }

    // sinal do resultado eh o do maior em modulo
    char sinalResult = maior->sinal;

    // agora faz maior - menor
    BigInt *result = create(0);
    if (!result) return NULL;
    result->sinal = sinalResult;

    Node *numA = maior->inicio; // menos significativo
    Node *numB = menor->inicio;

    int emprestado = 0;

    while (numA || numB) {
        int da = 0, db = 0;

        if (numA){
            da = numA->d0 + numA->d1 * 10;
            numA = numA->next;
        }

        if (numB){
            db = numB->d0 + numB->d1 * 10;
            numB = numB->next;
        }

        da -= emprestado;

        if (da < db) {
            da += 100;     // empresta 100 pois cada bloco tem 2 digitos
            emprestado = 1;
        } else {
            emprestado = 0;
        }

        int subt = da - db;

        int d0 = subt % 10;
        int d1 = subt / 10;

        addNodeEnd(result, d0, d1);
    }

    // remove zeros a esquerda 
    while (result->size > 1 && result->final->d0 == 0 && result->final->d1 == 0)
    {
        removeNodeEnd(result);
    }

    return result;
}
