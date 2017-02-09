#include "globals.h"


//mirror axis, depending if it should move as in reality or as webcam mirrored image shows
const bool MIRROR_YAW  = false;

possitionType* transform(possitionType *pos) {

  const float PITCH_CENTER = 0.5;

  if (MIRROR_YAW) {
    pos->yaw *= -1;
  }

  // scale, offset, limit, transform possition depending what is the difference in
  // hardware ranges of the servos, degree of freedom and difference
  // between the camera location and given lamp
  // could compensate for lens distorition as well.


  // slightly limit pitch range so the gimbal will not hurt itself
  pos->pitch   = ((pos->pitch - PITCH_CENTER) * 0.8) + PITCH_CENTER;


  return(pos);
}
