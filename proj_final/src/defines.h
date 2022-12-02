#include "tx_api.h"

#define STACK_SIZE 4096
#define BYTE_POOL_SIZE (STACK_SIZE * 8)

// Mock resources to run on PC
#define IS_MOCK true

#define THREAD_PERIOD(period_sec) (int)((period_sec)*TX_TIMER_TICKS_PER_SECOND)
