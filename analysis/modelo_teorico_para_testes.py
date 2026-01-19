import time

import random

import math

import csv # Biblioteca para criar o arquivo Excel/CSV direto



# --- CONFIGURAÇÃO ---

QTD_AMOSTRAS = 50  # Quantas linhas você quer no relatório?

NOME_ARQUIVO = "dados_relatorio.csv"



# Estado do "Sensor"

class EnsaioDispersao:

    def __init__(self):

        self.timestamp = 0

        self.pressao_pico_bar = 0.0

        self.temp_max_c = 0.0

        self.massa_nanomaterial_mg = 0.0

        self.massa_agua_seca_mg = 500.0 # Controle

        self.area_dispersao_cm2 = 0.0

        self.eficiencia_atingida = False



dados = EnsaioDispersao()



def simular_sensores(massa_nano):

    # Simula o tempo atual

    dados.timestamp = int(time.time() * 1000)

    dados.massa_nanomaterial_mg = massa_nano

    

    # Simulação Pressão (10 bar base + variação pela massa + ruído)

    dados.pressao_pico_bar = 10.0 + (massa_nano / 1000.0) + random.uniform(-0.5, 0.5)

    

    # Simulação Temperatura

    dados.temp_max_c = random.uniform(28.0, 32.5)

    

    # MODELO MATEMÁTICO (Mesmo do Firmware)

    # Area = 250 * log10(massa) - 300

    area_teorica = (250.0 * math.log10(massa_nano)) - 300.0

    dados.area_dispersao_cm2 = area_teorica + random.uniform(-15.0, 15.0)

    

    # Validação da Meta (> 200cm2)

    dados.eficiencia_atingida = (dados.area_dispersao_cm2 > 200.0)



print(f"--- Iniciando geração de {QTD_AMOSTRAS} amostras ---")



# Abre o arquivo para salvar os dados

with open(NOME_ARQUIVO, mode='w', newline='') as arquivo_csv:

    escritor = csv.writer(arquivo_csv)

    

    # Escreve o cabeçalho (primeira linha do Excel)

    escritor.writerow(["Timestamp", "Massa_Nano_mg", "Massa_Agua_mg", "Pressao_bar", "Temp_C", "Area_cm2", "Meta_OK"])

    

    # Loop que roda exatmente 50 vezes (ou quanto você definiu lá em cima)

    for i in range(QTD_AMOSTRAS):

        # Gera massa aleatória

        massa_teste = random.randint(300, 1000)

        

        simular_sensores(massa_teste)

        

        # Salva no arquivo

        escritor.writerow([

            dados.timestamp,

            dados.massa_nanomaterial_mg,

            dados.massa_agua_seca_mg,

            f"{dados.pressao_pico_bar:.2f}",

            f"{dados.temp_max_c:.2f}",

            f"{dados.area_dispersao_cm2:.2f}",

            1 if dados.eficiencia_atingida else 0

        ])

        

        # Mostra na tela só para você acompanhar

        print(f"Amostra {i+1}/{QTD_AMOSTRAS}: Massa {massa_teste}mg -> Área {dados.area_dispersao_cm2:.2f}cm2")

        

        # Pequena pausa para simular o tempo real (opcional, pode tirar se quiser rápido)

        time.sleep(0.1)



print(f"\n--- SUCESSO! ---")

print(f"Arquivo '{NOME_ARQUIVO}' gerado na pasta do projeto.")

print("Agora é só abrir esse arquivo no Excel.")