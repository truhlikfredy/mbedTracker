#ifndef SERIAL_HEADER_FILE
#define SERIAL_HEADER_FILE

#include "rtos.h"
#include "globals.h"

#define GOT_RX_DATA 0x01

extern Thread                       *readSerialThreadPtr;
extern MemoryPool<possitionType, 8> serPool;
extern Queue<     possitionType, 8> serQueue;

void setupSerialThread();

#endif
