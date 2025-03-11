import pandas as pd
import matplotlib.pyplot as plt
import os

# Verificar diretório atual (opcional, para debug)
print("Diretório atual:", os.getcwd())
print("Arquivos na pasta:", os.listdir())

# Lê o CSV correto
df = pd.read_csv('radix.csv', sep=';')

# Extrair otimizador, tipo e tamanho
df[['otimizador', 'tipo', 'tamanho']] = df['ficheiro'].str.extract(r'^(o\d+)_(\w+)_(\d+)')

# Garantir que tamanho é número para ordenar corretamente
df['tamanho'] = df['tamanho'].astype(int)

# Ordenar por tipo, tamanho e otimizador
df = df.sort_values(by=['tipo', 'tamanho', 'otimizador'])

# Criar coluna combinada (tipo + tamanho + otimizador)
df['combinado'] = df['otimizador'] + '_' + df['tipo'] + '_' + df['tamanho'].astype(str)

# ✅ Exibir dados (opcional, para conferência)
print(df[['combinado', 'energia', 'tempo']])

# ------------------- GRÁFICO DE TEMPO -------------------

plt.figure(figsize=(14, 6))
plt.bar(df['combinado'], df['tempo'], color='coral')
plt.xlabel('Tipo + Tamanho + Otimizador (Ordenado)')
plt.ylabel('Tempo (ms ou s)')
plt.title('Tempo por Tipo, Tamanho e Otimizador (Ordenado)')
plt.xticks(rotation=90)
plt.tight_layout()
plt.show()

# ------------------- GRÁFICO DE ENERGIA -------------------

plt.figure(figsize=(14, 6))
plt.bar(df['combinado'], df['energia'], color='seagreen')
plt.xlabel('Tipo + Tamanho + Otimizador (Ordenado)')
plt.ylabel('Energia (J ou unidade usada)')
plt.title('Energia por Tipo, Tamanho e Otimizador (Ordenado)')
plt.xticks(rotation=90)
plt.tight_layout()
plt.show()
