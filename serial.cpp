#include "mbed.h"
#include "rtos.h"
#include "globals.h"
#include "serial.h"

Serial                       pc(USBTX, USBRX);
Thread                       *readSerialThreadPtr;
MemoryPool<possitionType, 8> serPool;
Queue<     possitionType, 8> serQueue;


void readSerialInterupt(void) {
  LPC_UART0->IER = 0;                           // disable interupt temporary
  readSerialThreadPtr->signal_set(GOT_RX_DATA); // send signal to the thread
}


void readSerialThread(void const *args) {
  while (true) {
    Thread::signal_wait(GOT_RX_DATA);           // block until gets the signal, and then signal will get cleared

    possitionType *pos = serPool.alloc();       // read from serial and put msg to queue
    scanf("%f,%f\n", &pos->yaw, &pos->pitch);
    serQueue.put(pos);

    LPC_UART0->IER = 1;                         // enable interupt again
  }
}


void setupSerialThread() {
  static Thread localSerial(readSerialThread);
  localSerial.set_priority(osPriorityHigh);
  readSerialThreadPtr = &localSerial;           // global thread will be set to the worker
  pc.attach(&readSerialInterupt);
}

