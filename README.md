# ATIVIDADE 3 - RP2040/ BitDogLab - PIO E MATRIZ DE LEDs 5X5

Este projeto controla uma matriz de LEDs WS2812 (NeoPixel) na placa BitDogLab utilizando o Raspberry Pi Pico. O sistema altera entre duas animações principais com base nos comandos dos botões, contando com filtragem de ruído mecânico (debounce) via software.

## Animações e Comandos

* **Botão A (GP5):** Inicia a animação "GOOOL" (letras piscando sequencialmente com troca de cores).
* **Botão B (GP6):** Inicia a animação "Fogos de Artifício" (sequência de 11 frames de explosão e um tempo final apagado).

## Arquivos do Repositório

* `main.c`: Código principal com a lógica dos botões, debounce e arrays das animações.
* `ws2812.pio`: Código assembly do PIO para garantir a temporização correta dos LEDs.
* `CMakeLists.txt` e `pico_sdk_import.cmake`: Arquivos de configuração do compilador CMake.
* `.gitignore`: Configurado para ignorar a pasta build/ e não poluir o repositório.

## Como Executar

1. Abra a pasta do projeto no VS Code com a extensão do Raspberry Pi Pico instalada.
2. Clique em **Build** para compilar o projeto e gerar o arquivo `pratica2ws2812.uf2` dentro da pasta `build`.
3. Conecte a placa segurando o botão **BOOT**, dê um clique em **RESET** e solte o BOOT.
4. Arraste o arquivo `.uf2` para a unidade de disco `RPI-RP2` que se abriu no computador.

## Documentação e Testes

* **Relatório Técnico:** https://drive.google.com/file/d/1Yjyn-G_xm3UdvuE6IfxRfUU-_cDdF4o6/view?usp=sharing
* **Vídeo de Demonstração:** https://drive.google.com/file/d/1FtD3a_n-BD41WQc-STdntbOCFGccBgxP/view?usp=sharing
