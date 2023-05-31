#include "mbed.h"
#include "UTFT_SPI.h"
#include "OV5642.h"
#include "OV5642_regs.h"
#include <stdio.h>
#include <string.h>



ArduCAM myCAM(p5, p6, p7, p25, p9, p10);
ArduLCD myGLCD(p5, p6, p7, p25);
RawSerial pc(USBTX, USBRX, 115200);

void setup();

int main() {
    pc.printf("\r\n\r\n- OV5642 Program Start -\r\n");
    pc.printf("ARDUCHIP_TRIG , SHUTTER_MASK : %x, %x\r\n", ARDUCHIP_TRIG , SHUTTER_MASK);

    // set up ov5642
    setup();

    // start capture
    uint8_t get_bit_temp;
    int timestamp = 0;
    myCAM.set_format(JPEG);
    myCAM.InitCAM();
    myCAM.OV5642_set_JPEG_size(OV5642_1920x1080);
    pc.printf(">> before start capture, myCAM.get_bit(ARDUCHIP_TRIG,VSYNC_MASK): %d\r\n", myCAM.get_bit(ARDUCHIP_TRIG,VSYNC_MASK));
    myCAM.start_capture();
    pc.printf(">> OV5642 Capture Start!\r\n"); 
    while(1){
        if(!myCAM.get_bit(ARDUCHIP_TRIG,VSYNC_MASK)){
            pc.printf("[ Picture Taken! ]\r\n");
            pc.printf(">> after capture taken, myCAM.get_bit(ARDUCHIP_TRIG,VSYNC_MASK): %d\r\n", myCAM.get_bit(ARDUCHIP_TRIG,VSYNC_MASK));
            pc.printf(">> time stamp: %d\r\n", timestamp);
            break;
        }
        timestamp++;
    }
}


void setup()
{
    uint8_t vid,pid,temp; 
    pc.printf("\r\n>> OV5642 Set-up Start!\r\n"); 

    uint8_t temp1,temp2;
    pc.printf(">> Send 0x55 and 0xAA to test resister\r\n");
    myCAM.write_reg(ARDUCHIP_TEST1, 0x55);         //Write to test1 register by 0x55
    myCAM.write_reg(ARDUCHIP_TEST2, 0xAA);         //Write to test2 register by 0xaa
    wait_ms(10);
    temp1 = myCAM.read_reg(ARDUCHIP_TEST1);                //Read from test1 register 
    temp2 = myCAM.read_reg(ARDUCHIP_TEST2);                //Read from test1 register
    pc.printf(">>>> temp1 : %x, temp2 : %x\r\n",temp1, temp2);

    wait_ms(10);

    myCAM.write_reg(ARDUCHIP_TEST1, 0x55);
    temp = myCAM.read_reg(ARDUCHIP_TEST1);
  
    if(temp != 0x55)
    {
        pc.printf("[ SPI interface Error! ]\r\n");
        while(1);
    }

    //Change MCU mode
    pc.printf(">> Change MCU mode\r\n");
    myCAM.set_mode(MCU2LCD_MODE);
    
    //Initialize the LCD Module
    pc.printf(">> Initialize the LCD Module\r\n");
    myGLCD.InitLCD();
    
    //Check if the camera module type is OV5642
    pc.printf(">> Check the camera module type\r\n");
    myCAM.rdSensorReg16_8(OV5642_CHIPID_HIGH, &vid);
    myCAM.rdSensorReg16_8(OV5642_CHIPID_LOW, &pid);
    if((vid != 0x56) || (pid != 0x42))
        pc.printf("Can't find OV5642 module!\r\n");
    else
        pc.printf(">>>> OV5642 detected\r\n");

    //Change to BMP capture mode and initialize the OV5642 module     
    myCAM.set_format(BMP);
    myCAM.InitCAM();
    pc.printf(">> OV5642 Set-up Done!\r\n\r\n");
}

