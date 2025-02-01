## 🔥 Projeto: Controle de LEDs e Botões com Interrupções no BitDogLab

## 📌 Descrição do Projeto

Este projeto tem como objetivo consolidar o entendimento sobre interrupções em microcontroladores, utilizando a placa de desenvolvimento BitDogLab baseada no RP2040. Ele integra botões com interrupções, LEDs comuns e LEDs endereçáveis WS2812, aplicando técnicas de debouncing via software e resistores de pull-up internos.

## Objetivos

- Compreender o funcionamento e a aplicação de interrupções no RP2040.
- Implementar debouncing via software para evitar múltiplas detecções nos botões.
- Manipular e controlar LEDs comuns e LEDs WS2812.
- Utilizar resistores de pull-up internos nos botões de acionamento.
- Desenvolver um projeto funcional que integre hardware e software de forma eficiente.

## Componentes Utilizados

- **Placa BitDogLab (RP2040)**
- **Matriz 5x5 de LEDs WS2812**
- **LED RGB** 
- **Botão A** 
- **Botão B** 

## 📋 Funcionalidades do Projeto

- **Piscar LED RGB (vermelho):**
  O LED vermelho do LED RGB pisca 5 vezes por segundo.

- **Incremento do número exibido:**
  O botão A incrementa o número mostrado na matriz de LEDs sempre que for pressionado.

- **Decremento do número exibido:**
  O botão B decrementa o número mostrado na matriz de LEDs sempre que for pressionado.

- **Exibição de números na matriz WS2812:**
  Os LEDs WS2812 formam números de 0 a 9.

### 🛠️ Pré-requisitos

- **Hardware Necessário:**
  - Raspberry Pi Pico.
  - Matriz de LEDs WS2812B (5x5).

- **Software Necessário:**
  - Raspberry Pi Pico SDK configurado.
  - CMake para compilação.
  - VS Code com a extensão Raspberry Pi Pico
---

## 🛠️ Configurando o Projeto no VS Code

1. **Clonar o Repositório**:
```
git clone https://github.com/deciofrancis/EmbarcaTechInterruptions.git
cd seu-repositorio
```

2. **Abra o VS Code** e **importe o projeto**:
   - Vá até a **Extensão Raspberry Pi Pico**.
   - Selecione **Import Project**.
   - Escolha a pasta do repositório clonado.
   - Clique em **Import**.

3. **Compilar o código**:
   - Utilize a opção de **Build** da extensão.

4. **Rodar no BitDogLab**:
   - Na extensão do VSCode Raspberry PI PICO Project.
   - Clique em **Run Project(USB)** para enviar o arquivo para a BitDogLab.


## Desenvolvedor

[Décio Francis](https://www.linkedin.com/in/deciofrancis/)

## Vídeo de Demonstração

[Assista ao vídeo de demonstração aqui](https://youtube.com/shorts/lTdIc93EXjk)