/**
 * PROJETO ATENA - FIRMWARE DE MONITORAMENTO IOT
 * Simulação para Validação de Relatório Técnico
 * * Autor: Luan Cavalcante
 * Plataforma: ESP32 (PlatformIO)
 */

#include <Arduino.h>
#include <math.h> 

// --- CONFIGURAÇÕES DA SIMULAÇÃO ---
// Se true, imprime apenas números separados por vírgula (fácil de jogar no Excel)
// Se false, imprime texto bonito para leitura humana
#define MODO_RELATORIO_CSV  false 

struct EnsaioDispersao {
    uint32_t timestamp;
    float pressao_pico_bar;    // Simulação do sensor piezoresistivo
    float temp_max_c;          // Simulação do termopar
    
    // VARIÁVEIS DE CONTROLE
    float massa_nanomaterial_mg;
    float massa_agua_seca_mg; 
    
    // KPI CALCULADO
    float area_dispersao_cm2;    
    bool eficiencia_atingida;
};

EnsaioDispersao ensaioAtual;

// Função Auxiliar para gerar float aleatório em um intervalo
float randomFloat(float min, float max) {
    return min + (float)random((max - min) * 100) / 100.0;
}

void simularSensores(float massa_nano, EnsaioDispersao &dados) {
    // 1. INPUT: Massa (Eixo X)
    dados.massa_nanomaterial_mg = massa_nano;
    dados.massa_agua_seca_mg = 500.0;
    dados.timestamp = millis();

    // 2. SIMULAÇÃO: Pressão (Bar)
    // Vamos supor que mais massa gera ligeiramente mais pressão, com ruído
    // Base: 10 bar + um pouquinho proporcional à massa + ruído
    dados.pressao_pico_bar = 10.0 + (massa_nano / 1000.0) + randomFloat(-0.5, 0.5);

    // 3. SIMULAÇÃO: Temperatura (°C)
    // Temperatura ambiente variando levemente (ex: processo gera pouco calor)
    dados.temp_max_c = randomFloat(28.0, 32.5);

    // 4. MODELO MATEMÁTICO (O mesmo do Python)
    // Fórmula: Area = 250 * log10(massa) - 300
    // Adicionamos um "+ random" para simular imperfeições do mundo real
    float area_teorica = (250.0 * log10(massa_nano)) - 300.0;
    dados.area_dispersao_cm2 = area_teorica + randomFloat(-15.0, 15.0); // +/- 15cm² de erro

    // 5. VALIDAÇÃO DE META
    // Se a área for maior que 200cm², o teste passou
    dados.eficiencia_atingida = (dados.area_dispersao_cm2 > 200.0);
}

void setup() {
    Serial.begin(115200);
    while(!Serial) { delay(10); }

    // Semente aleatória para garantir dados diferentes a cada reinício
    // Se o pino 34 estiver flutuando (sem nada), gera ruído bom
    randomSeed(analogRead(34)); 

    if (!MODO_RELATORIO_CSV) {
        Serial.println("--- INICIANDO SIMULAÇÃO PROJETO ATENA ---");
        Serial.println("Formula: 250 * log10(massa) - 300");
    } else {
        // Cabeçalho do CSV para o Excel
        Serial.println("Timestamp_ms,Massa_mg,Pressao_bar,Temp_C,Area_cm2,Meta_Atingida");
    }
}

void loop() {
    // Gera uma massa aleatória para o teste (entre 300mg e 1000mg)
    float massa_teste = random(300, 1001);

    // Roda a simulação
    simularSensores(massa_teste, ensaioAtual);

    // Saída de Dados
    if (MODO_RELATORIO_CSV) {
        Serial.print(ensaioAtual.timestamp); Serial.print(",");
        Serial.print(ensaioAtual.massa_nanomaterial_mg); Serial.print(",");
        Serial.print(ensaioAtual.massa_agua_seca_mg); Serial.print(",");
        Serial.print(ensaioAtual.pressao_pico_bar); Serial.print(",");
        Serial.print(ensaioAtual.temp_max_c); Serial.print(",");
        Serial.print(ensaioAtual.area_dispersao_cm2); Serial.print(",");
        Serial.println(ensaioAtual.eficiencia_atingida ? "1" : "0");
    } else {
        Serial.println("----------------------------------------");
        Serial.print("Massa Energetico: "); Serial.print(ensaioAtual.massa_nanomaterial_mg); Serial.println(" mg");
        Serial.print("Pressao Pico:     "); Serial.print(ensaioAtual.pressao_pico_bar); Serial.println(" bar");
        Serial.print("Temp Maxima:      "); Serial.print(ensaioAtual.temp_max_c); Serial.println(" C");
        Serial.print("AREA DISPERSAO:   "); Serial.print(ensaioAtual.area_dispersao_cm2); Serial.println(" cm2");
        Serial.print("STATUS META:      "); 
        if(ensaioAtual.eficiencia_atingida) Serial.println("[ APROVADO ]"); 
        else Serial.println("[ REPROVADO ]");
    }

    // Aguarda 2 segundos para o próximo "ensaio"
    delay(2000);
}