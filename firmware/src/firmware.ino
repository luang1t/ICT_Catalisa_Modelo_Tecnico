/*

 * PROJETO ATENA - FIRMWARE DE MONITORAMENTO IOT

 * Módulo: Data Logger & Análise de Eficiência

 * Autor: Luan Cavalcante

 * Data: Dez/2025

 *

 * ATUALIZAÇÃO (Pós-Reunião Técnica):

 * Ajuste no modelo de dados para correlacionar Massa de Nanomaterial vs. Área de Dispersão.

 * A métrica de "Volume de Expansão" foi depreciada em favor de "Área de Cobertura (cm2)"

 * conforme alinhamento com a coordenação (Edinaldo/Marcos).

 */


#include <Arduino.h>  // Define os tipos básicos (uint32_t), Serial, e a função random()
#include <math.h>     // Necessário para a função log() - Logaritmo Natural

struct EnsaioDispersao {

    uint32_t timestamp;

    float pressao_pico_bar;    // Leitura do sensor piezoresistivo

    float temp_max_c;          // Leitura do termopar tipo K

   

    // VARIÁVEIS DE CONTROLE (Definidas no Setup do Ensaio)

    float massa_nanomaterial_mg; // Variável independente (Eixo X)

    float massa_agua_seca_mg;    // Constante

   

    // KPI CALCULADO (Via processamento de imagem Phantom v411)

    float area_dispersao_cm2;    // Variável dependente (Eixo Y)

   

    /*Flag de validação de sucesso*/

    bool eficiencia_atingida;

};



// Função de Simulação do Modelo Teórico (Para validação do protocolo MQTT)

void simularModeloDispersao(float massa_nano, EnsaioDispersao &dados) {

    // Modelo teórico: A dispersão aumenta logaritmicamente com a massa do energético

    // Baseado nas premissas de projeto Rev02

    dados.massa_nanomaterial_mg = massa_nano;

    dados.area_dispersao_cm2 = (log10(massa_nano) * 150.0) + random(-10, 10);

   

    Serial.print("Simulação -> Massa: ");

    Serial.print(dados.massa_nanomaterial_mg);

    Serial.print("mg | Área Estimada: ");

    Serial.print(dados.area_dispersao_cm2);

    Serial.println(" cm2");

}

EnsaioDispersao ensaioAtual;

void setup() {
    Serial.begin(115200); // Inicializa comunicação serial
    while(!Serial) { delay(10); } // Aguarda conexão
    
    Serial.println("--- INICIANDO PROJETO ATENA ---");
    Serial.println("Simulação de Dispersão (Modelo Logarítmico)");
    randomSeed(analogRead(0)); // Semente para números aleatórios
}

void loop() {
    // Simula um ensaio a cada 2 segundos com massa variável
    // Gera uma massa aleatória entre 300 e 1000 mg (como no seu Python)
    float massa_teste = random(300, 1001);
    
    simularModeloDispersao(massa_teste, ensaioAtual);
    
    delay(2000); 
}