# 🧠 Nano Kernel em C com Escalonadores SRTN e SPN

Implementação de um **Nano Kernel** em linguagem **C**, que utiliza dois algoritmos de escalonamento clássicos:

* **Shortest Remaining Time Next (SRTN)**
* **Shortest Process Next (SPN)**

## 📄 Descrição

O sistema simula o funcionamento de um kernel reduzido com suporte a escalonamento de processos. A escolha entre os algoritmos SRTN e SPN é feita dinamicamente pelo usuário na execução do programa.

A estrutura principal é baseada em:

* **Buffer circular** para organização dos processos
* **Módulo de escalonamento** selecionável (SRTN ou SPN)
* **Entrada de dados via arquivo** `stdin.txt`

A lógica de escalonamento é encapsulada em uma biblioteca separada, chamada `shotTime`, com as funções principais:

* `scheduler_SRTN()`: implementa o algoritmo SRTN
* `scheduler_SPN()`: implementa o algoritmo SPN

## 🗂 Estrutura de Arquivos

* [`main.c`](./main.c): arquivo principal que trata a interação com o usuário e executa a simulação.
* \[`shotTime.c` / `shotTime.h`]: biblioteca contendo as lógicas dos escalonadores.
* [`stdin.txt`](./stdin.txt): arquivo de entrada com os processos que serão simulados.

## 🔧 Requisitos para Executar

* Compilador **C** (GCC recomendado)
* Sistema com terminal

## ▶️ Como Compilar e Executar

```bash
# Compilar o programa
gcc -o nano_kernel main.c shotTime.c

# Executar
./nano_kernel
```

Durante a execução, o usuário poderá selecionar o algoritmo de escalonamento a ser utilizado.

## 📚 Conceitos Envolvidos

* Escalonamento de processos
* Estruturas de dados (buffer circular)
* Ponteiros de funções
* Modularização em C (uso de bibliotecas)
* Simulação de kernel

## 🎓 Sobre

Projeto final da disciplina **ECOS03 - Sistemas Operacionais Embarcados**, ofertada pela **Universidade Federal de Itajubá (UNIFEI)** no curso de **Engenharia da Computação**.

