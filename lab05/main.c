// LINK DO REPL.IT:
// https://replit.com/@FernandoBerthol/Paralelismo-e-Arrays#main.c
//Fernando Brito de Arruda Bertholino
//41906861

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>


//define as matrizes de forma global
#define SIZE 3 // Define o tamanho da matriz
int A[SIZE][SIZE]; // Matriz 1
int B[SIZE][SIZE]; // Matriz 2
int C[SIZE][SIZE]; // Resultante da soma das matrizes
int row, col;
int coluna = 0;

//Função para somar as colunas das matrizes
void* somarLinha(void* p){
  //loop para somar as linhas
    for(row=0; row<3; row++)
    {          
            C[row][coluna] = A[row][coluna] + B[row][coluna];
    }
    coluna++;//soma das colunas
    pthread_exit(somarLinha); //acaba a thread
}

int main()

{

    // Coloca os valores da primeira matriz A
    printf("Coloque os elementos da matriz A de tamanho 3x3: \n");
    for(row=0; row<SIZE; row++)
    {
        for(col=0; col<SIZE; col++)
        {
            scanf("%d", &A[row][col]);
        }
        
    }

    // Coloca os valores da segunda matriz B
    printf("\nColoque os elementos da matriz B de tamanho 3x3: \n");
    for(row=0; row<SIZE; row++)
    {
        for(col=0; col<SIZE; col++)
        {
            scanf("%d", &B[row][col]);
        }
    }
    
    //declara o id das threads
    pthread_t tid[3];
    
    int j;
    //Cria a threads
    for(j = 0; j < 3; j++){
      pthread_create(&tid[j], NULL, somarLinha, (void *)&tid);
    }

    //Junta as threads
    for(j = 0; j < 3; j++){
       pthread_join(tid[j], NULL);
      
    }

    //Imprime as matrizes
      printf("\nSoma das matrizes A+B = \n");
    for(row=0; row<SIZE; row++)
    {
        for(col=0; col<SIZE; col++)
        {
            printf("%d ", C[row][col]);
        }
        printf("\n");
    }


    
    return 0;
}