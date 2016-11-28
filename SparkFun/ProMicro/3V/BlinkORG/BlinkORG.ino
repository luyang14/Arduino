/* Pro Micro Test Code
   by: Nathan Seidle
   modified by: Jim Lindblom
   SparkFun Electronics
   date: September 16, 2013
   license: Public Domain - please use this code however you'd like.
   It's provided as a learning tool.

   This code is provided to show how to control the SparkFun
   ProMicro's TX and RX LEDs within a sketch. It also serves
   to explain the difference between Serial.print() and
   Serial1.print().
*/

int RXLED = 17;  // The RX LED has a defined Arduino pin
// The TX LED was not so lucky, we'll need to use pre-defined
// macros (TXLED1, TXLED0) to control that.
// (We could use the same macros for the RX LED too -- RXLED1,
//  and RXLED0.)

void setup()
{
  pinMode(RXLED, OUTPUT);  // Set RX LED as an output
  // TX LED is set as an output behind the scenes

  while (!Serial);
  Serial.begin(115200);
//  Serial.begin(115200); //This pipes to the serial monitor
//  Serial1.begin(115200); //This is the UART, pipes to sensors attached to board

  Serial.println("Start blink");
}

#define WM (1000/1)

void loop()
{
  Serial.println(WM);  // Print "Hello World" to the Serial Monitor
  // Serial1.println("Hello!");  // Print "Hello!" over hardware UART

  digitalWrite(RXLED, LOW);   // set the LED on
  TXLED0; //TX LED is not tied to a normally controlled pin
  delay(WM);              // wait for a second
  digitalWrite(RXLED, HIGH);    // set the LED off
  TXLED1;
  delay(WM);              // wait for a second
}
