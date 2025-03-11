import csv
import matplotlib.pyplot as plt
import numpy as np

# Função para ler o CSV e organizar os dados
def ler_dados_csv(nome_arquivo):
    dados = {}
    with open(nome_arquivo, newline='') as csvfile:
        leitor = csv.DictReader(csvfile, delimiter=';')
        for row in leitor:
            chave = row['ficheiro'].replace('.csv', '')
            energia = float(row['energia'])
            tempo = float(row['tempo'])
            dados[chave] = {'energia': energia, 'tempo': tempo}
    return dados

# Função para extrair o sufixo (ex: "45" de "o2_fibR_45")
def extrair_sufixo(nome):
    return nome.split('_')[-1]

# Função principal para cálculo e separação dos dados por N
def calcular_metricas_e_graficos(dados):
    # Descobrir sufixos presentes
    sufixos = set(extrair_sufixo(k) for k in dados.keys())

    # Para cada sufixo (N)
    for suf in sorted(sufixos):
        base_key = f"o0_fibR_{suf}"
        if base_key not in dados:
            print(f"Base '{base_key}' não encontrada, pulando sufixo '{suf}'")
            continue

        energia_base = dados[base_key]['energia']
        tempo_base = dados[base_key]['tempo']

        pontos = []  # Lista de (Speedup, Greenup, Label) para esse N

        print(f"\n==== Resultados para N = {suf} ====")
        print(f"{'Versão':<15} {'Base':<15} {'Speedup':<10} {'Greenup':<10} {'Powerup':<10}")
        print('-' * 60)

        # Comparar com as versões
        for prefixo in ['o2_fibR', 'o0_fibI', 'o2_fibI']:
            chave = f"{prefixo}_{suf}"
            if chave not in dados:
                print(f"Versão '{chave}' não encontrada, pulando.")
                continue

            energia_otim = dados[chave]['energia']
            tempo_otim = dados[chave]['tempo']

            # Cálculos
            speedup = tempo_base / tempo_otim
            greenup = energia_base / energia_otim
            powerup = speedup / greenup  # Mantido para print, mas o gráfico será Greenup vs Speedup

            pontos.append((speedup, greenup, chave))

            # Exibição
            print(f"{chave:<15} {base_key:<15} {speedup:<10.2f} {greenup:<10.2f} {powerup:<10.2f}")

        # Plotar o gráfico específico deste N
        plotar_grafico(pontos, suf)

# Função para plotar o gráfico de um N específico
def plotar_grafico(pontos, sufixo):
    fig, ax = plt.subplots(figsize=(8, 6))

    # Obter limites automáticos baseados nos dados com margem
    speedups = [p[0] for p in pontos]
    greenups = [p[1] for p in pontos]

    min_speedup = max(min(speedups) * 0.5, 0.1)
    max_speedup = max(speedups) * 2
    min_greenup = max(min(greenups) * 0.5, 0.1)
    max_greenup = max(greenups) * 2

    # Definir limites diretamente sem log scale
    ax.set_xlim(min_greenup, max_greenup)
    ax.set_ylim(min_speedup, max_speedup)

    # Linhas principais de referência
    ax.plot([min_greenup, max_greenup], [min_greenup, max_greenup], color='blue', linestyle='-.', label='Speedup = Greenup')

    ax.axhline(1, color='green', linewidth=2, linestyle='--', label='Greenup = 1')
    ax.axvline(1, color='red', linewidth=2, linestyle='--', label='Speedup = 1')

    # Plotar os pontos
    for speedup, greenup, label in pontos:
        ax.scatter(greenup, speedup, s=100, edgecolors='black', facecolors='orange', zorder=5)
        ax.text(greenup * 1.1, speedup * 1.1, label, fontsize=10, weight='bold', ha='center')

    # Labels e título
    ax.set_xlabel('Greenup', fontsize=12)
    ax.set_ylabel('Speedup', fontsize=12)
    ax.set_title(f'Greenup vs Speedup (N = {sufixo})', fontsize=14)

    # Legenda
    ax.legend()

    # Grid e layout
    plt.grid(True, linestyle='--', alpha=0.7)
    plt.tight_layout()

    # Mostrar gráfico
    plt.show()

    # Para salvar como imagem, descomentar:
    # plt.savefig(f"grafico_N{sufixo}_greenup_speedup.png", dpi=300)
    # print(f"Gráfico salvo como grafico_N{sufixo}_greenup_speedup.png")

# ---------- Execução principal ----------
if __name__ == "__main__":
    nome_arquivo = "media.csv"  # Nome do arquivo com os dados
    dados = ler_dados_csv(nome_arquivo)
    calcular_metricas_e_graficos(dados)
