import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import re

archivo = "tiempos_busqueda.txt"
with open(archivo, "r") as file:
    lineas = file.readlines()

datos = []
for linea in lineas:
    match = re.match(r"N=(\d+)\s+Mejor=([\d.]+)\s+Peor=([\d.]+)\s+Prom=([\d.]+)", linea)
    if match:
        N, mejor, peor, prom = match.groups()
        datos.append({
            "N": int(N),
            "Mejor": float(mejor),
            "Peor": float(peor),
            "Promedio": float(prom)
        })

df = pd.DataFrame(datos)

grado = 2
N = df["N"].to_numpy()

coef_mejor = np.polyfit(N, df["Mejor"], grado)
coef_peor = np.polyfit(N, df["Peor"], grado)
coef_prom = np.polyfit(N, df["Promedio"], grado)

p_mejor = np.poly1d(coef_mejor)
p_peor = np.poly1d(coef_peor)
p_prom = np.poly1d(coef_prom)

def formatear_ecuacion(p):
    return f"{p[0]:.2e}·n² + {p[1]:.2e}·n + {p[2]:.2e}"

# Etiquetas con ecuaciones para la leyenda
label_mejor = "Mejor caso:\n" + formatear_ecuacion(coef_mejor)
label_peor = "Peor caso:\n" + formatear_ecuacion(coef_peor)
label_prom = "Promedio:\n" + formatear_ecuacion(coef_prom)

plt.figure(figsize=(12, 7))
plt.plot(N, p_mejor(N), 'o-', label=label_mejor)
plt.plot(N, p_peor(N), 'o-', label=label_peor)
plt.plot(N, p_prom(N), 'o-', label=label_prom)

plt.xticks(N)
plt.xlabel("Tamaño de la matriz (N x N)")
plt.ylabel("Tiempo (segundos)")
plt.title("Tiempos de búsqueda en matriz cuadrada")
plt.legend(loc='upper left', fontsize=9)
plt.grid(True)
plt.tight_layout()

plt.savefig("grafica_tiempos_busqueda.png")
df.to_excel("tiempos_busqueda.xlsx", index=False)

plt.show()
