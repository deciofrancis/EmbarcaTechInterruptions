#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "pico/bootrom.h"

// Inclusão do arquivo gerado pelo PIO
#include "EmbarcaTechInterruptions.pio.h"

// Inclusão dos frames numéricos para a matriz de LEDs
#include "framesNumeros.c"

// Definição de pinos
#define LED_GREEN 11
#define LED_BLUE 12
#define LED_RED 13
#define BOTAO_A 5
#define BOTAO_B 6
#define LED_PIN 7     // Pino da matriz de LEDs
#define NUM_PIXELS 25 // Matriz de LEDs

// Definição de variáveis globais
uint valor_led;
PIO pio;
uint sm;
int static volatile num_atual = 0; // Número atualmente exibido na matriz
uint volatile contador_botoes = 0;
uint static volatile ultimo_tempo_botao = 0; // Para debounce dos botões

// Função para controlar a intensidade do LED RGB
void controlar_intensidade_led(uint pino, uint intensidade)
{
    // Ajusta a intensidade do PWM
    if (intensidade > 255)
        intensidade = 255;
    if (intensidade < 0)
        intensidade = 0;
}

// Define as cores para os LEDs da matriz e a intensidade
uint matrix_rgb(float r, float g, float b, uint intensidade)
{
    unsigned char R = r * 255 * (intensidade / 255.0); // Ajusta a intensidade
    unsigned char G = g * 255 * (intensidade / 255.0); // Ajusta a intensidade
    unsigned char B = b * 255 * (intensidade / 255.0); // Ajusta a intensidade
    return (G << 24) | (R << 16) | (B << 8);
}

// Desenha os números na matriz de LEDs
void desenho_pio(double *desenho, uint32_t valor_led, PIO pio, uint sm, double r, double g, double b)
{
    for (int16_t i = 0; i < NUM_PIXELS; i++)
    {
        valor_led = matrix_rgb(desenho[i] * r, desenho[i] * g, desenho[i] * b, 10);
        pio_sm_put_blocking(pio, sm, valor_led);
    }
}

// Função para piscar um LED
void pisca_leds(int led, int tempo)
{
    gpio_put(led, 1);
    sleep_ms(tempo);
    gpio_put(led, 0);
    sleep_ms(tempo);
}

// Converte a posição (x, y) da matriz de LEDs para a posição do vetor
int getid(int x, int y)
{
    if (y % 2 == 0)
    {
        return 24 - (y * 5 + x); // Linha par: esquerda para direita
    }
    else
    {
        return 24 - (y * 5 + (4 - x)); // Linha ímpar: direita para esquerda
    }
}

// Garante que o número exibido permaneça dentro do intervalo 0-9
void correcao_num()
{
    if (num_atual < 0)
    {
        num_atual = 9;
    }
    else if (num_atual > 9)
    {
        num_atual = 0;
    }
}

// Função que trata o evento de pressionar o botão e faz o tratamento do debounce
void tratar_evento_botao(uint botao, uint32_t events)
{
    // Array de ponteiros para os frames dos números
    double *framesNumeros[10] = {numero0, numero1, numero2, numero3, numero4, numero5, numero6, numero7, numero8, numero9};

    uint time = to_ms_since_boot(get_absolute_time()); // Tempo atual desde o boot
    if (time - ultimo_tempo_botao > 250)               // Debounce para evitar múltiplos acionamentos
    {
        ultimo_tempo_botao = time;

        if (!gpio_get(botao)) // Verifica se o botão está pressionado
        {
            if (botao == BOTAO_A)
            {
                num_atual++;
            }
            else
            {
                num_atual--;
            }

            correcao_num();
            desenho_pio(framesNumeros[num_atual], valor_led, pio, sm, 0.3, 0.8, 0.1);
            contador_botoes++;
        }
    }
}

// Função principal
int main()
{
    // Inicializa a matriz de LEDs
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    // Inicializa os botões
    gpio_init(BOTAO_A);
    gpio_set_dir(BOTAO_A, GPIO_IN);
    gpio_pull_up(BOTAO_A);
    gpio_init(BOTAO_B);
    gpio_set_dir(BOTAO_B, GPIO_IN);
    gpio_pull_up(BOTAO_B);

    // Inicializa os LEDs RGB
    gpio_init(LED_RED);
    gpio_set_dir(LED_RED, GPIO_OUT);
    gpio_init(LED_GREEN);
    gpio_set_dir(LED_GREEN, GPIO_OUT);
    gpio_init(LED_BLUE);
    gpio_set_dir(LED_BLUE, GPIO_OUT);

    bool frequenciaClock;
    pio = pio0;

    // Configuração do clock do sistema
    frequenciaClock = set_sys_clock_khz(128000, false);
    stdio_init_all(); // Inicializa comunicação serial

    uint offset = pio_add_program(pio, &pio_matrix_program);
    sm = pio_claim_unused_sm(pio, true);
    pio_matrix_program_init(pio, sm, offset, LED_PIN);

    // Configuração de interrupções dos botões
    gpio_set_irq_enabled_with_callback(BOTAO_A, GPIO_IRQ_EDGE_FALL, true, &tratar_evento_botao);
    gpio_set_irq_enabled_with_callback(BOTAO_B, GPIO_IRQ_EDGE_FALL, true, &tratar_evento_botao);

    // Loop que faz piscar o led
    while (true)
    {
        pisca_leds(LED_RED, 200); // Pisca o LED vermelho a cada 200ms
    }

    return 0;
}