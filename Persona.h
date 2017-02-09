
#ifndef PERSONA_H
#define PERSONA_H

#include "globals.h"

namespace state {
  enum Enum {
    idle = 0,
    tracking,
    dayDreaming,
    starled,
    angry,
    happy
  };
}

class Persona {

public:

    Persona(float fieldOfView, float temper, float stamina, float attentionSpan);

    void move(possitionType move);

    possitionType getPossition();

    void tick();

    state::Enum getCurrentState();



private:
    float         modifierFov;
    float         modifierTemper;
    float         modifierStamina;
    float         modifierAttentionSpan;

    possitionType oldMove;
    unsigned int  oldMoveSinceTime;
    float         totalDistance;
    float         distanceIn3s;

    float         tired;
    float         annoyed;
    float         happy;

    state::Enum   currentState;
    unsigned int  currentStateSinceTime;
    state::Enum   oldState;

    unsigned int  time;
};

#endif
