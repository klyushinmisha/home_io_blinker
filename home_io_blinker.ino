#include <Wire.h>

int SLAVE_ADDRESS = 0x04;
int ledPin = 13;
int analogPin = A0;

struct BlinkerState {
    bool enabled = true;
    int interval = 1000;
};

static BlinkerState state;

enum Command {
    ENABLE, DISABLE, SWITCH_INTERVAL
};

void setup() {
    pinMode(ledPin, OUTPUT);
    Wire.begin(SLAVE_ADDRESS);
    Wire.onReceive(handleReceive);
    Wire.onRequest(handleRequest);
}

void loop() {
    state.enabled = false;
    if (state.enabled) {
        digitalWrite(ledPin, HIGH);
        delay(state.interval);
        digitalWrite(ledPin, LOW);
        delay(state.interval);
    }
}

void handleReceive(int n) {
    byte command = Wire.read();
    switch (command) {
        case ENABLE:
            state.enabled = true;
            break;
        case DISABLE:
            state.enabled = false;
            break;
        case SWITCH_INTERVAL:
            state.interval = Wire.read();
            break;
        default:
            break;
    }
}

void handleRequest() {
    
}
