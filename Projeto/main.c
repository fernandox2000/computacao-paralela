#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
int thread_count = 1;

void SerieHarmonica(int T,long double* soma)
{
#pragma omp atomic
    *soma += (1.0 / T);
}

int main()
{
    long int T = 1;
    long double soma = 0;
    time_t start = time(NULL);
    while(1)
    {
#pragma omp parallel num_threads(thread_count)
        {
            SerieHarmonica(T,&soma);
#pragma omp atomic
            T++;
        }
        printf("\n %.20Lf %ld",soma,time(NULL) - start);
    }
}