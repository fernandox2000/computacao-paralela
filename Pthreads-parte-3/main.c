// Fernando Brito de Arruda Bertholino
// 41906861

// Link do repl.it:
// https://replit.com/@FernandoBerthol/CalculoDePi#main.c

// Link do GitHub:
// https://github.com/fernandox2000/computacao-paralela/tree/main/Pthreads-parte-3

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int thread_count;
double sum;
long long n = 100000;
double pi;

void* Thread_sum(void* rank){
  long my_rank = (long) rank;
  double factor;
  long long i;
  long long my_n = n/thread_count;
  long long my_first_i = my_n*my_rank;
  long long my_last_i = my_first_i + my_n;

  if(my_first_i % 2 == 0){
  factor = 1.0;
  }
  else{
    factor = - 1.0;
  }
  for(i = my_first_i; i < my_last_i; i++, factor = -factor){
    sum += factor/(2*i+1);
  }
  pi = sum*4;
  return NULL;
}

int main(int argc, char* argv[]) //main
{
    long thread;
    pthread_t* thread_handles;

    thread_count = strtol(argv[1], NULL, 10);
   // thread_count = 2; //Definindo o count da pthread o tamanho da matriz
    thread_handles = malloc(thread_count*sizeof(pthread_t));

    for(thread = 0;thread < thread_count;thread++) //cria as pthreads
    {
        pthread_create(&thread_handles[thread],NULL,Thread_sum,(void*)thread);
    }
    printf("Chamando a função\n");
    for(thread = 0;thread < thread_count;thread++) //Realiza as pthread de fato
    {
        pthread_join(thread_handles[thread],NULL);
    }

    free(thread_handles);
    
    printf("pi = %lf", pi);

    return 0;
}




