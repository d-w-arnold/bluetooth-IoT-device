/***
 * LED Blinking
 *
 * @author David W. Arnold
 * @version 18th Oct 2019
 */
#include <Arduino.h>

const int ledPin = 14;
const int pirPin = 0;

volatile int motion = 0;

void sense(void)
{
    motion = 1;
}

void blink(void)
{
    digitalWrite(ledPin, HIGH);	// turn on the LED
    delay(1000);	// wait for half a second or 500 milliseconds
    digitalWrite(ledPin, LOW); // turn off the LED
    delay(500);	// wait for half a second or 500 milliseconds
}

void setup()
{
    // setup pin 5 as a digital output pin
    pinMode(ledPin, OUTPUT);

    // setup pin 0 as a digital input pin, from the PIR motion sensor.
    pinMode(pirPin, INPUT);

    // Interrupt for when the PIR motion sensor, senses movement.
    attachInterrupt(0, sense, CHANGE);
}

void loop()
{
    if (motion) {
        for (int i = 0; i < 3; ++i) {
            blink();
        }
        motion = 0;
    }
}

// TODO: Now Add basic BLE implementation to scan for all Bluetooth devices nearby,
//  maybe return the list of details for each device (MAC Address in particular)
//  look into CO657 Ass 1 (Client) as a start, of scanning for devices,
//  though I won't require a specific service.
