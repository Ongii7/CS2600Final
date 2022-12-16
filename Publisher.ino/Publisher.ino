#include <ArduinoMqttClient.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <Keypad.h>

int latchPin = 2; //Pin connected to ST_CP of 74HC595 (Pin12)
int clockPin = 4; //Pin connected to SH_CP of 74HC595 (Pin11)
int dataPin = 15; //Pin connected to DS of 74HC595 (Pin14)

const char* ssid = "igloo3bro"; //your netword SSID (name)
const char* pass = "1357913579"; //network password (use for WPA, or use as key for WEP)

int ledBoard[] = {
  0x00, 0x40, 0x20, 0x0B, 0x60, 0x60, 0x60, 0x00
};

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

const char* broker = "192.168.1.194";
int        port     = 1883;
const char topic[]  = "game_start";
const char topic2[] = "TicTacToe";
const char topic3[] = "ESP32_input";

char keys[3][3] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'}
};

byte rowPins[3] = {14, 27, 26};
byte colPins[3] = {13, 21, 22};

Keypad myKeypad = Keypad(makeKeymap(keys), rowPins, colPins, 3, 3);
int keyPressed = myKeypad.getKey();

//set interval for sending messages (milliseconds)
const long interval = 8000;
unsigned long previousMillis = 0;

int count = 0;

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  //Initialize serial and wait for port to open:
  Serial.begin(115200);
  //set pins to output

  while (!Serial) {
    ; //wait for serial port to connect. Needed for native USB port only
  }

  //attempt to connect to Wifi network:
  Serial.print("\nAttempting to connect to WPA SSID: ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    // failed, retry
    Serial.print(".");
    delay(5000);
  }

  Serial.println("You're connected to the network");
  Serial.println();

  Serial.print("Attempting to connect to the MQTT broker: ");
  Serial.println(broker);

  if (!mqttClient.connect(broker, port)) {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());

    while (1);
  }

  Serial.println("You're connected to the MQTT broker!");
  Serial.println();

  // set the message receive callback
  mqttClient.onMessage(onMqttMessage);
  Serial.print("Subscribing to topic: ");
  Serial.println(topic2);
  Serial.println();
  // subscribe to a topic
  mqttClient.subscribe(topic2);
}
  
void loop() {
  int cols;
  //call poll() regularly to allow the library to send MQTT keep alive which
  //avoids being disconnected by the broker
  mqttClient.poll();

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    //save the last time a message was sent
    previousMillis = currentMillis;

    //record random value from A0, A1, and A2
    int gameStart = 1;

    Serial.print("Sending message to topic: ");
    Serial.println(topic);
    Serial.println(gameStart);
    delay(3000);

    Serial.print("Sending message to topic: ");
    Serial.println(topic3);
    Serial.println(keyPressed);

    //send message, the Print interface can be used to set the message contents
    mqttClient.beginMessage(topic);
    mqttClient.print(gameStart);
    mqttClient.endMessage();

    mqttClient.beginMessage(topic3);
    mqttClient.print(keyPressed);
    mqttClient.endMessage();

    Serial.println();
  }
}

void onMqttMessage(int messageSize) {
// we received a message, print out the topic and contents
Serial.println("Received a message with topic '");
Serial.print(mqttClient.messageTopic());
Serial.print("', length ");
Serial.print(messageSize);
Serial.println(" bytes:");

  // use the Stream interface to print the contents
  while (mqttClient.available()) {
    Serial.print((char)mqttClient.read());
  }
Serial.println();
Serial.println();
}
