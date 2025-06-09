#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ArduinoOTA.h>

// Motor control pins
#define IN1 15 // D8 pin for motor A
#define IN2 13 // D7 pin for motor A
#define IN3 2  // D4 pin for motor B
#define IN4 0  // D3 pin for motor B
#define ENA 14  // D1 Enable pin for motor A (PWM)
#define ENB 12  // D2 Enable pin for motor B (PWM)

ESP8266WebServer server(80); // Web server on port 80

// WiFi credentials
const String STA_SSID = "Team8"; // Set your WiFi SSID
const String STA_PASSWORD = "1234"; // Set your WiFi password

String command = ""; // Command from the client
int SPEED = 1023;    // Default speed (adjustable between 330-1023)

// Function to initialize motors
void initMotors() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  analogWriteRange(1023); // Set PWM range for ESP8266

  // Stop motors initially
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);

  Serial.println("Motors initialized and stopped.");
}

// Function to move forward
void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, SPEED);
  analogWrite(ENB, SPEED);
  Serial.println("Moving forward at speed: " + String(SPEED));
}

// Function to move backward
void moveBackward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, SPEED);
  analogWrite(ENB, SPEED);
  Serial.println("Moving backward at speed: " + String(SPEED));
}

// Function to turn left
void turnLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, SPEED / 3);
  analogWrite(ENB, SPEED);
  Serial.println("Turning left at speed: " + String(SPEED));
}

// Function to turn right
void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, SPEED);
  analogWrite(ENB, SPEED / 3);
  Serial.println("Turning right at speed: " + String(SPEED));
}

// Function to stop the robot
void stopRobot() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  Serial.println("Robot stopped.");
}

// Handle HTTP requests
void handleRoot() {
  if (server.hasArg("State")) {
    command = server.arg("State");
    Serial.println("Command received: " + command);

    if (command == "F") moveForward();
    else if (command == "B") moveBackward();
    else if (command == "L") turnLeft();
    else if (command == "R") turnRight();
    else if (command == "0") { SPEED = 330; Serial.println("Speed set to 330"); }
    else if (command == "1") { SPEED = 400; Serial.println("Speed set to 400"); }
    else if (command == "2") { SPEED = 470; Serial.println("Speed set to 470"); }
    else if (command == "3") { SPEED = 540; Serial.println("Speed set to 540"); }
    else if (command == "4") { SPEED = 610; Serial.println("Speed set to 610"); }
    else if (command == "5") { SPEED = 680; Serial.println("Speed set to 680"); }
    else if (command == "6") { SPEED = 750; Serial.println("Speed set to 750"); }
    else if (command == "7") { SPEED = 820; Serial.println("Speed set to 820"); }
    else if (command == "8") { SPEED = 890; Serial.println("Speed set to 890"); }
    else if (command == "9") { SPEED = 960; Serial.println("Speed set to 960"); }
    else stopRobot();
  }
  server.send(200, "text/plain", "Command Received");
}

// Setup function
void setup() {
  Serial.begin(9600);
  Serial.println("WiFi Robot Remote Control");

  initMotors();

  String chipID = "wificar-" + String(ESP.getChipId(), HEX).substring(6);
  WiFi.mode(WIFI_STA);
  WiFi.begin(STA_SSID.c_str(), STA_PASSWORD.c_str());
  Serial.println("Connecting to WiFi...");

  unsigned long startMillis = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - startMillis < 10000) {
    delay(500);
    Serial.print(".");
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nConnected to WiFi");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
  } else {
    WiFi.mode(WIFI_AP);
    WiFi.softAP(chipID.c_str());
    Serial.println("\nFailed to connect to WiFi. AP Mode Enabled");
    Serial.print("AP IP Address: ");
    Serial.println(WiFi.softAPIP());
  }

  server.on("/", handleRoot);
  server.onNotFound(handleRoot);
  server.begin();

  ArduinoOTA.begin();
}

// Main loop
void loop() {
  ArduinoOTA.handle();
  server.handleClient();
}


