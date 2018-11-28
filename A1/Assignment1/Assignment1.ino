/*  Programmer: Francis Mendoza
 *  Assignment: A1
 *  Purpose: LED has varying brightness using serial input
 */
//-------------------------------------------------------------
String inData;          
  //Receive data to vary brightness
int led1 = D8;        
  //led1
//-------------------------------------------------------------
void setup() 
{
  // initialize serial:
  Serial.begin(115200);
  pinMode(led1, OUTPUT);
}
//-------------------------------------------------------------
void loop() 
{ 
    while (Serial.available() > 0)
    {
        char receivedCheck = Serial.read();
        inData += receivedCheck; 

        // Process message when new line character is recieved
        if (receivedCheck == '\n')
        {
          int inputVar = inData.toInt();

          Serial.print("Received Data: "  + inData); // Print input value
          
          int ledVal1 = map(inputVar, 0, 100, 0, 1023); // Constrain value of input to write to LED one

          Serial.print("Varying brightness level to: " + String(ledVal1) + "\n"); //Print brightness value
          
          analogWrite(led1, ledVal1); // Write to first LED
          
          inData = ""; // Clear recieved buffer
        }
    }
}
