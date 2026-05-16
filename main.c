#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "ws2812.pio.h"

#define PIN_LED 7
#define BTN_A 5
#define BTN_B 6

// Cores GRB (24-bits)
#define GREEN  0xFF0000
#define YELLOW 0xFFFF00
#define BLUE   0x0000FF
#define RED    0x00FF00
#define ORANGE 0x45FF00
#define OFF    0x000000

int estado_atual = 0;

static inline void put_pixel(uint32_t pixel_grb) {
    pio_sm_put_blocking(pio0, 0, pixel_grb << 8u);
}

// Matrizes das Letras e Frames dos Fogos de Artifício (5x5)
uint8_t G[] = {0,1,1,1,0, 1,0,0,0,1, 1,1,1,0,1, 1,0,0,0,0, 0,1,1,1,0};
uint8_t O[] = {0,1,1,1,0, 1,0,0,0,1, 1,0,0,0,1, 1,0,0,0,1, 0,1,1,1,0};
uint8_t L[] = {1,1,1,1,1, 1,0,0,0,0, 0,0,0,0,1, 1,0,0,0,0, 0,0,0,0,1};

uint8_t f1[] = {0,0,1,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0};
uint8_t f2[] = {0,0,1,0,0, 0,0,1,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0};
uint8_t f3[] = {0,0,1,0,0, 0,0,1,0,0, 0,0,1,0,0, 0,0,0,0,0, 0,0,0,0,0};
uint8_t f4[] = {0,0,0,0,0, 0,0,1,0,0, 0,0,1,0,0, 0,0,0,0,0, 0,0,0,0,0};
uint8_t f5[] = {0,0,0,0,0, 0,0,0,0,0, 0,0,1,0,0, 0,0,0,0,0, 0,0,0,0,0};
uint8_t f6[] = {0,0,0,0,0, 0,1,0,1,0, 0,0,1,0,0, 0,1,0,1,0, 0,0,0,0,0};
uint8_t f7[] = {1,0,0,0,1, 0,1,0,1,0, 0,0,1,0,0, 0,1,0,1,0, 1,0,0,0,1};
uint8_t f8[] = {1,0,0,0,1, 0,1,1,1,0, 1,1,1,1,1, 0,1,1,1,0, 1,0,0,0,1};
uint8_t f9[] = {1,0,1,0,1, 0,1,0,1,0, 1,0,1,0,1, 0,1,0,1,0, 1,0,1,0,1};
uint8_t f10[] = {1,0,1,0,1, 0,1,0,1,0, 1,0,0,0,1, 0,1,0,1,0, 1,0,1,0,1};
uint8_t f11[] = {1,0,1,0,1, 0,0,0,0,0, 1,0,0,0,1, 0,0,0,0,0, 1,0,1,0,1};

void animar_goool() {
    uint32_t cores[] = {RED, ORANGE, YELLOW, GREEN, BLUE};
    uint8_t* letras[] = {G, O, O, O, L};
    for(int k=0; k<5; k++) {
        if (gpio_get(BTN_B) == 0) return;   // Sair da animação se o botão oposto (B) for pressionado
        for(int i=0; i<25; i++) put_pixel(letras[k][i] ? cores[k] : OFF);
        sleep_ms(500);
    }
}

void animar_fogos() {
    uint8_t* frames[] = {f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11};
    for(int k=0; k<11; k++) {
        if (gpio_get(BTN_A) == 0) return;   // Sair da animação se o botão oposto (A) for pressionado
        for(int i=0; i<25; i++) put_pixel(frames[k][i] ? ORANGE : OFF);
        sleep_ms(120);
    }
    for(int i=0; i<25; i++) put_pixel(OFF);
        if (gpio_get(BTN_A) == 0) return;
        sleep_ms(400);
}

int main() {
    stdio_init_all();
    
    // Inicialização do PIO
    PIO pio = pio0;
    uint offset = pio_add_program(pio, &ws2812_program);
    ws2812_program_init(pio, 0, offset, PIN_LED, 800000, false);

    // Configuração dos Botões
    gpio_init(BTN_A); gpio_set_dir(BTN_A, GPIO_IN); gpio_pull_up(BTN_A);
    gpio_init(BTN_B); gpio_set_dir(BTN_B, GPIO_IN); gpio_pull_up(BTN_B);

    while (1) {
        if (!gpio_get(BTN_A)) { estado_atual = 1; sleep_ms(200); }
        if (!gpio_get(BTN_B)) { estado_atual = 2; sleep_ms(200); }

        if (estado_atual == 1) animar_goool();
        else if (estado_atual == 2) animar_fogos();
        
        sleep_ms(20);
    }
}