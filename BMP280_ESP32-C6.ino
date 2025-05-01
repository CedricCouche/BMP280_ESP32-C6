#include <Wire.h>
#include <Adafruit_BMP280.h>

// Create an instance of the sensor
Adafruit_BMP280 bmp;

// I2C pins for ESP32-C6
#define SDA_PIN 5  // GPIO5 for SDA
#define SCL_PIN 6  // GPIO6 for SCL

// Common BMP280 addresses
#define BMP280_ADDRESS_1 0x76
#define BMP280_ADDRESS_2 0x77

void setup() {
  // Initialize serial communication
  Serial.begin(115200);
  
  // Wait for serial monitor to open
  while(!Serial) {
    delay(10);
  }
  
  Serial.println("BMP280 Sensor Test with Auto Address Detection");
  
  // Initialize I2C with custom pins
  Wire.begin(SDA_PIN, SCL_PIN);
  
  // Try to initialize with the first common address
  if (bmp.begin(BMP280_ADDRESS_1)) {
    Serial.println("BMP280 sensor found at address 0x76!");
  }
  // If that fails, try the second common address
  else if (bmp.begin(BMP280_ADDRESS_2)) {
    Serial.println("BMP280 sensor found at address 0x77!");
  }
  // If both fail, display an error
  else {
    Serial.println("Could not find a valid BMP280 sensor!");
    Serial.println("Check your wiring or try running the I2C scanner.");
    while (1) delay(10);
  }
  
  // Default settings from datasheet
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     // Operating Mode
                  Adafruit_BMP280::SAMPLING_X2,     // Temp. oversampling
                  Adafruit_BMP280::SAMPLING_X16,    // Pressure oversampling
                  Adafruit_BMP280::FILTER_X16,      // Filtering
                  Adafruit_BMP280::STANDBY_MS_500); // Standby time
}

void loop() {
  // Read temperature in Celsius
  float temperature = bmp.readTemperature();
  
  // Read pressure in hPa (hectopascals)
  float pressure = bmp.readPressure() / 100.0F;
  
  // Calculate altitude (using standard sea-level pressure)
  float altitude = bmp.readAltitude(1013.25);
  
  // Print readings to serial monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");
  
  Serial.print("Pressure: ");
  Serial.print(pressure);
  Serial.println(" hPa");
  
  Serial.print("Approx. Altitude: ");
  Serial.print(altitude);
  Serial.println(" m");
  
  Serial.println();
  
  // Wait 2 seconds before next reading
  delay(2000);
}