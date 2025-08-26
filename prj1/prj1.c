#include <stdio.h>
#include <stdlib.h>


/* Você deverá implementar um programa com um pequeno menu, contabilizar o tempo médio
de execução para diferentes entradas, construir um gráfico a partir disso, e contabilizar
suas operações (comparação e atribuição).
O programa deverá implementar:
1. Inversão da ordem do vetor de entrada.
2. Busca Sequencial no vetor de entrada.
3. Busca Binária Iterativa no vetor de entrada.
4. Busca Binária Recursiva no vetor de entrada.
*/

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

}


// Opcao 2: Busca Sequencial no vetor de entrada.
    void buscaSequencial(int *vetor, int n){

    }


// Opcao 3: Busca Binária Iterativa no vetor de entrada.
    void buscaBinIterativa(int *vetor, int n){

    }


// Opcao 4: Busca Binária Recursiva no vetor de entrada
    void buscaBinRecursiva(int *vetor, int n){

    }


void chamaAlgoritmo(int option, int *vetor, int n){
    switch (option)
    {
    case 1:
        inverteOrdem(vetor, n);
        break;
    case 2:
        buscaSequencial(vetor, n);
        break;
    case 3:
        buscaBinIterativa(vetor, n);
        break;
    case 4:
        buscaBinRecursiva(vetor, n);
        break;
    case 5:
        break;
    default:
        printf("Opcao Inválida!\n");
        break;
    }
}








int main(){
    int n = scanf("%d", &n); // Lê o número de elementos do vetor
    int *vetor = malloc(n * sizeof(int)); // Aloca memória dinamicamente de acordo com a quantidade de elementos 

    leVetor(vetor, n); // O usuário insere o elemento de cada índice do vetor


int option; //Opcao do menu
do {
    option = leOpcao(); // "Option" é declarado e lido pela função leOpcao()

    chamaAlgoritmo(option, vetor, n); // De acordo com a opção lida, chama-se a funcao para escolher qual dos algoritmos serão utilizados



} while(option != 5);


    return 0;
}
