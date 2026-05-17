import matplotlib.pyplot as plt
import numpy as np

# --- DANE WEJŚCIOWE (Twoje wyniki) ---
expected_value = 2.0

# Wyniki dla float
float_results = {
    'Heapsort': 2.0090389252,
    'Naturalne': 1.9536743164,
    'Kahan': 2.0000000000
}

# Wyniki dla double
double_results = {
    'Heapsort': 2.0000000000,
    'Naturalne': 1.9999999999,
    'Kahan': 2.0000000000
}

# Wyniki dla long double
long_double_results = {
    'Heapsort': 2.0000000000,
    'Naturalne': 2.0000000000,
    'Kahan': 2.0000000000
}

# --- OBLICZENIA (Błąd względny w procentach) ---
def calculate_relative_error(measured, expected):
    return abs(measured - expected) / expected * 100

algorithms = ['Heapsort', 'Naturalne', 'Kahan']

float_errors = [calculate_relative_error(float_results[alg], expected_value) for alg in algorithms]
double_errors = [calculate_relative_error(double_results[alg], expected_value) for alg in algorithms]
long_double_errors = [calculate_relative_error(long_double_results[alg], expected_value) for alg in algorithms]

# --- KONFIGURACJA WYKRESU ---
x = np.arange(len(algorithms))  # lokalizacje etykiet
width = 0.25  # szerokość słupków

fig, ax = plt.subplots(figsize=(12, 7))

# Rysowanie słupków dla każdej precyzji
rects1 = ax.bar(x - width, float_errors, width, label='float (32-bit)', color='#e74c3c', edgecolor='black', alpha=0.8)
rects2 = ax.bar(x, double_errors, width, label='double (64-bit)', color='#3498db', edgecolor='black', alpha=0.8)
rects3 = ax.bar(x + width, long_double_errors, width, label='long double (80/128-bit)', color='#2ecc71', edgecolor='black', alpha=0.8)

# --- STYLIZACJA ---
ax.set_ylabel('Błąd względny [%]', fontsize=14, fontweight='bold')
ax.set_title('Porównanie precyzji algorytmów sumowania\n(Wartość oczekiwana = 2.0)', fontsize=16, fontweight='bold', pad=20)
ax.set_xticks(x)
ax.set_xticklabels(algorithms, fontsize=13)
ax.legend(fontsize=12, title='Typ danych', title_fontsize=13)

# Ustawienie skali logarytmicznej, aby zobaczyć małe błędy double/long double
ax.set_yscale('log')
ax.grid(True, which="both", ls="--", alpha=0.5)

# Dodanie etykiet z wartościami nad słupkami (tylko dla float, bo reszta jest bliska zeru)
def autolabel(rects):
    for rect in rects:
        height = rect.get_height()
        if height > 1e-6: # Pokaż etykietę tylko jeśli błąd jest zauważalny
            ax.annotate(f'{height:.2f}%',
                        xy=(rect.get_x() + rect.get_width() / 2, height),
                        xytext=(0, 3),  # przesunięcie pionowe
                        textcoords="offset points",
                        ha='center', va='bottom', fontsize=10, fontweight='bold')

autolabel(rects1)

# Dodanie opisu osi X
ax.set_xlabel('Algorytm sumowania', fontsize=14, fontweight='bold', labelpad=15)

# --- WYŚWIETLENIE/ZAPIS ---
plt.tight_layout()
plt.show() # Użyj plt.savefig('wykres.png') aby zapisać do pliku