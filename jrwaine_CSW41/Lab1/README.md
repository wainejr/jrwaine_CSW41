# README

Respostas das questões do laboratório 1

## Onde aparecem as mensagem enviadas via cout?

É aberto um terminal para I/O ao executar o programa. Nele são mostrados os textos dos cout

## Como entrar dados para leitura via cin?

No mesmo terminal para I/O é possível entrar os dados, com uma mensagem escrita "Input needed!" aparecendo no nome da janela. 

## Quais os valores dos símbolos pré-definidos que você escolheu? O que significam?

`__DATE__`: Dia, mês e ano atual
`__FILE__`: Caminho do arquivo atual do cout (a main.cpp, no caso)
`__TIME__`: Horário atual
`__CORE__`: Inteiro que reflete a opção `--cpu` que define a arquitetura para gerar código.
`__ARMVFP__`: Inteiro que reflete a opção de `--fpu`, o qual permite gerar código que utiliza a unidade de operação em FP (ou seja, permite fazer contas com ponto flutuante).
`__ARM_SIZEOF_WCHAR_T`: Inteiro que identifica o tamanho do tipo `wchar_t`.

## Que tipo de instrução assembly foi usada para a soma dos dois valores float?

`VADD.F32` foi a instrução utilizada

## Qual configuração do projeto no IAR causou o uso desta instrução?

Ativar a FPU em 
Project -> Options -> General Options -> 32 bits -> Floating point settings