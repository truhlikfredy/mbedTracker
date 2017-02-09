// Hello World to sweep a servo through its full range

#include "mbed.h"
#include "rtos.h"
#include "globals.h"
#include "Servo.h"
#include "serial.h"
#include "transform.h"
#include "Persona.h"

#define TEST_SERVOS false

Servo   servoYaw(p21);
Servo   servoPitch(p22);
Persona wheatley(0.4, 0.0, 2.0, 10.0);

void testServos() {
  for(float p=0; p<1.0; p += 0.01) {
      servoYaw.write(p);
      servoPitch.write(p);
      wait(0.01);
      printf("%f\n\r",p);
  }
  for(float p=1; p>0; p -= 0.01) {
      servoYaw.write(p);
      servoPitch.write(p);
      wait(0.01);
      printf("%f\n\r",p);
  }
}


void gimbalThread(void const *args) {
  while (true) {
    osEvent e = serQueue.get();

    if (e.status == osEventMessage) {
      possitionType *posPtr = (possitionType*)e.value.p;

      transform(posPtr);
      servoYaw.write(posPtr->yaw);
      servoPitch.write(posPtr->pitch);

      serPool.free(posPtr);
    }

  }
}


void setupThreads() {
  static Thread gimbal(gimbalThread);

  setupSerialThread();
}


void setupHardware() {
  // can do the range limit in the transform function
  //  servoPitch.calibrate(0.0008,80);              //slightly limit range or the gimbal will hit PCB
}

void setupPersona() {
  static Ticker ticker;

  //need to solve this first ISO C++ forbids taking the address of a bound member function to form a pointer to member function.  Say '&Persona::tick' [-fpermissive]
  //  ticker.attach(&wheatley.tick, 1.0);
}


int main() {


  setupHardware();
  setupThreads();
  setupPersona();

  if (TEST_SERVOS) {
    testServos();
  }
  else {
    while (true) {
      Thread::wait(1000);
    }
  }
}
