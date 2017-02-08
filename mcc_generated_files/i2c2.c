/**
  MSSP2 Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    i2c2.c

  @Summary
    This is the generated header file for the MSSP2 driver using 
    MPLAB(c) Code Configurator

  @Description
    This header file provides APIs for driver for MSSP2.
    Generation Information :
        Product Revision  :  MPLAB(c) Code Configurator - 4.0
        Device            :  PIC16F18345
        Driver Version    :  2.00
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.35
        MPLAB 	          :  MPLAB X 3.40
*/

/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

#include "i2c2.h"

//write default slave address to EEPROM during programming, zeros for rest of
//function inputs
#define I2C2_SLAVE_ADDRESS_DEFAULT   0X08
#define I2C2_SLAVE_MASK    0x7F

typedef enum
{
    SLAVE_NORMAL_DATA,
    SLAVE_DATA_ADDRESS,
} SLAVE_WRITE_DATA_TYPE;

/**
 Section: Global Variables
*/

volatile uint8_t    I2C2_slaveWriteData      = 0x55;

/**
 Section: Local Functions
*/
void I2C2_StatusCallback(I2C2_SLAVE_DRIVER_STATUS i2c_bus_state);



/**
  Prototype:        void I2C2_Initialize(void)
  Input:            none
  Output:           none
  Description:      I2C2_Initialize is an
                    initialization routine that takes inputs from the GUI.
  Comment:          
  Usage:            I2C2_Initialize();

*/
void I2C2_Initialize(void)
{
    uint8_t i2c2SlaveAddress;
    // initialize the hardware
    // R_nW write_noTX; P stopbit_notdetected; S startbit_notdetected; BF RCinprocess_TXcomplete; SMP High Speed; UA dontupdate; CKE disabled; D_nA lastbyte_address; 
    SSP2STAT = 0x00;
    // SSPEN enabled; WCOL no_collision; CKP disabled; SSPM 7 Bit Polling; SSPOV no_overflow; 
    SSP2CON1 = 0x26;
    // ACKEN disabled; GCEN disabled; PEN disabled; ACKDT acknowledge; RSEN disabled; RCEN disabled; ACKSTAT received; SEN disabled; 
    SSP2CON2 = 0x00;
    // ACKTIM ackseq; SBCDE disabled; BOEN disabled; SCIE disabled; PCIE disabled; DHEN disabled; SDAHT 100ns; AHEN disabled; 
    SSP2CON3 = 0x00;
    // SSP2MSK 127; 
    SSP2MSK = (I2C2_SLAVE_MASK << 1);  // adjust UI mask for R/nW bit            
    // SSP2ADD read from EEPROM;     
    if(eeprom_read(0x00) == 1) i2c2SlaveAddress = eeprom_read(0x01);
    else i2c2SlaveAddress = I2C2_SLAVE_ADDRESS_DEFAULT;      
    SSP2ADD = (i2c2SlaveAddress << 1);  // adjust UI address for R/nW bit

    // clear the slave interrupt flag
    PIR2bits.SSP2IF = 0;
    // enable the master interrupt
    PIE2bits.SSP2IE = 1;

}

void I2C2_ISR ( void )
{
    uint8_t     i2c_data                = 0x55;


    // NOTE: The slave driver will always acknowledge
    //       any address match.

    PIR2bits.SSP2IF = 0;        // clear the slave interrupt flag
    i2c_data        = SSP2BUF;  // read SSPBUF to clear BF
    if(1 == SSP2STATbits.R_nW)
    {
        if((1 == SSP2STATbits.D_nA) && (1 == SSP2CON2bits.ACKSTAT))
        {
            // callback routine can perform any post-read processing
            I2C2_StatusCallback(I2C2_SLAVE_READ_COMPLETED);
        }
        else
        {
            // callback routine should write data into SSPBUF
            I2C2_StatusCallback(I2C2_SLAVE_READ_REQUEST);
        }
    }
    else if(0 == SSP2STATbits.D_nA)
    {
        // this is an I2C address

        // callback routine should prepare to receive data from the master
        I2C2_StatusCallback(I2C2_SLAVE_WRITE_REQUEST);
    }
    else
    {
        I2C2_slaveWriteData   = i2c_data;

        // callback routine should process I2C2_slaveWriteData from the master
        I2C2_StatusCallback(I2C2_SLAVE_WRITE_COMPLETED);
    }

    SSP2CON1bits.CKP    = 1;    // release SCL

} // end I2C2_ISR()



/**

    Example implementation of the callback

    This slave driver emulates an EEPROM Device.
    Sequential reads from the EEPROM will return data at the next
    EEPROM address.

    Random access reads can be performed by writing a single byte
    EEPROM address, followed by 1 or more reads.

    Random access writes can be performed by writing a single byte
    EEPROM address, followed by 1 or more writes.

    Every read or write will increment the internal EEPROM address.

    When the end of the EEPROM is reached, the EEPROM address will
    continue from the start of the EEPROM.
*/

void I2C2_StatusCallback(I2C2_SLAVE_DRIVER_STATUS i2c_bus_state)
{
    
    static uint8_t byteIndex        = 0;
    static uint8_t eepromAddress    = 0;
    static uint8_t slaveWriteType   = SLAVE_NORMAL_DATA;

    switch (i2c_bus_state)
    {
        case I2C2_SLAVE_WRITE_REQUEST:
            // the master will be sending RTD address next
            slaveWriteType  = SLAVE_DATA_ADDRESS;
            break;


        case I2C2_SLAVE_WRITE_COMPLETED:

            switch(slaveWriteType)
            {
                case SLAVE_DATA_ADDRESS:
                    eepromAddress   = I2C2_slaveWriteData;
                    break;

                case SLAVE_NORMAL_DATA:
                default:
                    switch(eepromAddress){
                        case 0x00:
                            gainValue = I2C2_slaveWriteData;
                            eepromAddress++;
                            setGain();
                            break;
                        case 0x01:
                            spsValue = I2C2_slaveWriteData;                            
                            setSPS();
                            break;
                        case 0x02:
                        case 0x03:
                        case 0x04:
                        case 0x05:
                            a_parameter.b[eepromAddress-2] = I2C2_slaveWriteData;
                            eepromAddress++;
                            break;
                        case 0x06:
                        case 0x07:
                        case 0x08:
                        case 0x09:
                            b_parameter.b[eepromAddress-6] = I2C2_slaveWriteData;
                            eepromAddress++;                            
                            break;
                        case 0x0A:
                            eeprom_write(0x00, 0X01);
                            eeprom_write(0x01, I2C2_slaveWriteData);
                            break;
                        default:
                            break;
                    } // end of switch(eepromAddress) for Write case
                    break;                   
                    
            } // end switch(slaveWriteType)           

            slaveWriteType  = SLAVE_NORMAL_DATA;
            break;

        case I2C2_SLAVE_READ_REQUEST:
            
            switch(eepromAddress){
                case 0x00:
                case 0x01:
                case 0x02:
                case 0x03:
                case 0x04:
                    
                    //Send temperature bytes back for requested RTD                                    
                    SSP2BUF = rtdBytes[eepromAddress][byteIndex];                
                    byteIndex++;                        
            
                    if(sizeof(rtdBytes[eepromAddress]) <= byteIndex){         
                        byteIndex = 0;    // reset byteIndex to zero            
                    }
                    break;
                    
                case 0x05:
                case 0x06:
                case 0x07:
                case 0x08:
                case 0x09:                                       
                    
                    SSP2BUF = rtdResistance.b[eepromAddress-5][byteIndex];                    
                    byteIndex++;
                    
                    if(sizeof(rtdResistance.b[eepromAddress]) <= byteIndex){
                        byteIndex = 0;
                    }
                    break;
                case 0x0A:
                case 0x0B:
                case 0x0C:
                case 0x0D:
                    //Send Temperature C back in 8bit pieces Note: not an option
                    //to send back icOffset here as it does not translate to a
                    //degree value in the same way since it's a differential number                   
                    SSP2BUF = rtdTemperatureC.b[eepromAddress-10][byteIndex];
                    byteIndex++;
                    
                    if(sizeof(rtdTemperatureC.b[eepromAddress]) <= byteIndex){
                        byteIndex = 0;
                    }
                    break;
                    
                case 0x0E:
                case 0x0F:
                case 0x10:
                case 0x11:
                    //Send Temperature F back in 8bit pieces Note: not an option
                    //to send back icOffset here as it does not translate to a
                    //degree value in the same way since it's a differential number                    
                    SSP2BUF = rtdTemperatureF.b[eepromAddress-14][byteIndex];
                    byteIndex++;
                    
                    if(sizeof(rtdTemperatureF.b[eepromAddress]) <= byteIndex){
                        byteIndex = 0;
                    }
                    break;
                    
                case 0x13:                    
                    initializeThreeWireRTD();
                    //send "don't care" bytes back once initialization complete
                    SSP2BUF = 0x0;
                    break;                   
                
                case 0x14:
                    performReset();
                    //send "don't care" bytes back once calibration complete
                    SSP2BUF = 0x0;
                    break;
            } //end of switch(eepromAddress) for Read case
            break;

        case I2C2_SLAVE_READ_COMPLETED:
        default:;

    } // end switch(i2c_bus_state)
}



