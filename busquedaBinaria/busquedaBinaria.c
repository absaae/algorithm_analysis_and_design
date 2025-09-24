#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define repeticiones 3000000

int busquedaBinaria(int * arr, int izq, int der, int x)
{
    if(izq > der)
    {
        return -1;
    }

    int centro = izq + (der - izq) / 2;

    if(arr[centro] > x)
    {
        return busquedaBinaria(arr, izq, centro - 1, x);
    }

    if(arr[centro] < x)
    {
        return busquedaBinaria(arr, centro + 1, der, x);
    }

    return arr[centro];
}

int main()
{
    srand(time(NULL));

    int n0 = 2100;
    int N = 150000000;

    int * arr = (int*)malloc(sizeof(int)*N);
    FILE * archivo = fopen("tiempos_busqueda.txt", "w");

    for(int i=0; i<N; ++i)
    {
        arr[i] = i+1;
    }

    for(int n=n0; n<=N; n*=2)
    {
        struct timespec inicio, fin;

        clock_gettime(CLOCK_MONOTONIC, &inicio);
        for(int i=0; i<repeticiones; ++i)
        {
            busquedaBinaria(arr, 0, n-1, N+1);
        }
        clock_gettime(CLOCK_MONOTONIC, &fin);

        double tiempo = (fin.tv_sec - inicio.tv_sec) + (fin.tv_nsec - inicio.tv_nsec) / 1e9;
        tiempo /= repeticiones;

        fprintf(archivo, "%d %.9f\n", n, tiempo);
        printf("n = %d, promedio = %.9f segundos\n", n, tiempo);
    }

    fclose(archivo);
    free(arr);

    return 69;
}