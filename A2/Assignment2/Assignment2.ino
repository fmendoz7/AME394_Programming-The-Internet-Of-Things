/*  Programmer: Francis Mendoza
 *  Assignment: A2
 *  Purpose: LEDs light up like progress bar through potentiometer
 */

//LEDs
int led1 = D5;        // PWM PIN for LED 1
int led2 = D6;        // PWM PIN for LED 2
int led3 = D7;        // PWM PIN for LED 3
int led4 = D8;        // PWM PIN for LED 4
int potentiometer = A0;          // Input pin for potentiometer
//-------------------------------------------------------------------------------
// the setup routine runs once when you press reset:
void setup() 
{
  pinMode(potentiometer, INPUT); // Set potentiometer pin to input mode
 
  pinMode(led1, OUTPUT); // Set LED1 pin to output 
  pinMode(led2, OUTPUT); // Set LED2 pin to output 
  pinMode(led3, OUTPUT); // Set LED3 pin to output 
  pinMode(led4, OUTPUT); // Set LED4 pin to output 
}
//-------------------------------------------------------------------------------
// the loop routine runs over and over again forever:
void loop() 
{
  int ledVal1 = map(analogRead(potentiometer), 0, 256, 0, 1023); 
    // Potentiometer writes to led1, from 0 to 256
    
  int ledVal2 = map(analogRead(potentiometer), 256, 512, 0, 1023); 
    // Potentiometer writes to led2, from 256 to 512
    
  int ledVal3 = map(analogRead(potentiometer), 512, 768, 0, 1023); 
    // Potentiometer writes to led3, from 512 to 768
    
  int ledVal4 = map(analogRead(potentiometer), 768, 1024, 0, 1023); 
    // Potentiometer writes to led4, from 768 to 1024

  analogWrite(led1, ledVal1); //Write to first LED
  analogWrite(led2, ledVal2); //Write to second LED
  analogWrite(led3, ledVal3); //Write to third LED
  analogWrite(led4, ledVal4); //Write to fourth LED
//-------------------------------------------------------------------------------

  delay(10); //Slight delay
}

