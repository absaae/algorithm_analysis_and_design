
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NUM_DEN 5

int denominaciones[NUM_DEN] = {15, 10, 5, 2, 1};
int cantidades[NUM_DEN] = {5, 9, 10, 21, 13};

typedef enum {
    menor,
    mayor,
    mayorCantidad,
    menorCantidad,
    cercano
} Caso;

const char* nombreCaso(Caso caso) {
    switch (caso) {
        case menor: return "Menor Valor";
        case mayor: return "Mayor Valor";
        case mayorCantidad: return "Mayor Cantidad";
        case menorCantidad: return "Menor Cantidad";
        case cercano: return "Más cercano a lo buscado";
        default: return "Desconocido";
    }
}

int es_valida(int i, int resto, int finitas) {
    if (denominaciones[i] > resto) return 0;
    if (finitas && cantidades[i] <= 0) return 0;
    return 1;
}

int seleccionVoraz(int resto, Caso caso, int finitas) {
    int mejor = -1;
    for (int i = 0; i < NUM_DEN; i++) {
        if (!es_valida(i, resto, finitas)) continue;

        if (mejor == -1) {
            mejor = i;
        } else {
            switch (caso) {
                case mayor:
                    if (denominaciones[i] > denominaciones[mejor]) mejor = i;
                    break;
                case menor:
                    if (denominaciones[i] < denominaciones[mejor]) mejor = i;
                    break;
                case mayorCantidad:
                    if (cantidades[i] > cantidades[mejor]) mejor = i;
                    break;
                case menorCantidad:
                    if (cantidades[i] < cantidades[mejor]) mejor = i;
                    break;
                case cercano:
                    if (abs(resto - denominaciones[i]) < abs(resto - denominaciones[mejor]))
                        mejor = i;
                    break;
            }
        }
    }
    return mejor;
}

void cambio(int monto, int *numMonedas, Caso caso, int finitas) {
    int suma = 0, totalMonedas = 0, iDen;

    for (int i = 0; i < NUM_DEN; i++) numMonedas[i] = 0;

    while (suma < monto) {
        iDen = seleccionVoraz(monto - suma, caso, finitas);
        if (iDen == -1) {
            printf("No se encontró solución. Cambio incompleto para estrategia: %s.\n\n", nombreCaso(caso));
            return;
        }

        numMonedas[iDen]++;
        totalMonedas++;
        suma += denominaciones[iDen];
        if (finitas) cantidades[iDen]--;
    }

    printf("Cambio para %d usando el caso: %s\n", monto, nombreCaso(caso));
    for (int i = 0; i < NUM_DEN; i++) {
        if (numMonedas[i] > 0) {
            printf("Monedas de $%d: %d\n", denominaciones[i], numMonedas[i]);
        }
    }
    printf("Total de monedas usadas: %d\n\n", totalMonedas);
}

int main() {
    int numMonedas[NUM_DEN];
    int montos[] = {79, 56, 94, 13};
    int numCasos = sizeof(montos) / sizeof(int);

    Caso estrategias[] = {
        menor,
        mayor,
        mayorCantidad,
        menorCantidad,
        cercano
    };
    int numEstrategias = sizeof(estrategias) / sizeof(Caso);
    int stockOriginal[] = {5, 9, 56, 94, 13};

    for (int m = 0; m < numCasos; m++) {
        int monto = montos[m];

        printf(" \n\n  CASO DE PRUEBA: Monto = %d\n", monto);

        printf("\n- MONEDAS INFINITAS -\n");
        for (int i = 0; i < numEstrategias; i++) {
            cambio(monto, numMonedas, estrategias[i], 0);
        }

        printf("\n- MONEDAS FINITAS -\n");
        for (int i = 0; i < numEstrategias; i++) {
            for (int j = 0; j < NUM_DEN; j++) cantidades[j] = stockOriginal[j];
            cambio(monto, numMonedas, estrategias[i], 1);
        }
    }

    return 0;
}
