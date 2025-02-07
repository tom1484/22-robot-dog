#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "Interact_Inputs.h"

#define CAP_TOUCH_PIN      4
#define LIMIT_SWITCH_PIN   12
#define PHOTO_RESISTOR_PIN 32

EventGroupHandle_t intEG;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  intEG = createInteractEG();

  initCapTouch(CAP_TOUCH_PIN, 50);
  initLimitSwitch(LIMIT_SWITCH_PIN, RISING);
  initPhotoResistor(PHOTO_RESISTOR_PIN, 1500, 300);    // with 10 kohm to GND
}

void loop() {
  // put your main code here, to run repeatedly:
  EventBits_t curBits;
  curBits = xEventGroupWaitBits( intEG,
                                 CAP_TOUCH_BIT | LIMIT_SWITCH_BIT | PHOTO_RESIETOR_BIT,
                                 pdFALSE,   // true -> clear the bits before returning, won't affect returned value
                                 pdFALSE,   // true -> wait for all
                                 portMAX_DELAY);

  if (curBits & CAP_TOUCH_BIT)
  {
    Serial.println("CAP");// (touchRead(CAP_TOUCH_PIN));
    xEventGroupClearBits(intEG, CAP_TOUCH_BIT);
  }
  if (curBits & LIMIT_SWITCH_BIT)
  {
    Serial.println("LIM");
    xEventGroupClearBits(intEG, LIMIT_SWITCH_BIT);
  }
  if (curBits & PHOTO_RESIETOR_BIT)
  {
    Serial.println("PHR");
    xEventGroupClearBits(intEG, PHOTO_RESIETOR_BIT);
  }
}
