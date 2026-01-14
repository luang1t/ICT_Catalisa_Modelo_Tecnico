/**
 * PROJETO ATENA - SIMULAÇÃO PC (Sem ESP32)
 * Autor: Luan Cavalcante
 * Adaptação para rodar em C++ Padrão (Windows/Linux)
 */

/* #include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <thread> // Para o delay
#include <chrono> // Para o delay

// --- CONFIGURAÇÕES ---
// true = Saída CSV (Excel)
// false = Saída Bonita (Terminal)
#define MODO_RELATORIO_CSV  false 

using namespace std;

struct EnsaioDispersao {
    long timestamp;
    float pressao_pico_bar;
    float temp_max_c;
    
    // VARIÁVEIS DE CONTROLE
    float massa_nanomaterial_mg; 
    float massa_agua_seca_mg;
    
    // KPI CALCULADO
    float area_dispersao_cm2;    
    bool eficiencia_atingida;
};

EnsaioDispersao ensaioAtual;

// Função Auxiliar para gerar float aleatório
float randomFloat(float min, float max) {
    return min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)));
}

// Simula o tempo do Arduino (millis)
long getSimulatedMillis() {
    static auto start = std::chrono::steady_clock::now();
    auto now = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count();
}

void simularSensores(float massa_nano, EnsaioDispersao &dados) {
    dados.timestamp = getSimulatedMillis();
    dados.massa_nanomaterial_mg = massa_nano;
    dados.massa_agua_seca_mg = 500.0; // Controle fixo

    // Simulação Pressão
    dados.pressao_pico_bar = 10.0 + (massa_nano / 1000.0) + randomFloat(-0.5, 0.5);

    // Simulação Temperatura
    dados.temp_max_c = randomFloat(28.0, 32.5);

    // MODELO MATEMÁTICO (Mesma lógica do Firmware)
    // Area = 250 * log10(massa) - 300
    float area_teorica = (250.0 * log10(massa_nano)) - 300.0;
    dados.area_dispersao_cm2 = area_teorica + randomFloat(-15.0, 15.0);

    dados.eficiencia_atingida = (dados.area_dispersao_cm2 > 200.0);
}

int main() {
    // Inicializa a semente aleatória
    srand(static_cast <unsigned> (time(0)));

    if (!MODO_RELATORIO_CSV) {
        cout << "--- INICIANDO SIMULACAO (VERSAO PC) ---" << endl;
        cout << "Formula: 250 * log10(massa) - 300" << endl;
    } else {
        cout << "Timestamp,Massa_Nano_mg,Massa_Agua_mg,Pressao_bar,Temp_C,Area_cm2,Meta_OK" << endl;
    }

    // Loop Infinito (simulando o loop do Arduino)
    // Para parar, pressione Ctrl+C no terminal
    while (true) {
        float massa_teste = 300 + (rand() % 701); // Random entre 300 e 1000

        simularSensores(massa_teste, ensaioAtual);

        if (MODO_RELATORIO_CSV) {
            cout << ensaioAtual.timestamp << ","
                 << ensaioAtual.massa_nanomaterial_mg << ","
                 << ensaioAtual.massa_agua_seca_mg << ","
                 << ensaioAtual.pressao_pico_bar << ","
                 << ensaioAtual.temp_max_c << ","
                 << ensaioAtual.area_dispersao_cm2 << ","
                 << (ensaioAtual.eficiencia_atingida ? "1" : "0") << endl;
        } else {
            cout << fixed << setprecision(2);
            cout << "----------------------------------------" << endl;
            cout << "Massa Energetico: " << ensaioAtual.massa_nanomaterial_mg << " mg" << endl;
            cout << "Massa Agua Seca:  " << ensaioAtual.massa_agua_seca_mg << " mg (Ctrl)" << endl;
            cout << "Pressao Pico:     " << ensaioAtual.pressao_pico_bar << " bar" << endl;
            cout << "Temp Maxima:      " << ensaioAtual.temp_max_c << " C" << endl;
            cout << "AREA DISPERSAO:   " << ensaioAtual.area_dispersao_cm2 << " cm2" << endl;
            cout << "RESULTADO:        " << (ensaioAtual.eficiencia_atingida ? "[ APROVADO ]" : "[ REPROVADO ]") << endl;
        }

        // Delay de 2 segundos
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    }

    return 0;
}
*/