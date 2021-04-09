#include <Arduino.h>
#include <SPI.h>
#include <RF24.h>
#include <Adafruit_FreeTouch.h>

//TODO: set pins
constexpr int qt_Thresh = 850;
Adafruit_FreeTouch touch_Left = Adafruit_FreeTouch(A0, OVERSAMPLE_4, RESISTOR_50K, FREQ_MODE_NONE);
Adafruit_FreeTouch touch_Right = Adafruit_FreeTouch(A1, OVERSAMPLE_4, RESISTOR_50K, FREQ_MODE_NONE);

//TODO: set pins
constexpr byte vibe_Left = A2;
constexpr byte vibe_Right = A3;

/****************** User Config ***************************/
/***      Set this radio as radio number 0 or 1         ***/
bool radioNumber = 0;

//TODO: set pins
/* Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 7 & 8 */
RF24 radio(7, 8);
/**********************************************************/
byte addresses[][6] = {"1Node", "2Node"};
// Used to control whether this node is sending or receiving
bool role = 0;
bool isTransmitting = false;

void setup()
{
  Serial.begin(115200);
  Serial.println(F("RF24/examples/GettingStarted"));
  Serial.println(F("*** PRESS 'T' to begin transmitting to the other node"));

  touch_Left.begin();
  touch_Right.begin();

  pinMode(vibe_Left, OUTPUT);
  pinMode(vibe_Right, OUTPUT);
  digitalWrite(vibe_Left, 0);
  digitalWrite(vibe_Right, 0);

  radio.begin();

  // Set the PA Level low to prevent power supply related issues since this is a
  // getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.
  radio.setPALevel(RF24_PA_LOW);

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

void SendRF(bool, bool);
void ListenRF();
void loop()
{
  /****************** Change Roles via Touch Commands ***************************/

  bool sendLeft = false, sendRight = false;

  sendLeft = touch_Left.measure() >= qt_Thresh;
  sendRight = touch_Right.measure() >= qt_Thresh;

  role = sendLeft | sendRight;
  if (!isTransmitting && role)
  {
    radio.stopListening(); // First, stop listening so we can talk.
    isTransmitting = true;
  }
  else if (isTransmitting && !role)
  {
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

  delay(10);
}

void SendRF(bool sendLeft, bool sendRight)
{
  Serial.println(F("Now sending"));

  unsigned short sendBuffer = ((sendLeft ? 'L' : 0) << 8) | (sendRight ? 'R' : 0);
  if (!radio.write(&sendBuffer, sizeof(unsigned short)))
  {
    Serial.println(F("failed"));
  }
}

void ListenRF()
{
  unsigned short recvBuffer = 0;
  bool leftMotorOn = 0, rightMotorOn = 0;

  if (radio.available())
  {
    // Variable for the received timestamp
    while (radio.available())
    {                                                  // While there is data ready
      radio.read(&recvBuffer, sizeof(unsigned short)); // Get the payload
    }

    leftMotorOn = (((recvBuffer & 0xFF00) ^ 'L') == 0);
    rightMotorOn = (((recvBuffer & 0x00FF) ^ 'R') == 0);

    digitalWrite(vibe_Left, leftMotorOn);
    digitalWrite(vibe_Right, rightMotorOn);
  }
}