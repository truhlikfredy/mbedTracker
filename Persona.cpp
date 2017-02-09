#include "Persona.h"
#include <cmath>
#include "mbed.h"

float possitionDistance(possitionType a, possitionType b) {
  const float x = pow(a.yaw   - b.yaw,   2);
  const float y = pow(a.pitch - b.pitch, 2);

  return(sqrt(x+y));
}


Persona::Persona(float fieldOfView, float temper, float stamina, float attentionSpan) {
  modifierFov           = fieldOfView;
  modifierTemper        = temper;
  modifierStamina       = stamina;
  modifierAttentionSpan = attentionSpan;

  currentState          = state::idle;
  time                  = 0;
  oldMove               = { 0.5, 0.5};
}


void Persona::move(possitionType move) {

  // if i'm idle and the tracked object can be seen with my field of view from my idlePosition
  if (currentState == state::idle && possitionDistance(move, oldMove) < modifierFov) {
    currentState = state::tracking;
  }

  if (currentState == state:: tracking) {
    totalDistance += possitionDistance(move, oldMove);
    distanceIn3s  += possitionDistance(move, oldMove);

    oldMove = move;
    oldMoveSinceTime = time;
  }
}


possitionType Persona::getPossition() {
  // depending on the state this could return different
  // moves, not just tracking. animations from look-up-tables etc...

  return oldMove;
}


void Persona::tick() {
  time++;

  // this will not be working perfectly to count distance in last 3s
  if (time%3 == 0) {
    distanceIn3s = 0;
  }
}


state::Enum Persona::getCurrentState() {
  // track with state machine current state
  // and allow transition only to certain states
  // iddle -> tracking or starled
  // it can't go from iddle to annoyed straightaway
  // for each state caculate all the acumulated values how tired/annoyed he is
  //
  // if lot of distance is covered in short period of time get annoyed
  // if there is not enough distance covered in some time get bored
  return currentState;
}
