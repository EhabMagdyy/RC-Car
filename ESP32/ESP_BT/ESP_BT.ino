/*****************************************************************************************************************************
**********************************    Author  : Ehab Magdy Abdullah                      *************************************
**********************************    Linkedin: https://www.linkedin.com/in/ehabmagdyy/  *************************************
**********************************    Youtube : https://www.youtube.com/@EhabMagdyy      *************************************
******************************************************************************************************************************/

#include "BluetoothSerial.h"

#define RXp2    16
#define TXp2    17

char bt_value = 0;

String device_name = "ESP32-BT";

BluetoothSerial SerialBT;

void setup() 
{
  SerialBT.begin(device_name); 
  Serial2.begin(115200, SERIAL_8N1, RXp2, TXp2);
}

void loop() 
{
  if (SerialBT.available()) 
  {
    bt_value = SerialBT.read();
  }
  
  if((bt_value >= '1' && bt_value <= '4') || (bt_value >= 'A' && bt_value <= 'Z'))
  {
      Serial2.write(bt_value);
  }
}
