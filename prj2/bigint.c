#include "BigInt.h"
#include "ListaEncad.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// --- Criação e Destruição ---

BigInt *create(int digitos) { // Cria a struct BigInt e inicializa os ponteiros e valores
    BigInt *bi = (BigInt *)malloc(sizeof(BigInt));
    if (!bi) return NULL; // Checa se deu ruim na alocacao
    
    bi->inicio = NULL;
    bi->final = NULL;
    bi->size = 0;
    bi->sinal = POS; // Assume o padrao positivo
    return bi;
}

void destruir(BigInt **n) { // Desaloca toda a memoria do BigInt
    if (!n || !(*n)) return; // Checa ponteiros nulos
    
    BigInt *ptr = *n;
    // Remove todos os nós da lista, liberando a memoria de cada um
    while (ptr->size > 0) {
        removeNodeEnd(ptr);
    }
    
    free(ptr); // Libera a memoria da struct principal
    *n = NULL;
}

// --- Parsing (String -> BigInt) ---

int definir(BigInt *n, const char *decimal) { // Converte uma string (ex: "-12345") para a lista encadeada
    if (!n || !decimal) return 0;

    // Limpa a lista antes de adicionar os novos digitos, caso ela já exista
    while (n->size > 0) removeNodeEnd(n);

    int len = strlen(decimal);
    int i = 0;

    // 1. Trata o sinal
    if (decimal[0] == '-') {
        n->sinal = NEG;
        i++; // Pula o '-' na string
    } else {
        n->sinal = POS;
        if (decimal[0] == '+') i++; // Pula o '+' opcional
    }

    // 2. Leitura e criação dos blocos (de trás pra frente)
    
    int pos = len - 1; // Começa pelo ultimo digito da string
    while (pos >= i) {
        int d0 = decimal[pos] - '0'; // Pega o digito menos significativo do bloco
        int d1 = 0;
        pos--; // Anda para trás

        if (pos >= i) {
            d1 = decimal[pos] - '0'; // Pega o digito mais significativo do bloco (se existir)
            pos--; // Anda de novo
        }

        // Adiciona o bloco no final (no lado do menos significativo), mantendo a ordem correta na lista
        if (!addNodeEnd(n, d0, d1)) return 0; // Se a alocacao falhar, retorna erro
    }

    return 1; // Sucesso
}

// --- Output ---

void printBigInt(const BigInt *n) { // Imprime o numero gigante no console
    if (!n || n->size == 0) {
        printf("0");
        return;
    }

    if (n->sinal == NEG) printf("-"); // Imprime o sinal se for negativo

    // 1. Encontra o primeiro nó significativo (ignora os zeros a esquerda do número)
    Node *atual = n->final; // Começa pelo nó mais significativo
    
    // Continua avançando para o anterior enquanto o nó for nulo E NÃO for o único nó
    while (atual != NULL && (atual->d1 == 0 && atual->d0 == 0) && atual->prev != NULL) {
        atual = atual->prev; 
    }

    // 2. Imprime os blocos
    int primeiroBloco = 1;

    while (atual != NULL) {
        // Recria o valor do bloco
        int valor = atual->d1 * 10 + atual->d0;
        
        if (primeiroBloco) {
            // O primeiro bloco é impresso sem padding de zero (ex: 1999, imprime 1)
            printf("%d", valor);
            primeiroBloco = 0;
        } else {
            // Os demais blocos (os menos significativos) sempre precisam de 2 digitos (ex: 05)
            printf("%02d", valor); 
        }
        atual = atual->prev; // Volta para o bloco menos significativo
    }
}

// ============================================================================
// FUNCOES AUXILIARES (Internas)
// ============================================================================

// Funcao interna pra ajudar a comparar só o tamanho dos numeros (ignora o sinal)
// Retorna: 1 se a > b, -1 se a < b, e 0 se forem iguais em modulo
static int compararMagnitude(const BigInt *a, const BigInt *b) {
    // 1. Encontrar o tamanho REAL, ignorando blocos zero à esquerda

    // Ponteiros temporários que ignoram os zeros iniciais
    Node *noA = a->final;
    Node *noB = b->final;

    int sizeA = a->size;
    int sizeB = b->size;

    // Reduz o tamanho de A enquanto houver blocos de zero no começo
    while (sizeA > 1 && noA->d1 == 0 && noA->d0 == 0) {
        noA = noA->prev;
        sizeA--;
    }
    
    // Reduz o tamanho de B enquanto houver blocos de zero no começo
    while (sizeB > 1 && noB->d1 == 0 && noB->d0 == 0) {
        noB = noB->prev;
        sizeB--;
    }


    // 2. Compara os tamanhos REAIS (sem blocos '00')
    if (sizeA > sizeB) return 1;
    if (sizeA < sizeB) return -1;

    // 3. Se os tamanhos são iguais, compara os conteúdos dos nós
    // Usamos os ponteiros 'noA' e 'noB' que já foram ajustados para o primeiro nó não-zero

    while (noA != NULL && noB != NULL) {
        // Primeiro compara o digito mais significativo do bloco (d1)
        if (noA->d1 > noB->d1) return 1;
        if (noA->d1 < noB->d1) return -1;

        // Se d1 for igual, desempata com o d0
        if (noA->d0 > noB->d0) return 1;
        if (noA->d0 < noB->d0) return -1;

        // Continua voltando pro começo da lista
        noA = noA->prev;
        noB = noB->prev;
    }

    return 0; // Chegou aqui, sao identicos em valor absoluto
}

// ============================================================================
// COMPARAÇÕES (Públicas)
// ============================================================================

bool igual(const BigInt *a, const BigInt *b) {
    if (!a || !b) return false; // Protecao basica

    // Se os sinais sao diferentes, impossivel ser igual
    if (a->sinal != b->sinal) return false;

    // REMOVEMOS: a checagem if (a->size != b->size) return false;
    // Pois comparMagnitude ja lida com a diferenca de tamanho causada pelos zeros!

    // Se passou pelo sinal, confere o conteudo. Se compararMagnitude for 0, sao iguais.
    return (compararMagnitude(a, b) == 0);
}

bool maior(const BigInt *a, const BigInt *b) {
    if (!a || !b) return false;

    // Caso 1: Sinais diferentes
    // Se A é positivo e B negativo -> A é maior (True)
    if (a->sinal == POS && b->sinal == NEG) return true;
    
    // Se A é negativo e B positivo -> A é menor (False)
    if (a->sinal == NEG && b->sinal == POS) return false;

    // Caso 2: Sinais iguais
    int mag = compararMagnitude(a, b);

    if (a->sinal == POS) {
        // Se os dois sao positivos, quem tem maior modulo ganha
        return (mag == 1);
    } else {
        // Se os dois sao negativos, quem tem maior modulo é "menor" (ex: -100 < -5)
        // Entao retorna true se A tiver MENOR magnitude
        return (mag == -1);
    }
}

bool menor(const BigInt *a, const BigInt *b) {
    if (!a || !b) return false;

    // Logica inversa do maior
    
    // Sinais diferentes
    if (a->sinal == POS && b->sinal == NEG) return false; // Positivo nunca é menor que negativo
    if (a->sinal == NEG && b->sinal == POS) return true;  // Negativo é sempre menor que positivo

    // Sinais iguais
    int mag = compararMagnitude(a, b);

    if (a->sinal == POS) {
        // Positivos: menor modulo é menor mesmo
        return (mag == -1);
    } else {
        // Negativos: maior modulo é o menor numero (ex: -50 < -2)
        return (mag == 1);
    }
}