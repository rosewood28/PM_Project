#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

WiFiClient wifiClient;

const char* ssid = "MyAp"; // WiFI ssid (Service Set Identifier)
const char* password = "hhrz2108"; // WiFi password

boolean INPUT_state; // variable to store the state received
boolean last_INPUT_state = LOW;
int INPUT_from_UNO = 5; //INPUT GPIO 5 (D1_R1 pin D1) connected to PD4 of Arduino  

void setup () {

  WiFi.begin(ssid, password);
  Serial.begin(115200);
  Serial.println();
  Serial.println("SETUP()");
  Serial.setDebugOutput(true);
  //Serial.setDebugOutput(false);

  // Wait until the ESP is connected to Wifi
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
  }

  pinMode(INPUT_from_UNO, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
 
  digitalWrite(LED_BUILTIN, LOW);
  delay(100);
  digitalWrite(LED_BUILTIN, HIGH);
 
}
 
void loop()
{ 
  INPUT_state = digitalRead(INPUT_from_UNO);  //HIGH when sensors are blocked, else LOW

  // Check if the input state changes
  if (INPUT_state != last_INPUT_state)
  {

    // Turn on wemos D1 mini LED to indicate sending the request
    digitalWrite(LED_BUILTIN, LOW);
    delay(300);
    digitalWrite(LED_BUILTIN, HIGH);

    // Check WiFi connection status
    if (WiFi.status() == WL_CONNECTED)
    {
      // Declare an object of class HTTPClient
      HTTPClient http;

      if (INPUT_state == 1) {
        Serial.println("Garaj Blocat");
        // Request link obtained from IFTTT
        http.begin(wifiClient, "http://maker.ifttt.com/trigger/Iot_Event_01/json/with/key/d9_GAL4FyMF6zFmsWdnwg7");
      } else {
        Serial.println("Garaj Liber");
        // Request link obtained from IFTTT
        http.begin(wifiClient, "http://maker.ifttt.com/trigger/Iot_Event_02/json/with/key/d9_GAL4FyMF6zFmsWdnwg7");
      }
      
      // Send the request
      http.GET();

      // Close connection
      http.end();
    }
    last_INPUT_state = INPUT_state;
  }
}
