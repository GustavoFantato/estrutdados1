#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

/* Grupo 11: Código final para medição e contagem */

// --- CONTADORES GLOBAIS ---
long long g_comparacoes = 0;
long long g_atribuicoes = 0;

// --- FUNÇÕES DOS ALGORITMOS (CORRIGIDAS E INSTRUMENTADAS) ---

// Opcao 1: Inversão da ordem do vetor de entrada.
void inverteOrdem(int *vetor, int n){
    // Função segura: cria cópia interna na heap
    int *vetorTemp = malloc(n * sizeof(int)); g_atribuicoes++;
    if (vetorTemp == NULL) return; 

    g_comparacoes++; // for inicial
    for(int i = 0; i < n ; i++){
        g_comparacoes++; // check do loop
        vetorTemp[i] = vetor[i]; g_atribuicoes++;
        g_atribuicoes++; // i++
    }

    int j = n-1; g_atribuicoes++;
    int aux; // declaração não conta como atribuição

    g_comparacoes++; // for inicial
    for (int i = 0; i < n/2; i++){
        g_comparacoes++; // check do loop
        aux = vetorTemp[j];           g_atribuicoes++;
        vetorTemp[j] = vetorTemp[i];  g_atribuicoes++;
        vetorTemp[i] = aux;           g_atribuicoes++;
        j--;                          g_atribuicoes++; // j = j - 1
        g_atribuicoes++; // i++
    }
    
    free(vetorTemp);
}

// Opcao 2: Busca Sequencial no vetor de entrada.
void buscaSequencial(int *vetor, int n, int x){
    g_comparacoes++; // for inicial
    for(int i = 0; i < n; i++){
        g_comparacoes++; // check do loop
        
        g_comparacoes++; // if (vetor[i] == x)
        if(vetor[i] == x){
            return;
        }
        g_atribuicoes++; // i++
    }
}

// Opcao 3: Busca Binária Iterativa no vetor de entrada.
// (Versão corrigida e padronizada)
void buscaBinIterativa(int *vetor, int n, int x){
    int inicio = 0; g_atribuicoes++;
    int fim = n - 1; g_atribuicoes++; 

    g_comparacoes++; // Comparação inicial do while
    while (inicio <= fim){
        g_comparacoes++; // Comparação de cada loop
        
        int meio = inicio + (fim - inicio) / 2; g_atribuicoes++;

        g_comparacoes++; // if (vetor[meio] == x)
        if(vetor[meio] == x){
            return;
        }

        g_comparacoes++; // if (vetor[meio] < x)
        if(vetor[meio] < x){ 
            inicio = meio + 1; g_atribuicoes++;
        } else {
            fim = meio - 1; g_atribuicoes++;
        }
    }
}

// Opcao 4: Busca Binária Recursiva no vetor de entrada
// (Versão corrigida e padronizada)
void buscaBinRecursiva(int *vetor, int inicio, int fim, int x){
    g_comparacoes++; // if (inicio > fim)
    if(inicio > fim){
        return;
    } 
    
    int meio = inicio + (fim - inicio) / 2; g_atribuicoes++;

    g_comparacoes++; // if (vetor[meio] == x)
    if(vetor[meio] == x){
        return;
    } 

    g_comparacoes++; // if (vetor[meio] < x)
    if(vetor[meio] < x){
        buscaBinRecursiva(vetor, meio+1, fim, x);
    } else {
        buscaBinRecursiva(vetor, inicio, meio-1, x);
    }
}

// --- MAIN (NÃO-INTERATIVO) ---

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Uso: %s <id_algoritmo> <tamanho_n>\n", argv[0]);
        return 1;
    }

    int id_algoritmo = atoi(argv[1]);
    int n = atoi(argv[2]);
    int num_execucoes = 100;

    int *vetor = malloc(n * sizeof(int));
    for(int i = 0; i < n; i++) {
        vetor[i] = i; 
    }
    
    int valor_pior_caso_busca = n + 1;

    struct timeval start, end;
    double total_time;

    // ZERA OS CONTADORES GLOBAIS ANTES DO LOOP
    g_comparacoes = 0;
    g_atribuicoes = 0;

    gettimeofday(&start, NULL);

    for (int i = 0; i < num_execucoes; i++) {
        // Switch simples, pois inverteOrdem já lida com a cópia
        switch (id_algoritmo) {
            case 1:
                inverteOrdem(vetor, n);
                break;
            case 2:
                buscaSequencial(vetor, n, valor_pior_caso_busca);
                break;
            case 3:
                // Chamada padronizada
                buscaBinIterativa(vetor, n, valor_pior_caso_busca);
                break;
            case 4:
                // Chamada padronizada
                buscaBinRecursiva(vetor, 0, n - 1, valor_pior_caso_busca);
                break;
        }
    }

    gettimeofday(&end, NULL);

    total_time = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
    double tempo_medio = total_time / num_execucoes;

    // IMPRIME A SAÍDA DE 4 VALORES
    printf("%d,%.10f,%lld,%lld\n", n, tempo_medio, (g_comparacoes / num_execucoes), (g_atribuicoes / num_execucoes));

    free(vetor);
    return 0;
}