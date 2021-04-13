#include <Arduino.h>
#include <SPI.h>
#include <RF24.h>
#include <Adafruit_FreeTouch.h>
#ifdef NEOPIX
#include <Adafruit_NeoPixel.h>
#endif

#ifdef NEOPIX
Adafruit_NeoPixel neoStrip(1, NEOPIX, NEO_GRB + NEO_KHZ800);
#endif

/****************** User Config ***************************/
/***      Set this radio as radio number 0 or 1         ***/
bool radioNumber = RADIO_NUM;

//TODO: set pins
/* Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 7 & 8 */
RF24 radio(RADIO_PORT_CE, RADIO_PORT_CS);

/**********************************************************/
byte addresses[][6] = {"1Node", "2Node"};
// Used to control whether this node is sending or receiving
bool role = 0;
bool isTransmitting = false;
constexpr int lastReceiptThresh = 200;
unsigned long lastReceipt = 0;

inline bool CheckTouchLeft();
inline bool CheckTouchRight();
void SendRF(bool, bool);
void ListenRF();
void SetLightState(bool);

void setup()
{
  Serial.begin(115200);
  Serial.println(F("RF24/examples/GettingStarted"));
  Serial.println(F("*** PRESS 'T' to begin transmitting to the other node"));

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(TOUCH_LEFT, INPUT);
  pinMode(TOUCH_RIGHT, INPUT);
  pinMode(VIBE_LEFT, OUTPUT);
  pinMode(VIBE_RIGHT, OUTPUT);
  digitalWrite(VIBE_LEFT, 0);
  digitalWrite(VIBE_RIGHT, 0);
#ifdef NEOPIX

  neoStrip.begin();
  neoStrip.setBrightness(150);
  neoStrip.show(); // Initialize all pixels to 'off'
#endif
#ifdef NEOPIX_QUIET
  digitalWrite(NEOPIX_QUIET, 0);
#endif

  radio.begin();

  // Set the PA Level low to prevent power supply related issues since this is a
  // getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.
  radio.setPALevel(RF24_PA_MAX);

  // Open a writing and reading pipe on each radio, with opposite addresses
  if (radioNumber)
  {
    radio.openWritingPipe(addresses[1]);
    radio.openReadingPipe(1, addresses[0]);
  }
  else
  {
    radio.openWritingPipe(addresses[0]);
    radio.openReadingPipe(1, addresses[1]);
  }

  // Start the radio listening for data
  radio.startListening();
}

void loop()
{
  /****************** Change Roles via Touch Commands ***************************/

  bool sendLeft = false, sendRight = false;

  sendLeft = CheckTouchLeft();
  sendRight = CheckTouchRight();

  role = sendLeft | sendRight;
  if (!isTransmitting && role)
  {
    radio.stopListening(); // First, stop listening so we can talk.
    isTransmitting = true;
  }
  else if (isTransmitting && !role)
  {
    SendRF(0, 0);
    radio.startListening(); // restart listener
    isTransmitting = false;
  }

  /****************** Ping Out Role ***************************/
  if (role == 1)
  {
    SendRF(sendLeft, sendRight);
  }

  /****************** Pong Back Role ***************************/
  if (role == 0)
  {
    ListenRF();
  }
}

bool CheckTouchLeft()
{
  bool x = (digitalRead(TOUCH_LEFT) == 1);
  if (x)
    Serial.println("left");
  return x;
}

bool CheckTouchRight()
{
  bool x = (digitalRead(TOUCH_RIGHT) == 1);
  if (x)
    Serial.println("right");
  return x;
}

void SendRF(bool sendLeft, bool sendRight)
{
  Serial.print(F("Sending - ["));
  Serial.print(sendLeft);
  Serial.print(F(", "));
  Serial.print(sendRight);
  Serial.print(F("]"));

  byte sendBuffer = (sendLeft * 0xF0) | (sendRight * 0x0F);

  Serial.println(sendBuffer, BIN);

  if (!radio.write(&sendBuffer, sizeof(byte)))
  {
    Serial.println(F("failed"));
  }
  delay(100);
}

void ListenRF()
{
  byte recvBuffer = 0;
  bool leftMotorOn = 0, rightMotorOn = 0;

  if (radio.available())
  {
    // Variable for the received timestamp
    while (radio.available())
    {                                        // While there is data ready
      radio.read(&recvBuffer, sizeof(byte)); // Get the payload
    }

    Serial.print(F("Receive - "));
    Serial.println(recvBuffer, BIN);

    leftMotorOn = ((recvBuffer & 0xF0) == 0xF0);
    rightMotorOn = ((recvBuffer & 0x0F) == 0x0F);

    digitalWrite(VIBE_LEFT, leftMotorOn);
    digitalWrite(VIBE_RIGHT, rightMotorOn);
    SetLightState(leftMotorOn | rightMotorOn);
    lastReceipt = millis();
  }

  if ((millis() - lastReceipt) > lastReceiptThresh)
  {
    digitalWrite(VIBE_LEFT, 0);
    digitalWrite(VIBE_RIGHT, 0);
    SetLightState(0);
  }
}

void SetLightState(bool isOn)
{
  digitalWrite(LED_BUILTIN, isOn);
#ifdef NEOPIX
  if (isOn)
  {
    neoStrip.setPixelColor(0, 255, 0, 0);
  }
  else
  {
    neoStrip.clear();
  }
  neoStrip.show();
#endif
}