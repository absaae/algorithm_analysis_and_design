#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_TAM 10000
typedef unsigned long ulong;

#define MAX_RAND_MOD (ulong)0x80000000
#define A_RAND       (ulong)0x343FD
#define C_RAND       (ulong)0x269EC3
#define SEED         21685489

ulong uNuevoRand() {
    static ulong uXn_1 = SEED;
    ulong uXn = (A_RAND * uXn_1 + C_RAND) % MAX_RAND_MOD;
    uXn_1 = uXn;
    return uXn;
}

char* generarMatrizConstante(char * matriz, ulong N) {
    for (ulong i=0; i< N*N; i++)
        matriz[i] = 'b';
}

char* generarMatrizAleatoria(char * matriz, ulong N) {
    for (ulong i = 0; i < N * N; i++)
        matriz[i] = (char)(uNuevoRand() % 256);
}

// buscamos un elemento tipo c en una matriz NxN
ulong buscarElemento(char* matriz, ulong N, char c) {
    ulong encontrados = 0;
    for (ulong i = 0; i < N * N; i++) {
        if (matriz[i] == c)
            encontrados++;
    }
    return encontrados;
}

int main() {
    ulong tamanos[] = {500, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000};
    ulong num_tamanos = sizeof(tamanos) / sizeof(tamanos[0]);
    FILE* txt = fopen("tiempos_busqueda.txt", "w");
    
    char * matrizConstante = (char*)malloc(MAX_TAM * MAX_TAM * sizeof(char));
    generarMatrizConstante(matrizConstante, MAX_TAM);
    
    char * matrizAleatoria = (char*)malloc(MAX_TAM * MAX_TAM * sizeof(char));
    generarMatrizAleatoria(matrizAleatoria, MAX_TAM);
    
    char buscar;
    double tiempo_peor, tiempo_mejor, tiempo_prom;
    clock_t inicio, fin;
    
    ulong veces = 150;

    for (ulong t = 0; t < num_tamanos; t++) {
        ulong N = tamanos[t];

        buscar = 'a';
        inicio = clock();
        for(ulong i = 0; i < veces; i++) 
        buscarElemento(matrizConstante, N, buscar);
        fin = clock();
        tiempo_mejor = (double)(fin - inicio) / CLOCKS_PER_SEC;
        tiempo_mejor /= veces;

        buscar = matrizConstante[0];
        inicio = clock();
        for(ulong i = 0; i < veces; i++) 
        buscarElemento(matrizConstante, N, buscar);
        fin = clock();
        tiempo_peor = (double)(fin - inicio) / CLOCKS_PER_SEC;
        tiempo_peor /= veces;

        buscar = matrizAleatoria[uNuevoRand() % (N * N)];
        inicio = clock();
        for(ulong i = 0; i < veces; i++) 
        buscarElemento(matrizAleatoria, N, buscar);
        fin = clock();
        tiempo_prom = (double)(fin - inicio) / CLOCKS_PER_SEC;
        tiempo_prom /= veces;

        printf("N=%lu\tMejor=%.6f\tPeor=%.6f\tProm=%.6f\n", N, tiempo_mejor, tiempo_peor, tiempo_prom);
        fprintf(txt, "N=%lu\tMejor=%.6f\tPeor=%.6f\tProm=%.6f\n", N, tiempo_mejor, tiempo_peor, tiempo_prom);
    }

    free(matrizConstante);
    free(matrizAleatoria);
    fclose(txt);
    return 0;
}

