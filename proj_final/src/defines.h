#include "tx_api.h"

#define STACK_SIZE 4096
#define BYTE_POOL_SIZE (STACK_SIZE * 8)

#define THREAD_PERIOD(period_sec) (int)((period_sec)*TX_TIMER_TICKS_PER_SECOND)
