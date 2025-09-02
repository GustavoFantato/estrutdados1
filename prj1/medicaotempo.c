#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

/*Grupo 11: 

Victor Kayky Zaneti Antunes NUSP : 15491132
Gustavo Fantato Fernandes NUSP : 16986132
Felipe Galvão Prazeres NUSP: 16828948

CÓDIGO DE SUPORTE PARA MEDIÇÃO DE TEMPO DE EXECUÇÃO
ESTE NÃO É O CÓDIGO QUE SERÁ ENVIADO PARA O RUNCODES POR NÃO SER INTERATIVO E NAO CONTER PRINTS/SAIDAS FORMATADAS PARA OS CASOS DE TESTE
*/

// Printa os elementos do vetor. Usado para debug e verificar se foi feito o que foi pedido

/*void printaVetor(int *vetor, int n){
    for(int i = 0; i < n; i++){
        printf("%d ", vetor[i]);
    }
    printf("\n");
}*/


// Lê os elementos de cada índice do vetor
void leVetor(int *vetor, int n){
    for (int i = 0; i < n; i++){
        scanf("%d", &vetor[i]);
    } // Loop para ler os elementos do vetor
}


// Função que solicita ao usuário o input da opção desejada
int leOpcao(){
    int n;
    scanf("%d", &n); // Lê a opção desejada pelo usuário
    return n;
}

// Opcao 1: Inversão da ordem do vetor de entrada.
    void inverteOrdem(int *vetor, int n){

        int *vetorTemp = malloc(n * sizeof(int)); // Cria um vetor temporário.

        // For para copiar o vetor original para um vetor temporário.
        for(int i = 0; i < n ; i++){
            vetorTemp[i] = vetor[i];
        }

        int contagem; //Contagem dos passos
        int j = n-1; // Índice auxiliar para contar de trás pra frente no vetor
        int aux;
        for (int i = 0; i < n/2; i++){
            aux = vetorTemp[j];
            vetorTemp[j] = vetorTemp[i];
            vetorTemp[i] = aux;
            j--;
        }

        //printaVetor(vetorTemp, n); 
        free(vetorTemp);
}


// Opcao 2: Busca Sequencial no vetor de entrada.
    void buscaSequencial(int *vetor, int n, int x){

        for(int i = 0; i < n; i++){
            if(vetor[i] == x){
                //printf("SIM\n");
                return;
            }
        }
        //printf("NAO\n"); //Se não for encontrado, sai do loop e printa NAO. Se tivesse sido encontado, o return não permitiria chegar nesse printf
    }


// Opcao 3: Busca Binária Iterativa no vetor de entrada.
    void buscaBinIterativa(int *vetor, int n, int x){
        int inicio = 0, fim = n;

        while (inicio <= fim){
            int meio = (inicio+fim) / 2; // acha o meio do vetor

            if(vetor[meio] == x){
                //printf("SIM\n"); 
                return;} // Elemento encontrado, retorna

            if(vetor[meio] < x){ // Se o elemento do vetor do meio for menor que o elemento desejado, o x estará na parte direita do vetor. Assim, desconsideramos o restante do vetor 
                inicio = meio + 1;
            } else { // Se for maior que x, ele estará na parte esquerda do vetor 
                fim = meio - 1; 
            }
        }

        //printf("NAO\n");
    }


// Opcao 4: Busca Binária Recursiva no vetor de entrada
     void buscaBinRecursiva(int *vetor, int inicio, int fim, int x){
        int meio = (inicio + fim) / 2; // Declara e calcula o meio

        if(vetor[meio] == x){
            //printf("SIM\n"); 
            return;} // Caso base: elemento encontrado. Retorna
        if(inicio > fim){
            //printf("NAO\n"); 
            return;} // Caso base: já chegou na ultima divisao binaria e  elemento nao encontrado. Retorna

        if(vetor[meio] < x){
            buscaBinRecursiva(vetor, meio+1, fim, x);
        }

        if(vetor[meio] > x){
            buscaBinRecursiva(vetor, inicio, meio-1, x);
        }

    }

int main(int argc, char *argv[]) {
    // Valida se os argumentos de linha de comando foram passados
    if (argc != 3) {
        printf("Uso: %s <id_algoritmo> <tamanho_n>\n", argv[0]);
        return 1;
    }

    int id_algoritmo = atoi(argv[1]);
    int n = atoi(argv[2]);
    int num_execucoes = 100;

    // Aloca e preenche o vetor para o teste
    int *vetor = malloc(n * sizeof(int));
    for(int i = 0; i < n; i++) {
        vetor[i] = i; // Vetor ordenado
    }
    
    // Valor para o pior caso de busca (garantido que não existe)

    int valor_pior_caso_busca = n + 1;

    struct timeval start, end;
    double total_time;

    // 1. INICIA O CRONÔMETRO (ANTES DO LOOP)
    gettimeofday(&start, NULL);

    // 2. EXECUTA 100 VEZES (SEM PAUSAS/SCANF)
    for (int i = 0; i < num_execucoes; i++) {
        switch (id_algoritmo) {
            case 1:
                inverteOrdem(vetor, n);
                inverteOrdem(vetor, n); // Desfaz para a próxima iteração
                break;
            case 2:
                // Passa o valor de busca diretamente, sem scanf
                buscaSequencial(vetor, n, valor_pior_caso_busca);
                break;
            case 3:
                buscaBinIterativa(vetor, n, valor_pior_caso_busca);
                break;
            case 4:
                buscaBinRecursiva(vetor, 0, n - 1, valor_pior_caso_busca);
                break;
        }
    }

    // 3. PARA O CRONÔMETRO (DEPOIS DO LOOP)
    gettimeofday(&end, NULL);

    // 4. CALCULA O TEMPO E IMPRIME O RESULTADO
    total_time = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
    double tempo_medio = total_time / num_execucoes;
    printf("%d,%.10f\n", n, tempo_medio);

    free(vetor);
    return 0;
}

