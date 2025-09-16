import subprocess
import matplotlib.pyplot as plt
import os
import unicodedata
import re

# --- CONFIGURAÇÕES ---
ARQUIVO_C = "medicaotempo.c"
EXECUTAVEL = "medicaotempo.exe"
TAMANHOS_ENTRADA = [10, 100, 1000, 5000]
PASTA_GRAFICOS = "graficos"

nomes_algoritmos = {
    1: "Inversão de Vetor",
    2: "Busca Sequencial",
    3: "Busca Binária Iterativa",
    4: "Busca Binária Recursiva"
}

# Dicionários para armazenar todos os dados
dados = {
    'tempo': {},
    'comparacoes': {},
    'atribuicoes': {}
}

def sanitizar_nome_arquivo(nome):
    nfkd_form = unicodedata.normalize('NFKD', nome)
    nome_sem_acentos = "".join([c for c in nfkd_form if not unicodedata.combining(c)])
    nome_seguro = re.sub(r'[^\w\s-]', '', nome_sem_acentos).strip()
    return nome_seguro

def compilar_codigo_c():
    print(f"Compilando '{ARQUIVO_C}'...")
    try:
        subprocess.run(
            ["gcc", ARQUIVO_C, "-o", EXECUTAVEL],
            check=True, capture_output=True, text=True
        )
        print("Compilação bem-sucedida!")
        return True
    except (FileNotFoundError, subprocess.CalledProcessError) as e:
        print(f"Erro na compilação: {e}")
        if hasattr(e, 'stderr'): print(e.stderr)
        return False

def coletar_dados():
    """Chama o executável C para cada algoritmo e tamanho, e coleta os dados."""
    for id_alg, nome_alg in nomes_algoritmos.items():
        print(f"\n--- Coletando dados para: {nome_alg} ---")
        
        lista_tempos = []
        lista_comparacoes = []
        lista_atribuicoes = []

        for tamanho in TAMANHOS_ENTRADA:
            comando = [f"./{EXECUTAVEL}", str(id_alg), str(tamanho)]
            resultado = subprocess.run(comando, capture_output=True, text=True, check=True)
            
            # Lê a saída de 4 valores
            output = resultado.stdout.strip()

            print(f"    DEBUG: Recebido do C -> '{output}'")
            
            _, tempo_str, comp_str, atrib_str = output.split(',')
            
            lista_tempos.append(float(tempo_str))
            lista_comparacoes.append(int(comp_str))
            lista_atribuicoes.append(int(atrib_str))

            print(f"  Tamanho: {tamanho:4d} -> Tempo: {float(tempo_str):.8f}s | Comp: {int(comp_str)} | Atrib: {int(atrib_str)}")
        
        dados['tempo'][nome_alg] = lista_tempos
        dados['comparacoes'][nome_alg] = lista_comparacoes
        dados['atribuicoes'][nome_alg] = lista_atribuicoes

def plotar_graficos_tempo():
    """Plota um gráfico separado para o tempo de cada algoritmo."""
    print("\n--- Gerando gráficos de TEMPO ---")
    for nome_alg, tempos in dados['tempo'].items():
        nome_arquivo_sanitizado = sanitizar_nome_arquivo(nome_alg)
        nome_base_arquivo = f"grafico_tempo_{nome_arquivo_sanitizado.lower().replace(' ', '_')}.png"
        caminho_arquivo = os.path.join(PASTA_GRAFICOS, nome_base_arquivo)

        plt.figure(figsize=(10, 6))
        plt.plot(TAMANHOS_ENTRADA, tempos, marker='o', linestyle='-')
        plt.title(f'Tempo de Execução (Pior Caso) - {nome_alg}')
        plt.xlabel('Tamanho da Entrada (N)')
        plt.ylabel('Tempo Médio (s)')
        plt.xticks(TAMANHOS_ENTRADA)
        plt.grid(True, which="both", ls="--")
        plt.yscale('log')
        plt.tight_layout()
        plt.savefig(caminho_arquivo)
        print(f"Gráfico salvo como '{caminho_arquivo}'")

def plotar_grafico_comparativo(metrica, titulo_y):
    """Plota um gráfico comparando todos os algoritmos para uma métrica."""
    print(f"\n--- Gerando gráfico de COMPARAÇÃO - {metrica.upper()} ---")
    
    nome_base_arquivo = f"grafico_comparativo_{metrica}.png"
    caminho_arquivo = os.path.join(PASTA_GRAFICOS, nome_base_arquivo)

    plt.figure(figsize=(12, 7))
    
    # --- LÓGICA DE PLOTAGEM FINAL (COM MARCADORES DIFERENTES) ---
    for nome_alg, valores in dados[metrica].items():
        
        if nome_alg == "Busca Binária Iterativa":
            # Linha PONTILHADA (:) com marcador 'X'
            plt.plot(TAMANHOS_ENTRADA, valores, marker='X', markersize=8, linestyle=':', label=f"{nome_alg} (O(log n))")
            
        elif nome_alg == "Busca Binária Recursiva":
            # Linha TRACEJADA (--) com marcador 'o' (círculo)
            plt.plot(TAMANHOS_ENTRADA, valores, marker='o', linestyle='--', label=f"{nome_alg} (O(log n))")
            
        else:
            # Linha SÓLIDA (-) para os algoritmos O(n)
            plt.plot(TAMANHOS_ENTRADA, valores, marker='s', linestyle='-', label=f"{nome_alg} (O(n))")
    # -----------------------------------------------

    plt.title(f'Comparação de {titulo_y} (Pior Caso)')
    plt.xlabel('Tamanho da Entrada (N)')
    plt.ylabel(f'Média de {titulo_y}')
    plt.xticks(TAMANHOS_ENTRADA)
    plt.grid(True, which="both", ls="--")
    plt.legend()
    plt.yscale('log')
    plt.xscale('log')
    plt.tight_layout()
    plt.savefig(caminho_arquivo)
    print(f"Gráfico salvo como '{caminho_arquivo}'")
def main():
    if not compilar_codigo_c():
        return
        
    os.makedirs(PASTA_GRAFICOS, exist_ok=True)
    
    coletar_dados()
    plotar_graficos_tempo()
    
    plotar_grafico_comparativo('comparacoes', 'Operações de Comparação')
    plotar_grafico_comparativo('atribuicoes', 'Operações de Atribuição')

if __name__ == "__main__":
    main()