/*
 * File:   ADS1220.c
 * Author: David W
 *
 * Created on November 6, 2016, 2:11 PM
 */


#include <xc.h>
#include "ADS1220.h"
#include "mcc_generated_files/mcc.h"

//performs chip reset
void performReset( void ){   
    
    SS_SetLow();
    __delay_us(5);
    
    garbage = SPI1_Exchange8bit(ADS1220_RESET);
    __delay_ms(1); //delay per datasheet
    
    __delay_us(5);
    SS_SetHigh();
}

void setGain( void ){
    //sets gain Register value based on user input gain value; called by i2c 
    //interrupt; this sets value but does not write to ADS1220 register
    
    switch(gainValue){
        case 0x01:
            gainRegisterValue = ADS1220_GAIN_1;
            break;
        case 0x02:
            gainRegisterValue = ADS1220_GAIN_2;
            break;
        case 0x04:
            gainRegisterValue = ADS1220_GAIN_4;
            break;
        case 0x08:
            gainRegisterValue = ADS1220_GAIN_8;
            break;
        case 0x10:
            gainRegisterValue = ADS1220_GAIN_16;
            break;
        case 0x20:
            gainRegisterValue = ADS1220_GAIN_32;
            break;
        case 0x40:
            gainRegisterValue = ADS1220_GAIN_64;
            break;
        case 0x80:
            gainRegisterValue = ADS1220_GAIN_128;
        default:
            gainRegisterValue = ADS1220_ERROR;
            //don't allow the program to proceed with an incorrect Gain value
            while(gainRegisterValue == ADS1220_ERROR);
            break;
    }
}

void setSPS( void ) {
    //sets sps Register value based on user input sps value; called by i2c
    //interrupt.  This sets value but does not write to ADS1220 register
    switch(spsValue){
        case 0x02:
            spsRegisterValue = ADS1220_SPS_20;
            break;
        case 0x04:           
            spsRegisterValue = ADS1220_SPS_40;
            break;
        case 0x09:
            spsRegisterValue = ADS1220_SPS_90;
            break;
        case 0x12:
            spsRegisterValue = ADS1220_SPS_180;
            break;
        case 0x23:
            spsRegisterValue = ADS1220_SPS_350;
            break;
        case 0x42:
            spsRegisterValue = ADS1220_SPS_660;
            break;
        case 0x78: 
            spsRegisterValue = ADS1220_SPS_1200;
            break;
        case 0xC8:
            spsRegisterValue = ADS1220_SPS_2000;
        default:
            spsRegisterValue = ADS1220_ERROR;
            //don't allow the program to proceed with an incorrect sps value
            while(spsRegisterValue == ADS1220_ERROR);
            break;
    }
}

//performs internal calibration of ADS1220
void performInternalOffset( void ){
    //performInternalOffset should only be called from within
    //initializeThreeWireRTD to ensure interrupts disabled for process
    //and to ensure proper RTD settings are put back in place for readings   
    
    //create local variables to read and sum data        
    uint32_t tempBit32;
    uint8_t numSamples = 8;
    
    offset32 = 0;       
    
    //Tell the chip to write to register and send 4 bytes
    garbage = SPI1_Exchange8bit(ADS1220_WRITE_REG);
    garbage = SPI1_Exchange8bit(gainRegisterValue | ADS1220_ICOFFSET_REG_0);
    garbage = SPI1_Exchange8bit(spsRegisterValue | ADS1220_3W_REG_1); //incorporate user set sps
    if(spsRegisterValue == 0x0) //if SPS of 20 used, enable 50&60HZ filter        
        garbage = SPI1_Exchange8bit(ADS1220_3W_REG_2_FLTR);
    else
        garbage = SPI1_Exchange8bit(ADS1220_3W_REG_2_NOFLTR);
    garbage = SPI1_Exchange8bit(ADS1220_3W_REG_3);
    //tell chip to start taking readings
    //garbage = SPI1_Exchange8bit(ADS1220_START);      
    
    
    //use for loop to collect average readings to use for rtdBytes[4]
    for (uint8_t i = 0; i < numSamples; i++){
        garbage = SPI1_Exchange8bit(ADS1220_START); //tell the chip to take a reading
        __delay_us(1);                 
    
        while(!PORTCbits.RC0 == 0); //wait for reading to be available
        tempBit32 = SPI1_Exchange8bit(0x0); //read byte0
        tempBit32 = (tempBit32 << 8) | SPI1_Exchange8bit(0x0); //read byte1
        tempBit32 = (tempBit32 << 8) | SPI1_Exchange8bit(0x0); //read byte2      
        
        //internal Offset could be negative; data sent as Twos Compliment so
        //bit shift answer left and then right to carry forward negative sign
        //if applicable
        tempBit32 = tempBit32 << 8;
        tempBit32 = tempBit32 >> 8;
        
        offset32 += tempBit32;        
                
    }  
       
    //average at end of for loop to minimize process effort
    //offset number small enough that for loop won't exceed 4 bytes
    offset32 /= numSamples;
    
    //transfer to the 8 bit array; only for users if they request.  Only 24bits
    //stored; offset32 used for internal PIC calculations
    rtdBytes[4][0] = (offset32 >> 16) & 0xff;
    rtdBytes[4][1] = (offset32 >> 8) & 0xff;
    rtdBytes[4][2] = offset32 & 0xff;        
    
}

//write settings to register for 3wire RTD
void initializeThreeWireRTD( void ){       
    
    INTCONbits.PEIE = 0;//turn off interrupts during initialization
    SS_SetLow(); //slave select pin low
    __delay_us(1);
    
    /*Current offset function does not work as implemented, need external voltage reference which 
    is not functional currently due to IC switch being closed; also need RTD connection in place
    to allow current path.  Due to these requirements, and the minimal impact this has to the reading
    accuracy, the performInternalOffset function is not used at this time*/
    //performInternalOffset();  
       
    //tell the chip to write to register and send 4 bytes for register settings
    garbage = SPI1_Exchange8bit(ADS1220_WRITE_REG);
    garbage = SPI1_Exchange8bit(gainRegisterValue | ADS1220_3W_REG_0); //incorporate user set gain
    garbage = SPI1_Exchange8bit(spsRegisterValue | ADS1220_3W_REG_1); //incorporate user set sps
    if(spsRegisterValue == ADS1220_SPS_20)
        garbage = SPI1_Exchange8bit(ADS1220_3W_REG_2_FLTR);
    else
        garbage = SPI1_Exchange8bit(ADS1220_3W_REG_2_NOFLTR);    
    garbage = SPI1_Exchange8bit(ADS1220_3W_REG_3);
    
    //tell the chip to start measuring temperatures
    //garbage = SPI1_Exchange8bit(ADS1220_START);
    
    __delay_us(1);
    SS_SetHigh();
    
    //upon first initialization, this will allow the main loop to start
    waitForRTDInitialization = false;
    INTCONbits.PEIE = 1; //turn interrupts back on
}
//reads temperatures from ADS1220
void readRTDBytes(uint8_t rtd){
        
    
    SS_SetLow();
    __delay_us(1);
    //start new reading
    garbage = SPI1_Exchange8bit(ADS1220_START);
    __delay_us(1);             
    
    while(!PORTCbits.RC0 == 0);
    
    INTCONbits.PEIE = 0;
    //garbage = SPI1_Exchange8bit(ADS1220_READ);
    //save temperature readings from ADS1220 chip to array
    rtdBytes[rtd][0] = SPI1_Exchange8bit(0x0); //read byte0
    rtdBytes[rtd][1] = SPI1_Exchange8bit(0x0); //read byte1
    rtdBytes[rtd][2] = SPI1_Exchange8bit(0x0); //read byte2
        
    //note that these numbers dont have icoffset subtracted from them
    INTCONbits.PEIE = 1;
    __delay_us(1);
    SS_SetHigh();   
    
        
}

void readRTDResistance(uint8_t rtd){
        
    uint32_t tempBit32;    
    
    if(rtd <4 ) //don't call readRTDBytes function if looking for Offset value
        readRTDBytes(rtd);
    
    tempBit32 = rtdBytes[rtd][0];
    tempBit32 = (tempBit32 << 8) | rtdBytes[rtd][1];
    tempBit32 = (tempBit32 << 8) | rtdBytes[rtd][2];
    
    //ADS1220 Output format is Binary Two's Compliment; RTD readings will always
    //be positive as voltage is always higher upstream of RTD; however icOffset
    //may be negative.  Ratio the input code read to 8,388,607 (7F FFFF in HEX)
    tempBit32 = tempBit32 << 8;
    tempBit32 = tempBit32 >> 8;
    
    if(rtd < 4)        
        tempBit32 -= offset32;            
    
    rtdResistance.f[rtd] = ((float)tempBit32 * 2 * (1000.0 * ADS1220_VREF)) / (ADS1220_FSR * gainValue);          
    
}

void readRTDTemperatureC(uint8_t rtd){ 
    
    readRTDResistance(rtd);
    //Using Callendar-Van Dusen formula
    //Formula also works for temperature <= 0C but error increases exponentially as temperature gets more negative.  
    //(Following Errors are from formula only and do not include other errors from sensor, etc) 
    //At -20C Error ~= 0.008C; At -50C Error ~= 0.01C;  At -75C Error ~= 0.08C; At -100C Error ~= 0.2C;   
    
    rtdTemperatureC.f[rtd] = (-1 * ADS1220_rZero * a_parameter.f + sqrt(
          pow(( ADS1220_rZero * a_parameter.f),2) - 4.0 * ADS1220_rZero * b_parameter.f * 
          (ADS1220_rZero - rtdResistance.f[rtd]))) / (2.0 * ADS1220_rZero *
          b_parameter.f);  
    
   
}

void readRTDTemperatureF(uint8_t rtd){    
    
    readRTDTemperatureC(rtd);
    rtdTemperatureF.f[rtd] = rtdTemperatureC.f[rtd] * (9.0 / 5.0) + 32;      
    
}
