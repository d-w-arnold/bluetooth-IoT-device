/***
 * LED Blinking
 *
 * @author David W. Arnold
 * @version 18th Oct 2019
 */
#include <Arduino.h>
#include <BLEDevice.h>
#include <unordered_map>
#include <list>

BLEClient *pClient;
BLEScan *scanner;

TaskHandle_t Task1;
TaskHandle_t Task2;

const int ledPin = 18;
const int pirPin = 14;
const int blinks = 1;
const int scanInterval = 1349;
const std::string bleBeacon = "f5:5c:00:54:6b:78";

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
        std::string macAddress = advertisedDevice.getAddress().toString();
        Serial.println(macAddress.c_str());
        if (macAddress == bleBeacon) {
            Serial.print("** I've found the BLE Beacon :)\n");
        }
    }
};

void bluetoothSetup() {
    // Clients do not need their own name.
    BLEDevice::init("");

    pClient = BLEDevice::createClient();

    // Set up scanner to search for BLE devices.
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
            attachInterrupt(pirPin, sense, CHANGE); // Necessary ?
            for (int i = 0; i < blinks; ++i) {
                blink();
            }
            std::list<std::string> x;
            for (auto & it : m) {
                std::string tmp = it.first;
                x.push_back(tmp);
            }
            delay(scanInterval * 2);
            std::list<std::string> y;
            for (auto & it : m) {
                std::string tmp = it.first;
                y.push_back(tmp);
            }
            std::list<std::string> diff;
            for (const auto & ye : y) {
                auto isInX = std::find(x.begin(), x.end(), ye) != x.end();
                if (!isInX) {
                    diff.push_back(ye);
                }
            }
            // diff contains list of new devices.
            // If these MAC addresses match any of the known MAC address of devices within a family,
            //  send a welcome message,
            //  and trigger the IoT system to turn on smart home lights accordingly.
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

        // If the map is empty, it must be the first scan, populate.
        // If same device found again, update the millis.
        for (uint32_t i = 0; i < deviceCount; i++) {
            BLEAdvertisedDevice device = foundDevices.getDevice(i);
            std::string key = device.getAddress().toString();
            m[key] = millis();
        }

        if (!m.empty()) {
            // Purge: remove any from the map with a millis more than 1000 millis old
            std::unordered_map<std::string, unsigned long>::iterator it;
            for (it = m.begin(); it != m.end();) {
                if (it->second < (millis() - scanInterval)) {
                    // Remove/Erase the item being iterated.
                    it = m.erase(it);
                } else {
                    ++it;
                }
            }
        }

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
