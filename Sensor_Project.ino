#include <Wire.h>// I2C library, required for MLX90614
#include <OneWire.h> //Library for waterproof sensor
#include <DallasTemperature.h> //Library for waterproof sensor
#include <SparkFunMLX90614.h> // SparkFunMLX90614 Arduino li

#define ONE_WIRE_BUS 2 // Data wire is plugged into pin 2 on the Arduino 

// Setup a oneWire instance to communicate with any OneWire devices  
// (not just Maxim/Dallas temperature ICs) 
OneWire oneWire(ONE_WIRE_BUS); 

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);


IRTherm therm; // Create an IRTherm object to interact with throughout



void setup() {
 Serial.begin(9600); 

 therm.begin(); // Initialize thermal IR sensor
 therm.setUnit(TEMP_C); // Set the library's units to Farenheit
  // Alternatively, TEMP_F can be replaced with TEMP_C for Celsius or
  // TEMP_K for Kelvin.
  
  
 sensors.begin(); 
}

void loop() {
   //Enter limits for clear and cloudy here in Celcius.   
    /*
     * 
     * 
     * 
     */
    float ClearLimit = 15;
    float CloudyLimit = 10;
    /*
     * 
     * 
     * 
     */
     //Do not change code under this line!

  
 if (therm.read()) // On success, read() will return 1, on fail 0.
  {
    Serial.print(String(therm.object(), 2)+",");
  
  }  
/********************************************************************/
 //Serial.print("Waterproof Sensor: "); 
 sensors.requestTemperatures(); // Send the command to get temperature readings 
/********************************************************************/
 //Serial.print("Waterproof Sensor: "); 
 Serial.print(String(sensors.getTempCByIndex(0)) + ",");

 Serial.print(sensors.getTempCByIndex(0)-therm.object()); //This the the difference of the 2 sensors
  Serial.print(",");
  Serial.print(ClearLimit);
  Serial.print(",");
  Serial.print(CloudyLimit);
   delay(600000); 
 Serial.println();

}
