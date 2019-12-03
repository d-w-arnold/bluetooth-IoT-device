/**
 * IoT Device
 *
 * @author David W. Arnold
 * @version 29th Oct 2019
 */
#include <Arduino.h>
#include <BLEDevice.h>
#include <unordered_map>
#include <tuple>

BLEClient *pClient;
BLEScan *scanner;

TaskHandle_t Task1;
TaskHandle_t Task2;

const int pirPin = 17;
const int scanInterval = 1349;
std::unordered_map<std::string, std::string> family;
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
        auto resultFamily = family.find(macAddress);
        auto resultPresent = present.find(macAddress);
        if (resultFamily != family.end()) {
//            Serial.print(("** I've found: " + resultFamily->second + "\n").c_str());
            if (resultPresent != present.end()) {
                present[macAddress] = std::tuple<int, unsigned long, unsigned long>(std::get<0>(resultPresent->second),
                                                                                    std::get<1>(resultPresent->second),
                                                                                    millis());
            } else {
                present[macAddress] = std::tuple<int, unsigned long, unsigned long>(pirIndex, millis(), millis());
            }
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
        // Populate information
        while (Serial.available()) {
            std::string bleDeviceMACAddress = Serial.readStringUntil('+').c_str();
            std::string bleDeviceName = Serial.readStringUntil('*').c_str();
            std::pair<std::string, std::string> device(bleDeviceMACAddress, bleDeviceName);
            family.insert(device);
        }
        // If motion is detected
        if (motion) {
            detachInterrupt(pirPin); // Necessary ?
            motion = 0;
            attachInterrupt(pirPin, sense, RISING); // Interrupt for when the PIR motion sensor, senses movement.
//            Serial.print("** Blink! Motion detected\n");
            for (std::pair<std::string, std::tuple<int, unsigned long, unsigned long>> device : present) {
                auto devicePirIndex = std::get<0>(device.second);
                auto deviceFirstTime = std::get<1>(device.second);
                if ((devicePirIndex == pirIndex) && ((millis() - deviceFirstTime) < (scanInterval * 10))) {
                    // Device of a user just come home.
//                    Serial.print(("** Device come home: " + family[device.first] + "\n").c_str());
                    Serial.print((family[device.first] + "\n").c_str());
                } else {
//                    Serial.print(("** Device not come home: " + family[device.first] + "\n").c_str());
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
//        Serial.println("Scan done!");
        std::unordered_map<std::string, std::tuple<int, unsigned long, unsigned long>>::iterator it;
        for (it = present.begin(); it != present.end();) {
            auto deviceMostRecentTime = std::get<2>(it->second);
            if ((millis() - deviceMostRecentTime) > (scanInterval * 10)) {
//                Serial.print(("** Removed from present: " + family[it->first] + "\n").c_str());
                it = present.erase(it);
            } else {
                it++;
            }
        }
        scanner->clearResults(); // Delete results fromBLEScan buffer to release memory
        delay(2000);
    }
}

void setup() {
    pinMode(pirPin, INPUT); // Setup pin as a digital input pin, from the PIR motion sensor.

    Serial.begin(9600);
//    Serial.println("\n\nStarting IoT Device ...");

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
