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

// Printa os elementos do vetor. Usado para debug e verificar se foi feito o que foi pedido
void printaVetor(int *vetor, int n){
    for(int i = 0; i < n; i++){
        printf("%d ", vetor[i]);
    }
    printf("\n");
}


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
        int contagem; //Contagem dos passos
        int j = n-1; // Índice auxiliar para contar de trás pra frente no vetor
        int aux;
        for (int i = 0; i < n/2; i++){
            aux = vetor[j];
            vetor[j] = vetor[i];
            vetor[i] = aux;
            j--;
        }
        // printaVetor(vetor, n); 
        // printf("%d", contagem);
}


// Opcao 2: Busca Sequencial no vetor de entrada.
    void buscaSequencial(int *vetor, int n){
        int x;
        scanf("%d", &x); // Lê valor desejado a ser buscado

        for(int i = 0; i < n; i++){
            if(vetor[i] == x){
                printf("SIM\n");
                return;
            }
        }
        printf("NAO\n"); //Se não for encontrado, sai do loop e printa NAO. Se tivesse sido encontado, o return não permitiria chegar nesse printf
    }


// Opcao 3: Busca Binária Iterativa no vetor de entrada.
    void buscaBinIterativa(int *vetor, int n, int x){
        int inicio = 0, fim = n;

        while (inicio <= fim){
            int meio = (inicio+fim) / 2; // acha o meio do vetor

            if(vetor[meio] == x){printf("SIM\n"); return;} // Elemento encontrado, retorna

            if(vetor[meio] < x){ // Se o elemento do vetor do meio for menor que o elemento desejado, o x estará na parte direita do vetor. Assim, desconsideramos o restante do vetor 
                inicio = meio + 1;
            } else { // Se for maior que x, ele estará na parte esquerda do vetor 
                fim = meio - 1; 
            }
        }

        printf("NAO\n");
    }


// Opcao 4: Busca Binária Recursiva no vetor de entrada
     void buscaBinRecursiva(int *vetor, int inicio, int fim, int x){
        int meio = (inicio + fim) / 2; // Declara e calcula o meio

        if(vetor[meio] == x){printf("SIM\n"); return;} // Caso base: elemento encontrado. Retorna
        if(inicio > fim){printf("NAO\n"); return;} // Caso base: já chegou na ultima divisao binaria e  elemento nao encontrado. Retorna

        if(vetor[meio] < x){
            buscaBinRecursiva(vetor, meio+1, fim, x);
        }

        if(vetor[meio] > x){
            buscaBinRecursiva(vetor, inicio, meio-1, x);
        }

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
        int x;
        scanf("%d", &x);
        buscaBinIterativa(vetor, n-1, x);
        break;
    case 4:
        int y ;
        scanf("%d", &y);
        buscaBinRecursiva(vetor, 0, n-1, y);
        break;
    case 5:
        break;
    default:
        printf("Opcao Inválida!\n");
        break;
    }
}








int main(){
    int n;
    scanf("%d", &n); // Lê o número de elementos do vetor
    int *vetor = malloc(n * sizeof(int)); // Aloca memória dinamicamente de acordo com a quantidade de elementos 

    leVetor(vetor, n); // O usuário insere o elemento de cada índice do vetor


int option; //Opcao do menu
do {
    option = leOpcao(); // "Option" é declarado e lido pela função leOpcao()

    chamaAlgoritmo(option, vetor, n); // De acordo com a opção lida, chama-se a funcao para escolher qual dos algoritmos serão utilizados



} while(option != 5);


    return 0;
}
