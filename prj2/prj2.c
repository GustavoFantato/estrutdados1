#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BigInt.h"
#include "ListaEncad.h"


/* 
 GRUPO:
    - NOME: GUSTAVO FANTATO FERNANDES
    - NUSP: 16986132

   - NOME: FELIPE GALVAO PRAZERES
   - NUSP: 16828948

    - NOME: VICTOR KAYKY ZANETI ANTUNES
    - NUSP: 15491132

  CONVENCAO DE RETURNS:
    return 1 --> sucesso!
    return 0 --> erro!

*/



int main() {

    int n; // qtd de operacoes a serem executadas
    char operation[6]; // operacoes a serem realizadas
    char num1[501], num2[501]; // numeros sobre os quais serao realizadas as operacoes
    BigInt *A = create();
    BigInt *B = create(); // cria os dois bigints


    scanf("%d", &n);
    
    while(n != 0){ // enquanto n for diferente de 0, fazemos as operacoes

        scanf("%s %s %s", operation, num1, num2); // Leitura das variaveis

        // printf("%s\n%s\n%s\n", operation, num1, num2); //--> debug

        // Como a funcao definir limpa o BigInt antes, nao havera problemas
        definir(A, num1);
        definir(B, num2);

        // printBigInt(A); // --> debug
        // printBigInt(B); // --> debug

        // Realizando as operacoes

        // SOMA
        if(strcmp(operation, "soma") == 0){ // quando strcmp da 0, ambas strings sao iguais

            BigInt *Soma = soma(A, B);

            if(Soma == NULL){ // caso ocorra erro na operacao, por exemplo erro no malloc
                printf("Erro na operacao soma\n");
                destruir(&A);
                destruir(&B);

                return 0;
            }

            printf("Resultado :: ");
            printBigInt(Soma);
            destruir(&Soma);
        }
        
        // OBS: utilizo else if para que caso uma das opcoes ja venham ocorrer, nao realizar a verificacao das outras operacoes

        // MAIOR
        else if(strcmp(operation, "maior") == 0){ // quando strcmp da 0, ambas strings sao iguais       

            printf("Resultado :: ");

            if(maior(A,B) == false){
                printf("False\n");
            } else{
                printf("True\n");
            }
        }

        // MENOR
        else if(strcmp(operation, "menor") == 0){ // quando strcmp da 0, ambas strings sao iguais       

            printf("Resultado :: ");

            if(menor(A,B) == false){
                printf("False\n");
            } else{
                printf("True\n");
            }
        }

        // IGUAL
        else if(strcmp(operation, "igual") == 0){ // quando strcmp da 0, ambas strings sao iguais       

            printf("Resultado :: ");

            if(igual(A,B) == false){
                printf("False\n");
            } else{
                printf("True\n");
            }
        }

        //n = 0; // --> debug


        
        n--; // decrementa para que o loop quebre ao atingir a qtd certa de operacoes
    }

    destruir(&A);
    destruir(&B);

    return 1;
}