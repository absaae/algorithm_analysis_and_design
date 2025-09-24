import matplotlib.pyplot as plt
import numpy as np

n = []
tiempos = []

with open("tiempos_busqueda.txt", "r") as archivo:
    for linea in archivo:
        if linea.strip() == "":
            continue
        partes = linea.strip().split()
        n.append(int(partes[0]))
        tiempos.append(float(partes[1]) * 1e9)  #nanosegundos

n = np.array(n)
tiempos = np.array(tiempos)
log_n = np.log(n)

coef = np.polyfit(log_n, tiempos, deg=1)
ajuste = np.poly1d(coef)
r_matrix = np.corrcoef(tiempos, ajuste(log_n))
r2 = r_matrix[0, 1] ** 2

plt.figure(figsize=(10, 6))
plt.plot(n, tiempos, 'o', label="tiempo medido", color="blue")
plt.plot(n, ajuste(log_n), '--', color='red',
         label=f"T(n) = {coef[0]:.2e}·ln(n) + {coef[1]:.2e}\n$R^2 = {r2:.4f}$")

plt.title("Tiempos promedio de búsqueda binaria recursiva", fontsize=14)
plt.xlabel("Tamaño del arreglo (n)", fontsize=12)
plt.ylabel("Tiempo (nanoesegundos)", fontsize=12)
plt.grid(True)
plt.legend()
plt.tight_layout()
plt.savefig("grafica_binaria_logaritmica.png")
plt.show()