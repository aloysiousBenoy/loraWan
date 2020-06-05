/*

LoRa Wan Arduino library for WIR-1286 based on the SX-1276 chip.
Implemets various methods to operate and configure the module via the serial ports on an arduino.


Author : Aloysious Benoy
Date : To be completed
v0.1

*/
#include "Arduino.h"
// #include <Serial.h>
#include "loraWan.h"
// lora_wan constructor for starting the communication with the LoRa module.
// The Default baud rate for normal serial communication for this specific module is 115200 bauds. This may change depending your module.
// Default pins are used when the arduino is connected to the hardware serial ports. This is included here with plans to use software serial in the future.
loraWan::loraWan(int CTS, int PROG, int TX = 1, int RX = 0, long baud = 115200, long t_baud=9600) 
{
    PROG_PIN = PROG;  // Program mode pin
    CTS_PIN = CTS;   // Clear to Send pin
    TX_PIN = TX;
    RX_PIN = RX;   
    BAUD = baud;  // Baud rate for program mode serial port 
    t_BAUD=t_baud;  // setting baud rate for normal radio communication
    GATEWAY= false;               // Set as node by default 
    digitalWrite(PROG_PIN, HIGH); // Disables program mode on startup - active low
           
}

// progMode function for putting the LoRa module to program mode or AT mode.
// This mode allows us to edit various settings and configure the LoRa module for various modes of operation.
// program mode is set by pulling the PROG_PIN low (as specified in the module docs).
// You need to invoke this function before you can set various module parameters such as node address, destination , power, baud etc....

void loraWan::progMode()
{

   if(Serial){
    Serial.end(); // Closes already active serial port 
    }           
    Serial.begin(BAUD);     // Opens serial port with the LoRa Module connected on the  specified pin
    digitalWrite(PROG_PIN, LOW); // active low
}

//  progModeDis function for disbling the program mode. Call this function once you are done with setting various module parameters.

void loraWan::progModeDis(){

    Serial.print("X\r\n");   // Exit program mode. Retains all configurations.
    digitalWrite(PROG_PIN,HIGH);
    Serial.end();  // End Serial port for program mode
    Serial.begin(t_BAUD);     // Restart serial port for normal communication.
}


//  set Destination node address. Call function with destination id 
// Destination ID is accepted as a 16-bit integer(default int size in most arduino boards), as the id is a 16 bit number.

void loraWan::setDestination(int destinationID){
    progMode();

    Serial.print("D=");
    Serial.print(destinationID,HEX);
    Serial.print("\r\n");

    progModeDis();

}


// set network Id. This function helps to set network id of the transmitting device

void loraWan::setNetworkID(int networkID){
    progMode();
    
    Serial.print("N=");
    Serial.print(networkID,HEX);
    Serial.print("\r\n");


    progModeDis();
}


// Controller setup. This Function helps to set a module as the transmitting controller. This sets the network id to 0.

void loraWan::setGateway(){
    progMode();
    
    GATEWAY=true;
    setNetworkID(0x0000);
    
    progModeDis();
}

