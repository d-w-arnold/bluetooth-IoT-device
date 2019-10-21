/***
 * LED Blinking
 *
 * @author David W. Arnold
 * @version 18th Oct 2019
 */
#include <Arduino.h>
#include <BLEDevice.h>
#include <unordered_map>

BLEClient *pClient;
BLEScan *scanner;

TaskHandle_t Task1;
TaskHandle_t Task2;

const int ledPin = 14;
const int pirPin = 0;

volatile int motion = 0;

std::unordered_map<std::string, unsigned long> m;

void sense() {
    motion = 1;
}

void blink() {
    digitalWrite(ledPin, HIGH);    // turn on the LED
    delay(1000); // wait for half a second or 1000 milliseconds
    digitalWrite(ledPin, LOW); // turn off the LED
    delay(500);    // wait for half a second or 500 milliseconds
}

// When scanning for BLE servers and each one found will be passed to this callback class.
class MyAdvertisedDeviceCallbacks : public BLEAdvertisedDeviceCallbacks {
    // Called for each advertising BLE server found.
    void onResult(BLEAdvertisedDevice advertisedDevice) override {
        Serial.print("BLE Advertised Device found: ");
        if (!(advertisedDevice.getName().empty())) {
            Serial.println(advertisedDevice.getName().c_str());
        }
        Serial.println(advertisedDevice.getAddress().toString().c_str());
    }
};

void bluetoothSetup() {
    // Clients do not need their own name.
    BLEDevice::init("");

    pClient = BLEDevice::createClient();

    // Set up scanner to search for BLE devices.
    scanner = BLEDevice::getScan();
    scanner->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks);
    scanner->setInterval(1349);
    scanner->setWindow(449);
    scanner->setActiveScan(true);
}

void Task1code(void *parameter) {
    for (;;) {
        if (motion) {
            motion = 0;
            for (int i = 0; i < 2; ++i) {
                blink();
            }
        }
        delay(100);
    }
}

void Task2code(void *parameter) {
    for (;;) {
        // put your main code here, to run repeatedly:
        BLEScanResults foundDevices = scanner->start(5, false);
        Serial.print("Devices found: ");
        int deviceCount = foundDevices.getCount();
        Serial.println(deviceCount);
        Serial.println("Scan done!");
        scanner->clearResults();   // delete results fromBLEScan buffer to release memory
        delay(2000);
    }
}

void setup() {
    // setup pin 5 as a digital output pin
    pinMode(ledPin, OUTPUT);

    // setup pin 0 as a digital input pin, from the PIR motion sensor.
    pinMode(pirPin, INPUT);

    Serial.begin(115200);
    Serial.println("Starting Arduino BLE Client application...");
    bluetoothSetup();

    // Interrupt for when the PIR motion sensor, senses movement.
    attachInterrupt(pirPin, sense, CHANGE);

    xTaskCreatePinnedToCore(
            Task1code, /* Function to implement the task */
            "Task1", /* Name of the task */
            10000,  /* Stack size in words */
            NULL,  /* Task input parameter */
            1,  /* Priority of the task */
            &Task1,  /* Task handle. */
            0 /* Core where the task should run */
    );


    xTaskCreatePinnedToCore(
            Task2code, /* Function to implement the task */
            "Task2", /* Name of the task */
            10000,  /* Stack size in words */
            NULL,  /* Task input parameter */
            1,  /* Priority of the task */
            &Task2,  /* Task handle. */
            1 /* Core where the task should run */
    );

}

void loop() {

}

// TODO: Now Add basic BLE implementation to scan for all Bluetooth devices nearby,
//  maybe return the list of details for each device (MAC Address in particular)
//  look into CO657 Ass 1 (Client) as a start, of scanning for devices,
//  though I won't require a specific service.
