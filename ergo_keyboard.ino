#include "ErgoK.h"

ErgoK k;

void updateClic(){
  k.updateClicks();
}


void setup()
{
  pinMode(7, INPUT);
  attachInterrupt(digitalPinToInterrupt(7), updateClic, CHANGE);
  k.begin(A2, A1, A0, A3, A4,A5);
}

void loop()
{
k.update();
}
