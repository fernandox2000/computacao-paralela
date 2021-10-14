// Fernando Brito de Arruda Bertholino
// 41906861

// Link do repl.it:
// https://replit.com/@FernandoBerthol/pthreadparte2

// Link do GitHub:
// https://github.com/fernandox2000/computacao-paralela/blob/main/Pthreads-parte-2/main.c


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//Criando variaveis de forma global para elas poderem ser acessadas tanto pela pthread como pela main
int thread_count;
int m = 3; //definindo tamanho da matriz
int n = 3; //definindo tamanho da matriz
int A[3][3] = { //Criando matriz
  {1,2,3}, 
  {4,5,6}, 
  {7,8,9}
  };
int x[3] = {10,20,30}; //vetor que será multiplicado
int y[3];

void *Pth_mat_vect(void* rank){ //Método de multiplicação matriz-vetor
  long my_rank = (long) rank;
  int i, j;

  int local_m = m/thread_count;
  int my_first_row = my_rank*local_m;
  int my_last_row = (my_rank+1)*local_m - 1;
  
  for(i = my_first_row; i <= my_last_row; i++){
    y[i] = 0.0;
    for(j = 0; j < n; j++){
      y[i] += A[i][j]*x[j];

    }
  }
  return NULL;
} 

int main(int argc, char* argv[]) //main
{
    long thread;
    pthread_t* thread_handles;

    thread_count = 3; //Definindo o count da pthread o tamanho da matriz
    thread_handles = malloc(thread_count*sizeof(pthread_t));

    for(thread = 0;thread < thread_count;thread++) //cria as pthreads
    {
        pthread_create(&thread_handles[thread],NULL,Pth_mat_vect,(void*)thread);
    }
    printf("Chamando a função\n");
    for(thread = 0;thread < thread_count;thread++) //Realiza as pthread de fato
    {
        pthread_join(thread_handles[thread],NULL);
    }

    free(thread_handles);
    int i;

    for(i = 0; i < thread_count; i++){ //Imprime valores de y
      printf("y[%d] = ", i);
      printf("%d\n", y[i]);
    
    }
  
    return 0;
}




