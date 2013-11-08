/* 
###########################################################
  Title:       Arduino Uno 3V Oscilloscope
  Purpose:     Use a Nokia 5110 LCD screen with the arduino
  Created by:  Brian O'Dell from the Fileark Arduino Oscilloscope.
  Note:        Please reuse, repurpose, and redistribute this code.
  Note:        This code uses the Adafruit PDC8544 LCD library  
###########################################################
 */

#include "PCD8544.h"

// pin 2 - Serial clock out (SCLK)
// pin 3 - Serial data out (DIN)
// pin 5 - Data/Command select (D/C)
// pin 7 - LCD chip select (CS)
// pin 6 - LCD reset (RST)
PCD8544 nokia = PCD8544(2, 3, 5, 7, 6);

//Analog Pins
int channelAI = A0;      // probe
int delayAI = A1;       // delay potentiometer

float delayVariable = 0;
float scale = 0;
int xCounter = 0;
int yPosition = 0;
int readings[85];
int counter = 0;

void setup(void) 
{

  //Serial.begin(9600);
  nokia.init();
  
  // turn all the pixels on (a handy test)
    nokia.command(PCD8544_DISPLAYCONTROL | PCD8544_DISPLAYALLON);
    delay(500);
  // back to normal
    nokia.command(PCD8544_DISPLAYCONTROL | PCD8544_DISPLAYNORMAL);
  
    nokia.clear();
}

void loop() 
{  
  
  delayVariable = analogRead(delayAI);
  delayVariable = (delayVariable/10);
  scale = 47.0/1023.0; 
  
  //record readings
  for(xCounter = 0; xCounter < 85; xCounter += 1)
    {                                 
      yPosition = analogRead(channelAI);
      readings[xCounter] = (yPosition*scale);
      delay (delayVariable);
    }
  
  nokia.clear();

  //Draw Voltage Ref Lines
  nokia.drawline( 10, 0, 10, 47, BLACK);
  nokia.drawline( 5, 47-(.166 *1023.0 * scale), 10, 47-(.166 *1023.0 * scale), BLACK);
  nokia.drawline( 0, 47-(.33 *1023.0 * scale), 10, 47-(.33 *1023.0 * scale), BLACK);
  nokia.drawline( 5, 47-(.5 *1023.0 * scale), 10, 47-(.5 *1023.0 * scale), BLACK);
  nokia.drawline( 0, 47-(.66 *1023.0 * scale), 10, 47-(.66 *1023.0 * scale), BLACK);
  nokia.drawline( 5, 47-(.84 *1023.0 * scale), 10, 47-(.84 *1023.0 * scale), BLACK);

  for(xCounter = 0; xCounter < 85; xCounter += 1)
    {
       nokia.setPixel(xCounter, 47-readings[xCounter], BLACK);
       if(xCounter>1){
         nokia.drawline(xCounter-1, 47-readings[xCounter-1], xCounter, 47-readings[xCounter], BLACK);
       }
    }
  
  nokia.display();     
} 


