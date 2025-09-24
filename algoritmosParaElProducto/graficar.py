import numpy as np
import matplotlib.pyplot as plt
from sklearn.preprocessing import PolynomialFeatures
from sklearn.linear_model import LinearRegression
from sklearn.metrics import r2_score


archivos = [
    "tiempos_codigo1.txt",
    "tiempos_codigo2.txt",
    "tiempos_codigo3.txt",
    "tiempos_codigo4.txt"
]

for archivo in archivos:
    print(f"Procesando {archivo}...")
    
    datos = np.loadtxt(archivo)
    n = datos[:, 0]
    tiempos = datos[:, 1] * 1000


    valores_unicos = np.unique(n)
    promedios = []
    desviaciones = []

    for valor in valores_unicos:
        tiempos_mismo_n = tiempos[n == valor]
        promedios.append(np.mean(tiempos_mismo_n))
        desviaciones.append(np.std(tiempos_mismo_n))

    promedios = np.array(promedios)
    desviaciones = np.array(desviaciones)


    X = valores_unicos.reshape(-1, 1)
    y = promedios
    poly = PolynomialFeatures(degree=2)
    X_poly = poly.fit_transform(X)
    modelo = LinearRegression().fit(X_poly, y)
    y_pred = modelo.predict(X_poly)


    a, b, c = modelo.coef_[2], modelo.coef_[1], modelo.intercept_
    r2 = r2_score(y, y_pred)

    plt.figure(figsize=(10, 6))
    plt.errorbar(valores_unicos, promedios, yerr=desviaciones, fmt='o', label='Datos promedio ± desviación')
    plt.plot(valores_unicos, y_pred, 'r-', label='Ajuste polinomial')


    eq = f"$T(n) = {a:.3e}n^2 + {b:.3e}n + {c:.3e}$\n$R^2 = {r2:.4f}$"
    plt.text(0.05, 0.95, eq, transform=plt.gca().transAxes,
             fontsize=12, verticalalignment='top',
             bbox=dict(facecolor='white', alpha=0.8))

    plt.title(f'Tiempos de ejecución - {archivo}')
    plt.xlabel('Tamaño de entrada (n)')
    plt.ylabel('Tiempo (milisegundos)')
    plt.legend()
    plt.grid(True)
    plt.tight_layout()


    nombre_salida = archivo.replace(".txt", ".png")
    plt.savefig(nombre_salida)
    plt.close()
