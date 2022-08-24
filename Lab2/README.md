# README

Respostas das questões do laboratório 2

## 5. Entenda como é o processo de inicialização que ocorre antes da função main ser chamada.

Inicialmente é chamada a função `ResetISR` que ativa a FPU e então chama o ponto de entrada do programa pela função `__iar_program_start`.
Essa função chama no assembly `__iar_init_vfp`, a qual deve iniciar em si a FPU, então `__low_level_init`, que chama `_call_main`, a qual move o PC para a entrada da `main`.

Durante essas funções há operações que não entendi muito bem.
Algumas comparações entre constantes que parecem desnecessárias de primeira vista.

## Porque a variável ui32Loop é declarada como volatile dentro de main()?

Variáveis `volatile` são aquelas que podem ser modificadas "sem o conhecimento" do compilador.
Isso faz com que a variável seja guardada em RAM também.

Observando o assembly gerado, é possível perceber que, ao retirar o `volatile`, o compilador retira os loops de delay, tornando o loop apenas um `BL`.

Isso pode ser causado por otimizações feitas pelo compilador.

## Altere este programa para que a temporização seja efetuada consultando o SysTick.

Para fazer isso, basta alterar e consultar o SysClock por meio da função `SysCtlClockFreqSet`.
Após isso, é possível setar um delay utilizando o clock por meio da função `SysCtlDelay(uint32_t)`.
