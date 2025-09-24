#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define max_bits 4096
#define repeticiones 1000

typedef void (*codigo)(int *M, int *m, int *R, int n);

void bits_random(int *bits, int n){
    for (int i = 0; i < n; i++){
        bits[i] = rand() % 2;
    }
}

void copiar(int *destino, const int *origen, int n){
    for (int i = 0; i < n; i++){
        destino[i] = origen[i];
    }
}

void pa_la_izq(int *bits, int n, int posiciones){
    if (posiciones >= n) {
        for (int i = 0; i < n; i++){
            bits[i] = 0;
            return;
        }
    }

    for (int i = 0; i < n - posiciones; i++){
        bits[i] = bits[i + posiciones];
    }

    for (int i = n - posiciones; i < n; i++){
        bits[i] = 0;
    }
}

void suma(const int *A, int *B, int *R, int n){
    int carry = 0;
    for (int i = n - 1; i >= 0; i--){
        int sum = A[i] + B[i] + carry;
        R[i] = sum % 2;
        carry = sum / 2;   
    }
}

void limpieza(int *bits, int n){
    for (int i = 0; i < n; i++){
        bits[i] = 0;
    }
}

void paratodos(codigo codigo, const char *nombre_archivo, const char *nombre_codigo){
    FILE *archivo = fopen(nombre_archivo, "w");
    
    int tamanos[] = {16, 32, 64, 128, 256, 512, 1024, 1670, 2048};
    int num_tamanos = sizeof(tamanos) / sizeof(tamanos[0]);

    for (int t = 0; t < num_tamanos; t++) {
        int n = tamanos[t];
        double suma_tiempos = 0.0;

        for (int rep = 0; rep < repeticiones; rep++) {
            int M[max_bits], m[max_bits], R[2 * max_bits];
            bits_random(M, n);
            bits_random(m, n);
            limpieza(R, 2 * n);

            clock_t inicio = clock();
            codigo(M, m, R, n);
            clock_t fin = clock();

            double tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;
            suma_tiempos += tiempo;
        }

        double tiempo_promedio = suma_tiempos / repeticiones;
        printf("%s - n = %d\t Tiempo promedio: %.10f s\n", nombre_codigo, n, tiempo_promedio);
        fprintf(archivo, "%d %.10f\n", n, tiempo_promedio);
    }

    fclose(archivo);
    
}

void codigo1(int *M, int *m, int *R, int n){
    int A[2 * max_bits];
    int M_ext[2 * max_bits];

    limpieza(M_ext, 2 * n);
    for (int i = 0; i < n; i++){
        M_ext[n + i] = M[i];
    }

    for (int i = 0; i < n; i++){
        if (m[n - 1 - i] == 1){
            copiar(A, M_ext, 2 * n);
        } else {
            limpieza(A, 2 * n);
        }

        pa_la_izq(A, 2 * n, i);
        suma(R, A, R, 2 * n);
    }
}

void codigo2(int *M, int *m, int *R, int n){
    int A[2 * max_bits];
    int M_ext[2 * max_bits];

    limpieza(M_ext, 2 * n);
    for (int i = 0; i < n; i++){
        M_ext[n + i] = M[i];
    }

    for (int i = 0; i < n; i++){
        if (m[n - 1 - i] == 1){
            copiar(A, M_ext, 2 * n);
            pa_la_izq(A, 2 * n, i);
            suma(R, A, R, 2 * n);
        }
    }
}

void codigo3(int *M_original, int *m, int *R, int n){
    int M[2 * max_bits];
    int R_local[2 * max_bits];

    limpieza(M, 2 * n);
    limpieza(R_local, 2 * n);

    for (int i = 0; i < n; i++){
        M[n + i] = M_original[i];
    }

    for (int i = 0; i < n; i++){
        if (m[n - 1 - i] == 1){
            suma(R_local, M, R_local, 2 * n);
        }
        
        pa_la_izq(M, 2 * n, 1);
    }

    copiar(R, R_local, 2 * n);
}

void codigo4peor(int *M, int *m, int *R, int n){
    int a = 0;
    int b = (1 << n) - 1;
    int resultado = 0;

    for (int i = 0; i < n; i++) {
        a = (a << 1) | (rand() % 2);
    }

    for (int i = 0; i < b; i++) {
        resultado += a;
    }

    R[0] = resultado;
}

int main() {

    srand(time(NULL));
    
    paratodos(codigo1, "tiempos_codigo1.txt", "código 1");

    printf("\n");
    paratodos(codigo2, "tiempos_codigo2.txt", "código 2");

    printf("\n");
    paratodos(codigo3, "tiempos_codigo3.txt", "código 3");

    printf("\n");
    FILE *archivo = fopen("tiempos_codigo4.txt", "w");
    if (!archivo) {
        perror("No se pudo abrir el archivo");
        return 1;
    }

    int tamanos[] = {4, 6, 8, 10, 12, 14, 16, 18, 20};
    int num_tamanos = sizeof(tamanos) / sizeof(tamanos[0]);

    for (int t = 0; t < num_tamanos; t++) {
        int n = tamanos[t];
        double suma_tiempos = 0.0;

        for (int i = 0; i < repeticiones; i++) {
            int M[max_bits], m[max_bits], R[2 * max_bits];

            clock_t inicio = clock();
            codigo4peor(M, m, R, n);
            clock_t fin = clock();

            double tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;
            suma_tiempos += tiempo;
        }

        double tiempo_promedio = suma_tiempos / repeticiones;
        printf("Código 4(peor caso) - n = %d\t Tiempo promedio: %.10f s\n", n, tiempo_promedio);
        fprintf(archivo, "%d %.10f\n", n, tiempo_promedio);
    }

    fclose(archivo);



    
    return 0;
}

