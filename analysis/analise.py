import matplotlib.pyplot as plt
import numpy as np

# MODELAGEM TEÓRICA: EFICIÊNCIA DA BOMBA DE ESPUMA
# Ajuste de KPIs: Área vs. Massa

# CORREÇÃO: Criando um intervalo de massa (ex: de 300mg a 1000mg)
massa_nanomaterial_mg = np.linspace(300, 1000, 100)
agua_seca_fixa_mg = 500 

# Modelo de Dispersão (Curva Logarítmica Teórica)
# O ajuste do offset (-300) garante que o gráfico faça sentido físico
area_dispersao_cm2 = 250 * np.log10(massa_nanomaterial_mg) - 300

# Plotagem
plt.figure(figsize=(10, 6))
plt.plot(massa_nanomaterial_mg, area_dispersao_cm2, linestyle='-', color='firebrick', label='Modelo Teórico (Log)')

# Configuração visual
plt.title('Modelo Teórico: Eficiência de Dispersão (Projeto Atena)', fontsize=14)
plt.xlabel('Massa de Nanomaterial Energético (mg)', fontsize=12)
plt.ylabel('Área de Dispersão Efetiva (cm²)', fontsize=12)
plt.grid(True, which='both', linestyle='--', alpha=0.7)

# Meta de eficiência citada no firmware
plt.axhline(y=200, color='green', linestyle=':', label='Área Mínima de Eficiência (Meta)')
plt.legend()

plt.text(600, 350, 'Zona de Otimização\nEsperada', bbox=dict(facecolor='yellow', alpha=0.2))

plt.show()