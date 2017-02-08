/**
  MSSP1 Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    spi1.c

  @Summary
    This is the generated driver implementation file for the MSSP1 driver using MPLAB(c) Code Configurator

  @Description
    This source file provides APIs for MSSP1.
    Generation Information :
        Product Revision  :  MPLAB(c) Code Configurator - 4.0
        Device            :  PIC16F18345
        Driver Version    :  2.00
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.35
        MPLAB             :  MPLAB X 3.40
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

/**
  Section: Included Files
*/

#include <xc.h>
#include "spi1.h"

/**
  Section: Macro Declarations
*/

#define SPI_RX_IN_PROGRESS 0x0

/**
  Section: Module APIs
*/

void SPI1_Initialize(void)
{
    // Set the SPI1 module to the options selected in the User Interface
    
    // R_nW write_noTX; P stopbit_notdetected; S startbit_notdetected; BF RCinprocess_TXcomplete; SMP Middle; UA dontupdate; CKE Idle to Active; D_nA lastbyte_address; 
    SSP1STAT = 0x00;
    
    // SSPEN enabled; WCOL no_collision; CKP Idle:Low, Active:High; SSPM FOSC/4_SSPxADD; SSPOV no_overflow; 
    SSP1CON1 = 0x2A;
    
    // SSP1ADD 1; 
    SSP1ADD = 0x01;
}

uint8_t SPI1_Exchange8bit(uint8_t data)
{
    // Clear the Write Collision flag, to allow writing
    SSP1CON1bits.WCOL = 0;

    SSP1BUF = data;

    while(SSP1STATbits.BF == SPI_RX_IN_PROGRESS)
    {
    }

    return (SSP1BUF);
}

/**
 End of File
*/