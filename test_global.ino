#include "ErgoK.h"

ErgoK k1;

void updateClic2(){
  k1.updateClicks();
}


void setup2()
{
  pinMode(7, INPUT);
  attachInterrupt(digitalPinToInterrupt(7), updateClic, CHANGE);
  k1.begin(A0, A1, A2, A3, A4,4 );
}

void loop2(){
k1.update();
}
