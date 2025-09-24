/*
 * Autor: Max Uriel Sanchez Diaz - 2213026327
 * Fecha: 04-08-2025
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_MAX_DENOMINACIONES 20
#define CANTIDAD_ILIMITADA 100000

typedef struct {
    int valor_moneda;
    int disponibles;
} DenominacionMoneda;

typedef struct {
    int uso_por_tipo[NUM_MAX_DENOMINACIONES];
    int monedas_total;
    int resuelto;
} SolucionVoraz;

int modo_seleccion;

// Encontrar todas las denominaciones que se pueden usar
int buscar_opciones_viables(DenominacionMoneda *monedas, int total_tipos, int cantidad_objetivo, int *opciones) {
    int contador_opciones = 0;
    
    for (int idx = 0; idx < total_tipos; idx++) {
        if (monedas[idx].disponibles > 0 && monedas[idx].valor_moneda <= cantidad_objetivo) {
            opciones[contador_opciones] = idx;
            contador_opciones++;
        }
    }
    
    return contador_opciones;
}

// Elegir la mejor opcion segun el modo de seleccion
int elegir_mejor_opcion(DenominacionMoneda *monedas, int *opciones_disponibles, int num_opciones, int objetivo_actual) {
    if (num_opciones == 0) return -1;
    
    int opcion_elegida = opciones_disponibles[0];
    
    for (int i = 1; i < num_opciones; i++) {
        int opcion_actual = opciones_disponibles[i];
        
        if (modo_seleccion == 1) { // Menor denominacion
            if (monedas[opcion_actual].valor_moneda < monedas[opcion_elegida].valor_moneda) {
                opcion_elegida = opcion_actual;
            }
        }
        else if (modo_seleccion == 2) { // Mayor denominacion
            if (monedas[opcion_actual].valor_moneda > monedas[opcion_elegida].valor_moneda) {
                opcion_elegida = opcion_actual;
            }
        }
        else if (modo_seleccion == 3) { // Mas cantidad disponible
            if (monedas[opcion_actual].disponibles > monedas[opcion_elegida].disponibles) {
                opcion_elegida = opcion_actual;
            }
        }
        else if (modo_seleccion == 4) { // Menos cantidad disponible
            if (monedas[opcion_actual].disponibles < monedas[opcion_elegida].disponibles) {
                opcion_elegida = opcion_actual;
            }
        }
        else if (modo_seleccion == 5) { // Mas cercana al objetivo
            int diferencia_actual = objetivo_actual - monedas[opcion_actual].valor_moneda;
            int diferencia_elegida = objetivo_actual - monedas[opcion_elegida].valor_moneda;
            if (diferencia_actual >= 0 && (diferencia_elegida < 0 || diferencia_actual < diferencia_elegida)) {
                opcion_elegida = opcion_actual;
            }
        }
    }
    
    return opcion_elegida;
}

// Verificar si la opcion es valida
int opcion_valida(DenominacionMoneda *monedas, int opcion, int cantidad_restante) {
    if (opcion < 0) return 0;
    if (monedas[opcion].disponibles <= 0) return 0;
    if (monedas[opcion].valor_moneda > cantidad_restante) return 0;
    return 1;
}

// Verificar si ya se resolvio el problema
int problema_resuelto(int restante) {
    return restante == 0;
}

// Resolver usando algoritmo voraz
SolucionVoraz resolver_cambio_voraz(DenominacionMoneda *sistema_monedas, int tipos_moneda, int monto_cambio, int tipo_seleccion, int ilimitadas) {
    SolucionVoraz resultado;
    
    for (int i = 0; i < NUM_MAX_DENOMINACIONES; i++) {
        resultado.uso_por_tipo[i] = 0;
    }
    resultado.monedas_total = 0;
    resultado.resuelto = 0;
    
    modo_seleccion = tipo_seleccion;
    
    DenominacionMoneda monedas_trabajo[NUM_MAX_DENOMINACIONES];
    for (int i = 0; i < tipos_moneda; i++) {
        monedas_trabajo[i].valor_moneda = sistema_monedas[i].valor_moneda;
        monedas_trabajo[i].disponibles = ilimitadas ? CANTIDAD_ILIMITADA : sistema_monedas[i].disponibles;
    }
    
    int pendiente = monto_cambio;
    
    while (pendiente > 0) {
        int opciones_validas[NUM_MAX_DENOMINACIONES];
        int total_opciones = buscar_opciones_viables(monedas_trabajo, tipos_moneda, pendiente, opciones_validas);
        
        if (total_opciones == 0) break;
        
        int moneda_seleccionada = elegir_mejor_opcion(monedas_trabajo, opciones_validas, total_opciones, pendiente);
        
        if (!opcion_valida(monedas_trabajo, moneda_seleccionada, pendiente)) break;
        
        resultado.uso_por_tipo[moneda_seleccionada]++;
        resultado.monedas_total++;
        pendiente -= monedas_trabajo[moneda_seleccionada].valor_moneda;
        monedas_trabajo[moneda_seleccionada].disponibles--;
    }
    
    if (problema_resuelto(pendiente)) {
        resultado.resuelto = 1;
    }
    
    return resultado;
}

void mostrar_configuracion(DenominacionMoneda *monedas, int cantidad_tipos) {
    printf("Configuracion de monedas:\n");
    for (int i = 0; i < cantidad_tipos; i++) {
        printf("  Valor $%d: %d unidades\n", monedas[i].valor_moneda, monedas[i].disponibles);
    }
    printf("\n");
}

void mostrar_resultado_final(SolucionVoraz *solucion, DenominacionMoneda *monedas, int cantidad_tipos, int monto_objetivo, char *descripcion_metodo, int caso_infinito) {
    printf("Metodo: %s\n", descripcion_metodo);
    printf("Monto objetivo: $%d | Caso: %s\n", monto_objetivo, caso_infinito ? "Infinitas" : "Finitas");
    
    if (solucion->resuelto) {
        printf("Solucion encontrada - Total monedas: %d\n", solucion->monedas_total);
        for (int i = 0; i < cantidad_tipos; i++) {
            if (solucion->uso_por_tipo[i] > 0) {
                int subtotal = monedas[i].valor_moneda * solucion->uso_por_tipo[i];
                printf("  $%d x %d = $%d\n", monedas[i].valor_moneda, solucion->uso_por_tipo[i], subtotal);
            }
        }
    } else {
        printf("No se pudo encontrar solucion\n");
    }
    printf("\n");
}

void probar_todos_metodos(DenominacionMoneda *monedas, int tipos, int objetivo) {
    printf("Pruebas para objetivo: $%d\n", objetivo);
    printf("=========================\n");
    
    char *nombres_metodos[] = {
        "Menor valor",
        "Mayor valor", 
        "Mayor stock",
        "Menor stock",
        "Optima cercania"
    };
    
    printf("Caso con monedas infinitas:\n");
    for (int metodo = 1; metodo <= 5; metodo++) {
        SolucionVoraz sol = resolver_cambio_voraz(monedas, tipos, objetivo, metodo, 1);
        mostrar_resultado_final(&sol, monedas, tipos, objetivo, nombres_metodos[metodo-1], 1);
    }
    
    printf("Caso con monedas finitas:\n");
    for (int metodo = 1; metodo <= 5; metodo++) {
        SolucionVoraz sol = resolver_cambio_voraz(monedas, tipos, objetivo, metodo, 0);
        mostrar_resultado_final(&sol, monedas, tipos, objetivo, nombres_metodos[metodo-1], 0);
    }
}

int main() {
    printf("IMPLEMENTACION ALGORITMO VORAZ\n");
    printf("Problema: Cambio de monedas\n");
    printf("==============================\n\n");
    
    printf("Componentes del algoritmo voraz implementados:\n");
    printf("a) Conjunto candidatos: Denominaciones disponibles\n");
    printf("b) Funcion seleccion: 5 estrategias diferentes\n");
    printf("c) Funcion factibilidad: Validacion de restricciones\n");
    printf("d) Funcion objetivo: Minimizar total de monedas\n");
    printf("e) Condicion solucion: Cambio exacto alcanzado\n\n");
    
    DenominacionMoneda conjunto_monedas[5];
    int denominaciones[] = {20, 10, 5, 2, 1};
    int stocks[] = {4, 6, 3, 8, 12};
    
    for (int pos = 0; pos < 5; pos++) {
        conjunto_monedas[pos].valor_moneda = denominaciones[pos];
        conjunto_monedas[pos].disponibles = stocks[pos];
    }
    
    mostrar_configuracion(conjunto_monedas, 5);
    
    int casos_prueba[] = {37, 43, 28};
    
    for (int caso = 0; caso < 3; caso++) {
        probar_todos_metodos(conjunto_monedas, 5, casos_prueba[caso]);
    }
    
    printf("Caracteristicas del algoritmo:\n");
    printf("- Complejidad: O(m * n) donde m=monto, n=tipos\n");
    printf("- Espacio: O(n) para almacenar solucion\n");
    return 0;
}