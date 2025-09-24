#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef unsigned long ulong;


void generando(ulong *A, ulong n, ulong k) {
    // los primeros k elementos ordenados
    for (ulong i = 0; i < k; ++i) {
        A[i] = i;
    }

    // los últimos n-k elementos en orden también paraaa poder
    for (ulong i = k; i < n; ++i) {
        A[i] = i;
    }

    // aplicar fisher yattes a la segunda mitad
    for (ulong i = n - 1; i > k; --i) {
        ulong j = k + rand() % (i - k + 1);
        ulong tmp = A[i];
        A[i] = A[j];
        A[j] = tmp;
    }
}


void bubbleSort(ulong *A, ulong n) {
    int salir;
    ulong i = 0, j, aux;
    do {
        salir = 1;
        for (j = 0; j < n - i - 1; j++) {
            if (A[j] > A[j + 1]) {
                aux = A[j];
                A[j] = A[j + 1];
                A[j + 1] = aux;
                salir = 0;
            }
        }
        i++;
    } while (!salir);
}


void insertionSort(ulong *A, ulong n) {
    ulong i, j, key;
    for (i = 1; i < n; i++) {
        key = A[i];
        j = i;
        while (j > 0 && A[j - 1] > key) {
            A[j] = A[j - 1];
            j--;
        }
        A[j] = key;
    }
}


void selectionSort(ulong *A, ulong n) {
    ulong i, j, min, aux;
    for (i = 0; i < n - 1; i++) {
        min = i;
        for (j = i + 1; j < n; j++) {
            if (A[j] < A[min]) {
                min = j;
            }
        }
        aux = A[i];
        A[i] = A[min];
        A[min] = aux;
    }
}


double medirTiempo(void (*sortFunc)(ulong *, ulong), ulong *A, ulong n) {
    struct timespec start, stop;
    clock_gettime(CLOCK_MONOTONIC, &start);
    sortFunc(A, n);
    clock_gettime(CLOCK_MONOTONIC, &stop);
    return (double)((stop.tv_sec - start.tv_sec) + (stop.tv_nsec - start.tv_nsec) / 1e9);
}

int main() {
    ulong valores_n[] = {15000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000, 101000, 102000, 103000, 104000, 105000, 106000};
    ulong valores_k[] = {0, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 11000, 12000, 13000, 14000};
    int total_n = sizeof(valores_n) / sizeof(valores_n[0]);
    int total_k = sizeof(valores_k) / sizeof(valores_k[0]);

    ulong *A = NULL;
    FILE *file;
    double t;

    // bubble Sort: T(n,k)
    file = fopen("bubble_tnk.txt", "w");
    fprintf(file, "# n\tk\tTiempo\n");
    for (int i = 0; i < total_n; i++) {
        ulong n = valores_n[i];
        A = (ulong *)malloc(n * sizeof(ulong));
        for (int j = 0; j < total_k; j++) {
            ulong k = valores_k[j];
            generando(A, n, k);
            t = medirTiempo(bubbleSort, A, n);
            fprintf(file, "%lu\t%lu\t%.8lf\n", n, k, t);
        }
        free(A);
    }
    fclose(file);

    // insertion Sort: T(n,k)
    file = fopen("insertion_tnk.txt", "w");
    fprintf(file, "# n\tk\tTiempo\n");
    for (int i = 0; i < total_n; i++) {
        ulong n = valores_n[i];
        A = (ulong *)malloc(n * sizeof(ulong));
        for (int j = 0; j < total_k; j++) {
            ulong k = valores_k[j];
            generando(A, n, k);
            t = medirTiempo(insertionSort, A, n);
            fprintf(file, "%lu\t%lu\t%.8lf\n", n, k, t);
        }
        free(A);
    }
    fclose(file);

    // selection Sort: mejor vs peor
    file = fopen("selection_mejor_peor.txt", "w");
    fprintf(file, "# n\tMejor(s)\tPeor(s)\n");
    for (int i = 0; i < total_n; i++) {
        ulong n = valores_n[i];
        A = (ulong *)malloc(n * sizeof(ulong));
        generando(A, n, n); // mejor caso: completamente ordenado
        double mejor = medirTiempo(selectionSort, A, n);
        generando(A, n, 0); // peor caso: completamente desordenado
        double peor = medirTiempo(selectionSort, A, n);
        fprintf(file, "%lu\t%.8lf\t%.8lf\n", n, mejor, peor);
        free(A);
    }
    fclose(file);

    return 0;
}