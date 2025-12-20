#include <Arduino.h>
#include <math.h> 

/*
 * PROJETO ATENA - FIRMWARE DE MONITORAMENTO IOT
 * Autor: Luan Cavalcante
 * Data: Dez/2025
 */

struct EnsaioDispersao {
    uint32_t timestamp;
    float pressao_pico_bar;    // Sensor piezoresistivo
    float temp_max_c;          // Termopar tipo K
    
    // VARIÁVEIS DE CONTROLE
    float massa_nanomaterial_mg; 
    float massa_agua_seca_mg;    
    
    // KPI CALCULADO
    float area_dispersao_cm2;    
    bool eficiencia_atingida;
};

// Função de Simulação
void simularModeloDispersao(float massa_nano, EnsaioDispersao &dados) {
    dados.massa_nanomaterial_mg = massa_nano;
    
    // CORREÇÃO TÉCNICA: Usando log10() para bater com o Python
    // Fórmula ajustada para parecer com a do Python: 250 * log10(x) - 300
    dados.area_dispersao_cm2 = (250.0 * log10(massa_nano)) - 300.0 + random(-5, 5); 
    
    // Validação simples da meta (ex: > 200cm2)
    dados.eficiencia_atingida = (dados.area_dispersao_cm2 > 200.0);

    Serial.print("Massa: ");
    Serial.print(dados.massa_nanomaterial_mg);
    Serial.print(" mg | Área Est.: ");
    Serial.print(dados.area_dispersao_cm2);
    Serial.print(" cm2 | Meta: ");
    Serial.println(dados.eficiencia_atingida ? "OK" : "NOK");
}

// --- BLOCOS OBRIGATÓRIOS ADICIONADOS ---

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