#include <AccelStepper.h>

const int jX = A7;
const int stepX = 3;
const int dirX = 2;
long speedX, valX, mapX;


const int maxSpeed = 1000;
const int minSpeed = 0;
const float accelerazione = 50.0;

const int treshold = 30;
long tresholdUp, tresholdDown;

boolean abilitato, muoviX;
AccelStepper motoreX(AccelStepper::DRIVER, stepX, dirX);

void setup() {
  speedX = 0;
  tresholdDown = (maxSpeed / 2) - treshold;
  tresholdUp = (maxSpeed / 2) + treshold;

  motoreX.setMaxSpeed(maxSpeed);
  motoreX.setSpeed(minSpeed);
  motoreX.setAcceleration(accelerazione);

}

void loop() {
  valX = analogRead(jX);
  mapX = map(valX, 0, 1023, minSpeed, maxSpeed);
  pilotaMotori(mapX);
}

void pilotaMotori(long mapX) {

  if (mapX <= tresholdDown) {

    speedX = -map(mapX, tresholdDown, minSpeed,   minSpeed, maxSpeed);
    muoviX = true;
  } else if (mapX >= tresholdUp) {

    speedX = map(mapX,  maxSpeed, tresholdUp,  maxSpeed, minSpeed);
    muoviX = true;
  } else {

    speedX = 0;
    muoviX = false;
  }

  if (muoviX) {
    motoreX.setSpeed(speedX);
    motoreX.run();
  } else {
    motoreX.stop();
  }

}
