/***
 * IoT Device
 *
 * @author David W. Arnold
 * @version 18th Oct 2019
 */
#include <Arduino.h>
#include <BLEDevice.h>
#include <unordered_map>
#include <tuple>

BLEClient *pClient;
BLEScan *scanner;

TaskHandle_t Task1;
TaskHandle_t Task2;

const int pirPin = 14;
const int scanInterval = 1349;
std::unordered_map<std::string, std::string> family({
                                                            {"f5:5c:00:54:6b:78", "BLE Beacon"}
                                                    });

std::unordered_map<std::string, std::tuple<int, unsigned long, unsigned long>> present;

int pirIndex = 0;

volatile int motion = 0;

void sense() {
    motion = 1;
}

// When scanning for BLE servers and each one found will be passed to this callback class.
class MyAdvertisedDeviceCallbacks : public BLEAdvertisedDeviceCallbacks {
    void onResult(BLEAdvertisedDevice advertisedDevice) override {
        std::string macAddress = advertisedDevice.getAddress().toString();
//        Serial.println(macAddress.c_str());
        auto result = family.find(macAddress);
        if (result != family.end()) {
            Serial.print(("** I've found: " + result->second + "\n").c_str());
            present[macAddress] = std::tuple<int, unsigned long, unsigned long>(pirIndex, millis(), millis());
        }
    }
};

void bluetoothSetup() {
    BLEDevice::init("");
    pClient = BLEDevice::createClient();
    scanner = BLEDevice::getScan();
    scanner->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks);
    scanner->setInterval(scanInterval);
    scanner->setWindow(449);
    scanner->setActiveScan(true);
}

void Task1code(void *parameter) {
    for (;;) {
        if (motion) {
            detachInterrupt(pirPin); // Necessary ?
            motion = 0;
            attachInterrupt(pirPin, sense, RISING); // Interrupt for when the PIR motion sensor, senses movement.
            Serial.print("** Blink! Motion detected\n");
            for (std::pair<std::string, std::tuple<int, unsigned long, unsigned long>> device : present) {
                if (std::get<0>(device.second) == pirIndex) {
                    Serial.print(("** Is home: " + family[device.first] + "\n").c_str()); // Device of a user just come home.
                }
            }
            pirIndex++;
        }
        delay(100);
    }
}

void Task2code(void *parameter) {
    for (;;) {
        BLEScanResults foundDevices = scanner->start(5, false);
        Serial.println("Scan done!");
        scanner->clearResults(); // Delete results fromBLEScan buffer to release memory
        delay(2000);
    }
}

void setup() {
    pinMode(pirPin, INPUT); // Setup pin as a digital input pin, from the PIR motion sensor.

    Serial.begin(115200);
    Serial.println("Starting Arduino BLE Client application...");

    bluetoothSetup();

    attachInterrupt(pirPin, sense, RISING); // Interrupt for when the PIR motion sensor, senses movement.

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
