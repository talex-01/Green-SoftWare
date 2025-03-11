import matplotlib.pyplot as plt
import pandas as pd

# Dados fornecidos
data = [
    ("o0_fibI_45.csv", 0.02, 5.00),
    ("o0_fibI_47.csv", 0.02, 3.90),
    ("o0_fibI_49.csv", 0.02, 5.40),
    ("o0_fibR_45.csv", 97.24, 8440.80),
    ("o0_fibR_47.csv", 239.55, 22348.50),
    ("o0_fibR_49.csv", 597.02, 60410.50),
    ("o2_fibI_45.csv", 0.02, 7.20),
    ("o2_fibI_47.csv", 0.02, 3.80),
    ("o2_fibI_49.csv", 0.02, 4.60),
    ("o2_fibR_45.csv", 32.69, 2844.20),
    ("o2_fibR_47.csv", 85.20, 7147.50),
    ("o2_fibR_49.csv", 203.24, 19208.60)
]

# Criar um DataFrame
df = pd.DataFrame(data, columns=['ficheiro', 'energia', 'tempo'])

# Extrair o número (X) e a combinação das duas primeiras partes do nome
df['flag_fib'] = df['ficheiro'].apply(lambda x: '_'.join(x.split('_')[:2]))  # flag_fib
df['X'] = df['ficheiro'].apply(lambda x: int(x.split('_')[2].split('.')[0]))  # Número X

# Criar os gráficos

# Gráfico de tempo de execução
plt.figure(figsize=(10, 5))
for flag_fib in df['flag_fib'].unique():
    subset = df[df['flag_fib'] == flag_fib]
    plt.plot(subset['X'], subset['tempo'], label=flag_fib)
plt.xlabel('Número (X)')
plt.ylabel('Tempo de Execução (s)')
plt.title('Tempo de Execução por Função')
plt.legend(title='Função')
plt.grid(True)
plt.show()

# Gráfico de energia consumida
plt.figure(figsize=(10, 5))
for flag_fib in df['flag_fib'].unique():
    subset = df[df['flag_fib'] == flag_fib]
    plt.plot(subset['X'], subset['energia'], label=flag_fib)
plt.xlabel('Número (X)')
plt.ylabel('Energia Consumida (J)')
plt.title('Energia Consumida por Função')
plt.legend(title='Função')
plt.grid(True)
plt.show()
