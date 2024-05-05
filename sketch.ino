#include <Arduino.h>

float slope = 0.5;
float intercept = 10;

const int ledPinIncrease = 9;
const int ledPinDecrease = 10;

const float learningRate = 0.01;

const float tempThresholdLow = 18.0;
const float tempThresholdHigh = 20.0;

const float tempData[] = {
    18, 17.9, 17.9, 18.1, 18, 17.9, 17.9, 18.4, 18.6, 19.3, 20.9, 20.9, 20.8, 20.5, 20.6, 20.9, 20.2, 19.6, 18.9, 19.2, 19.3, 19.1, 19, 18.6,
    18.7, 18.7, 18.5, 18.4, 18.2, 18.1, 17.9, 18.1, 17.8, 18.1, 18.2, 18.4, 18.6, 18.5, 18.7, 19.6, 19.4, 18.5, 17.9, 17.9, 18.1, 17.8, 17.5,
    17.1, 16.9, 16.8, 16.7, 16.7, 16.7, 16.6, 16.6, 16.4, 17.2, 18.4, 18.5, 19.3, 18.9, 18.7, 18.3, 17.8, 16.8, 16, 15.7, 15.5, 15.3, 15.4, 
    15.4, 15.2, 15.1, 15.1, 15.1, 14.9, 14.9, 15.1, 15, 15.1, 15.9, 16.9, 17.6, 17.8, 19.2, 20.2, 19.9, 19.1, 18.4, 17.4, 16.8, 16.8, 17.5, 
    17.3, 16.8, 17, 16.9, 16.5, 16.2, 15.9, 15.8, 15.9, 16.4, 16.6, 18, 19.8, 21.4, 22.8, 22.6, 22.7, 21.7, 21.4, 20.5, 19.4, 18.3, 17.9, 
    18.6, 18.6, 18.4, 18.5, 18.3, 18, 18.1, 18.1, 18, 17.9, 17.7, 17.6, 17.9, 18.3, 18.8, 19.1, 19.6, 19.3, 19.3, 18.7, 18.1, 17.3, 16.7, 
    16.2, 16.2, 16, 16, 15.9, 15.7, 15.5, 15.4, 15.4, 15.5, 15.6, 15.6, 16.8, 18.2, 19.1, 20, 20.9, 21.3, 21.1, 20.2, 18.6, 17.4, 16.5, 16.2,
    16.2, 16.1, 15.8, 15.6, 14.5, 15.2, 14.3, 14.8, 13.2, 12.8, 13, 13.7, 16, 18.4, 20.6, 22.2, 22.9, 23.3, 23.5, 23.2, 22.3, 20.5, 17.7, 18.9,
    17.6, 17.4, 17.3, 16.8, 17.7, 16.6, 16.1, 16.6, 16.8, 16.1, 15.2, 15.2, 18.3, 19.5, 20.5, 21.5, 22.0};

const int tempDataSize = sizeof(tempData) / sizeof(tempData[0]);

float predictTemperature(float currentTemp) {
    return slope * currentTemp + intercept;
}

void updateModel(float currentTemp, float actualNextTemp) {
    float error = actualNextTemp - predictTemperature(currentTemp);
    intercept += learningRate * error;
}

void setup() {
    pinMode(ledPinIncrease, OUTPUT);
    pinMode(ledPinDecrease, OUTPUT);
    Serial.begin(9600);
}

void loop() {
    static int dataIndex = 0;

    if (dataIndex >= tempDataSize) {
        Serial.println("End of data.");
        while (true);
    }

    float currentTemp = tempData[dataIndex];
    float actualNextTemp = currentTemp + random(-2, 3);
    float predictedTemp = predictTemperature(currentTemp);
    updateModel(currentTemp, actualNextTemp);

    Serial.print("Current Temperature: ");
    Serial.print(currentTemp);
    Serial.print("°C, Predicted Next Temperature: ");
    Serial.print(predictedTemp);
    Serial.print("°C, Actual Next Temperature: ");
    Serial.println(actualNextTemp);
    Serial.print("Updated Intercept: ");
    Serial.println(intercept);

    digitalWrite(ledPinIncrease, LOW);
    digitalWrite(ledPinDecrease, LOW);
    if (predictedTemp < tempThresholdLow) {
        digitalWrite(ledPinIncrease, HIGH);
    } else if (predictedTemp > tempThresholdHigh) {
        digitalWrite(ledPinDecrease, HIGH);
    }

    dataIndex++;
    delay(1000);
}
