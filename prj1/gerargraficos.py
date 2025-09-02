# Código para compilar o programa C e Plotar os gráficos

"""Grupo 11: 

Victor Kayky Zaneti Antunes NUSP : 15491132
Gustavo Fantato Fernandes NUSP : 16986132
Felipe Galvão Prazeres NUSP: 16828948

"""

import subprocess
import matplotlib.pyplot as plt
import os 

# Definições iniciais
ARQUIVO_C = "medicaotempo.c"
EXECUTAVEL = "medicaotempo.exe"
TAMANHOS_ENTRADA = [10, 100, 1000, 5000]
PASTA_GRAFICOS = "graficos"

#Dicionario com os nomes dos algoritmos para os gráficos.
nomes_algoritmos = {
    1: "Inversao de Vetor",
    2: "Busca Sequencial",
    3: "Busca Binaria Iterativa",
    4: "Busca Binaria Recursiva"
}

# Função que utiliza a biblioteca subprocess para compilar o codigo C
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

# Função que coleta a saída do nosso código C. Entrada formatada em c como: ./medicaotempo.exe opção_de_entrada tamanho_do_vetor   
def medir_tempo(id_algoritmo):
    tempos_medios = []
    print(f"\n--- Coletando dados para: {nomes_algoritmos[id_algoritmo]} ---")
    
    for tamanho in TAMANHOS_ENTRADA:
        comando = [f"./{EXECUTAVEL}", str(id_algoritmo), str(tamanho)]
        resultado = subprocess.run(comando, capture_output=True, text=True, check=True)
        output = resultado.stdout.strip()
        _, tempo_str = output.split(',')
        tempo = float(tempo_str)
        tempos_medios.append(tempo)
        print(f"  Tamanho: {tamanho:4d} -> Tempo médio: {tempo:.8f} s")
        
    return tempos_medios


# Plotar os gráficos e os guarda na pasta 'graficos' 

def plotar_grafico(id_algoritmo, tempos_medios):
    nome_algoritmo = nomes_algoritmos[id_algoritmo]
    
    nome_base_arquivo = f"grafico_{nome_algoritmo.lower().replace(' ', '_')}.png"
    caminho_arquivo = os.path.join(PASTA_GRAFICOS, nome_base_arquivo)


    plt.figure(figsize=(12, 6))
    plt.plot(TAMANHOS_ENTRADA, tempos_medios, marker='o', linestyle='-')
    plt.title(f'Tempo de Execução (Pior Caso) - {nome_algoritmo}')
    plt.xlabel('Tamanho da Entrada (N)')
    plt.ylabel('Tempo Médio de 100 Execuções (s)')
    plt.xticks(TAMANHOS_ENTRADA)
    plt.grid(True, which="both", ls="--")
    
    if id_algoritmo != 1:
        plt.yscale('log')

    plt.tight_layout()
    plt.savefig(caminho_arquivo)
    print(f"Gráfico salvo como '{caminho_arquivo}'")

def main():
    
    if not compilar_codigo_c():
        return
        
    os.makedirs(PASTA_GRAFICOS, exist_ok=True)

    for id_algoritmo in nomes_algoritmos.keys():
        tempos = medir_tempo(id_algoritmo)
        plotar_grafico(id_algoritmo, tempos)

if __name__ == "__main__":
    main()