import numpy as np
import matplotlib.pyplot as plt
from sklearn.metrics import r2_score
from scipy.stats import pearsonr

def graf_tnk(nombre_archivo, titulo):
    datos = np.loadtxt(nombre_archivo, comments='#')
    n_vals = np.unique(datos[:, 0])

    for n in n_vals:
        subconjunto = datos[datos[:, 0] == n]
        k = subconjunto[:, 1]
        tiempo = subconjunto[:, 2]

        coef = np.polyfit(k, tiempo, deg=1)
        polinomio = np.poly1d(coef)
        ajuste = polinomio(k)
        r2 = r2_score(tiempo, ajuste)
        r, _ = pearsonr(k, tiempo)

        plt.figure(figsize=(8, 5))
        plt.scatter(k, tiempo, label='Tiempos medidos')
        plt.plot(k, ajuste, 'r--', label=f'Ajuste lineal: R² = {r2:.4f}, r = {r:.4f}')
        plt.title(f"{titulo} (n = {int(n)})")
        plt.xlabel('k')
        plt.ylabel('Tiempo (s)')
        plt.legend()
        plt.grid(True)
        plt.tight_layout()
        plt.savefig(f"bubble_n{int(n)}.png")
        plt.show()

def grag_insertion(nombre_archivo, titulo_base):
    datos = np.loadtxt(nombre_archivo, comments='#')
    n_vals = np.unique(datos[:, 0])

    for n in n_vals:
        subconjunto = datos[datos[:, 0] == n]
        k = subconjunto[:, 1]
        tiempo = subconjunto[:, 2]

        coef = np.polyfit(k, tiempo, deg=2)
        pol = np.poly1d(coef)
        ajuste = pol(k)
        r2 = r2_score(tiempo, ajuste)

        plt.figure(figsize=(8, 5))
        plt.scatter(k, tiempo, label='Tiempos medidos')
        plt.plot(k, ajuste, 'k--', label=f'Ajuste cuadrático: R² = {r2:.4f}')
        plt.title(f"{titulo_base} (n = {int(n)})")
        plt.xlabel('k')
        plt.ylabel('Tiempo (s)')
        plt.legend()
        plt.grid(True)
        plt.tight_layout()
        plt.savefig(f"insertion_n{int(n)}.png")
        plt.show()

def graf_selectionCasos(nombre_archivo):
    datos = np.loadtxt(nombre_archivo)
    n = datos[:, 0]
    mejor = datos[:, 1]
    peor = datos[:, 2]

    # Mejor caso
    coef_mejor = np.polyfit(n, mejor, deg=2)
    pol_mejor = np.poly1d(coef_mejor)
    ajuste_mejor = pol_mejor(n)
    r2_mejor = r2_score(mejor, ajuste_mejor)

    plt.figure(figsize=(8, 5))
    plt.scatter(n, mejor, label='Mejor caso')
    plt.plot(n, ajuste_mejor, 'k--', label=f'Ajuste cuadrático: R² = {r2_mejor:.4f}')
    plt.title('Selection Sort - Mejor caso (con ajuste cuadrático)')
    plt.xlabel('n (tamaño del arreglo)')
    plt.ylabel('Tiempo (s)')
    plt.legend()
    plt.grid(True)
    plt.tight_layout()
    plt.savefig("selection_mejor.png")
    plt.show()

    # Peor caso
    coef_peor = np.polyfit(n, peor, deg=2)
    pol_peor = np.poly1d(coef_peor)
    ajuste_peor = pol_peor(n)
    r2_peor = r2_score(peor, ajuste_peor)

    plt.figure(figsize=(8, 5))
    plt.scatter(n, peor, label='Peor caso')
    plt.plot(n, ajuste_peor, 'k--', label=f'Ajuste cuadrático: R² = {r2_peor:.4f}')
    plt.title('Selection Sort - Peor caso (con ajuste cuadrático)')
    plt.xlabel('n (tamaño del arreglo)')
    plt.ylabel('Tiempo (s)')
    plt.legend()
    plt.grid(True)
    plt.tight_layout()
    plt.savefig("selection_peor.png")
    plt.show()

# Ejecutar gráficas
graf_tnk('bubble_tnk.txt', 'T(n,k) - Bubble Sort con ajuste (n fija)')
grag_insertion('insertion_tnk.txt', 'T(n,k) - Insertion Sort con ajuste (n fija)')
graf_selectionCasos('selection_mejor_peor.txt')