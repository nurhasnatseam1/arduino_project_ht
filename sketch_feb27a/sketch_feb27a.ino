#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
#include <Adafruit_MLX90614.h>
#include <string.h>

#define I2C_SDA 21
#define I2C_SCL 22
#define REPORTING_PERIOD_MS 1000

uint8_t bm280_address = 0x76;
uint8_t max30100_address = 0x57;
uint8_t irmlx90614_address = 0x5A;
uint32_t tsLastReport = 0;
String heartRate ="";
String spO2 ="";

Adafruit_MLX90614 mlx = Adafruit_MLX90614();
PulseOximeter pox;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  pox.begin();
  Serial.println();
  
  while (!Serial);
  Serial.println("Adafruit MLX90614 test");
  if (!mlx.begin()) {
    Serial.println("Error connecting to MLX sensor. Check wiring.");
    while (1);
  };
  Serial.print("Emissivity = "); Serial.println(mlx.readEmissivity());
  Serial.println();
  }
void loop() {
  printFreq();
}

void printTemp(){
  Serial.print("Ambient= "); 
  Serial.print(mlx.readAmbientTempC()); 
  Serial.print("*C\nBody Temperature= "); 
  Serial.print(mlx.readObjectTempC()); 
  Serial.println("*C");
  }

void printFreq(){
    pox.update();
    if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
    heartRate=pox.getHeartRate();
    spO2=pox.getSpO2();
    Serial.print("Heart rate:");
    Serial.print(heartRate);
    Serial.print("bpm / SpO2:");
    Serial.print(spO2);
    Serial.println("%");
    Serial.println();
    printTemp();

    /*
    undoing the stored value
    */
    heartRate="";
    spO2="";
    tsLastReport = millis();
  }
}
