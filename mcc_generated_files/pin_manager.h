/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using MPLAB(c) Code Configurator

  @Description:
    This header file provides implementations for pin APIs for all pins selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB(c) Code Configurator - 4.0
        Device            :  PIC16F18345
        Version           :  1.01
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.35
        MPLAB             :  MPLAB X 3.40

    Copyright (c) 2013 - 2015 released Microchip Technology Inc.  All rights reserved.

    Microchip licenses to you the right to use, modify, copy and distribute
    Software only when embedded on a Microchip microcontroller or digital signal
    controller that is integrated into your product or third party product
    (pursuant to the sublicense terms in the accompanying license agreement).

    You should refer to the license agreement accompanying this Software for
    additional information regarding your rights and obligations.

    SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
    EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
    MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
    IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
    CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
    OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
    INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
    CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
    SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
    (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.

*/


#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set ICSPDAT aliases
#define ICSPDAT_TRIS               TRISAbits.TRISA0
#define ICSPDAT_LAT                LATAbits.LATA0
#define ICSPDAT_PORT               PORTAbits.RA0
#define ICSPDAT_WPU                WPUAbits.WPUA0
#define ICSPDAT_OD                ODCONAbits.ODCA0
#define ICSPDAT_ANS                ANSELAbits.ANSA0
#define ICSPDAT_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define ICSPDAT_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define ICSPDAT_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define ICSPDAT_GetValue()           PORTAbits.RA0
#define ICSPDAT_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define ICSPDAT_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define ICSPDAT_SetPullup()      do { WPUAbits.WPUA0 = 1; } while(0)
#define ICSPDAT_ResetPullup()    do { WPUAbits.WPUA0 = 0; } while(0)
#define ICSPDAT_SetPushPull()    do { ODCONAbits.ODCA0 = 1; } while(0)
#define ICSPDAT_SetOpenDrain()   do { ODCONAbits.ODCA0 = 0; } while(0)
#define ICSPDAT_SetAnalogMode()  do { ANSELAbits.ANSA0 = 1; } while(0)
#define ICSPDAT_SetDigitalMode() do { ANSELAbits.ANSA0 = 0; } while(0)

// get/set ICSPCLK aliases
#define ICSPCLK_TRIS               TRISAbits.TRISA1
#define ICSPCLK_LAT                LATAbits.LATA1
#define ICSPCLK_PORT               PORTAbits.RA1
#define ICSPCLK_WPU                WPUAbits.WPUA1
#define ICSPCLK_OD                ODCONAbits.ODCA1
#define ICSPCLK_ANS                ANSELAbits.ANSA1
#define ICSPCLK_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define ICSPCLK_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define ICSPCLK_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define ICSPCLK_GetValue()           PORTAbits.RA1
#define ICSPCLK_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define ICSPCLK_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define ICSPCLK_SetPullup()      do { WPUAbits.WPUA1 = 1; } while(0)
#define ICSPCLK_ResetPullup()    do { WPUAbits.WPUA1 = 0; } while(0)
#define ICSPCLK_SetPushPull()    do { ODCONAbits.ODCA1 = 1; } while(0)
#define ICSPCLK_SetOpenDrain()   do { ODCONAbits.ODCA1 = 0; } while(0)
#define ICSPCLK_SetAnalogMode()  do { ANSELAbits.ANSA1 = 1; } while(0)
#define ICSPCLK_SetDigitalMode() do { ANSELAbits.ANSA1 = 0; } while(0)

// get/set RB5 procedures
#define RB5_SetHigh()    do { LATBbits.LATB5 = 1; } while(0)
#define RB5_SetLow()   do { LATBbits.LATB5 = 0; } while(0)
#define RB5_Toggle()   do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
#define RB5_GetValue()         PORTBbits.RB5
#define RB5_SetDigitalInput()   do { TRISBbits.TRISB5 = 1; } while(0)
#define RB5_SetDigitalOutput()  do { TRISBbits.TRISB5 = 0; } while(0)
#define RB5_SetPullup()     do { WPUBbits.WPUB5 = 1; } while(0)
#define RB5_ResetPullup()   do { WPUBbits.WPUB5 = 0; } while(0)
#define RB5_SetAnalogMode() do { ANSELBbits.ANSB5 = 1; } while(0)
#define RB5_SetDigitalMode()do { ANSELBbits.ANSB5 = 0; } while(0)

// get/set RB6 procedures
#define RB6_SetHigh()    do { LATBbits.LATB6 = 1; } while(0)
#define RB6_SetLow()   do { LATBbits.LATB6 = 0; } while(0)
#define RB6_Toggle()   do { LATBbits.LATB6 = ~LATBbits.LATB6; } while(0)
#define RB6_GetValue()         PORTBbits.RB6
#define RB6_SetDigitalInput()   do { TRISBbits.TRISB6 = 1; } while(0)
#define RB6_SetDigitalOutput()  do { TRISBbits.TRISB6 = 0; } while(0)
#define RB6_SetPullup()     do { WPUBbits.WPUB6 = 1; } while(0)
#define RB6_ResetPullup()   do { WPUBbits.WPUB6 = 0; } while(0)
#define RB6_SetAnalogMode() do { ANSELBbits.ANSB6 = 1; } while(0)
#define RB6_SetDigitalMode()do { ANSELBbits.ANSB6 = 0; } while(0)

// get/set RB7 procedures
#define RB7_SetHigh()    do { LATBbits.LATB7 = 1; } while(0)
#define RB7_SetLow()   do { LATBbits.LATB7 = 0; } while(0)
#define RB7_Toggle()   do { LATBbits.LATB7 = ~LATBbits.LATB7; } while(0)
#define RB7_GetValue()         PORTBbits.RB7
#define RB7_SetDigitalInput()   do { TRISBbits.TRISB7 = 1; } while(0)
#define RB7_SetDigitalOutput()  do { TRISBbits.TRISB7 = 0; } while(0)
#define RB7_SetPullup()     do { WPUBbits.WPUB7 = 1; } while(0)
#define RB7_ResetPullup()   do { WPUBbits.WPUB7 = 0; } while(0)
#define RB7_SetAnalogMode() do { ANSELBbits.ANSB7 = 1; } while(0)
#define RB7_SetDigitalMode()do { ANSELBbits.ANSB7 = 0; } while(0)

// get/set DRDY aliases
#define DRDY_TRIS               TRISCbits.TRISC0
#define DRDY_LAT                LATCbits.LATC0
#define DRDY_PORT               PORTCbits.RC0
#define DRDY_WPU                WPUCbits.WPUC0
#define DRDY_OD                ODCONCbits.ODCC0
#define DRDY_ANS                ANSELCbits.ANSC0
#define DRDY_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define DRDY_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define DRDY_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define DRDY_GetValue()           PORTCbits.RC0
#define DRDY_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define DRDY_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)
#define DRDY_SetPullup()      do { WPUCbits.WPUC0 = 1; } while(0)
#define DRDY_ResetPullup()    do { WPUCbits.WPUC0 = 0; } while(0)
#define DRDY_SetPushPull()    do { ODCONCbits.ODCC0 = 1; } while(0)
#define DRDY_SetOpenDrain()   do { ODCONCbits.ODCC0 = 0; } while(0)
#define DRDY_SetAnalogMode()  do { ANSELCbits.ANSC0 = 1; } while(0)
#define DRDY_SetDigitalMode() do { ANSELCbits.ANSC0 = 0; } while(0)

// get/set RC1 procedures
#define RC1_SetHigh()    do { LATCbits.LATC1 = 1; } while(0)
#define RC1_SetLow()   do { LATCbits.LATC1 = 0; } while(0)
#define RC1_Toggle()   do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define RC1_GetValue()         PORTCbits.RC1
#define RC1_SetDigitalInput()   do { TRISCbits.TRISC1 = 1; } while(0)
#define RC1_SetDigitalOutput()  do { TRISCbits.TRISC1 = 0; } while(0)
#define RC1_SetPullup()     do { WPUCbits.WPUC1 = 1; } while(0)
#define RC1_ResetPullup()   do { WPUCbits.WPUC1 = 0; } while(0)
#define RC1_SetAnalogMode() do { ANSELCbits.ANSC1 = 1; } while(0)
#define RC1_SetDigitalMode()do { ANSELCbits.ANSC1 = 0; } while(0)

// get/set RC2 procedures
#define RC2_SetHigh()    do { LATCbits.LATC2 = 1; } while(0)
#define RC2_SetLow()   do { LATCbits.LATC2 = 0; } while(0)
#define RC2_Toggle()   do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define RC2_GetValue()         PORTCbits.RC2
#define RC2_SetDigitalInput()   do { TRISCbits.TRISC2 = 1; } while(0)
#define RC2_SetDigitalOutput()  do { TRISCbits.TRISC2 = 0; } while(0)
#define RC2_SetPullup()     do { WPUCbits.WPUC2 = 1; } while(0)
#define RC2_ResetPullup()   do { WPUCbits.WPUC2 = 0; } while(0)
#define RC2_SetAnalogMode() do { ANSELCbits.ANSC2 = 1; } while(0)
#define RC2_SetDigitalMode()do { ANSELCbits.ANSC2 = 0; } while(0)

// get/set SWITCH_A aliases
#define SWITCH_A_TRIS               TRISCbits.TRISC3
#define SWITCH_A_LAT                LATCbits.LATC3
#define SWITCH_A_PORT               PORTCbits.RC3
#define SWITCH_A_WPU                WPUCbits.WPUC3
#define SWITCH_A_OD                ODCONCbits.ODCC3
#define SWITCH_A_ANS                ANSELCbits.ANSC3
#define SWITCH_A_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define SWITCH_A_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define SWITCH_A_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define SWITCH_A_GetValue()           PORTCbits.RC3
#define SWITCH_A_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define SWITCH_A_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define SWITCH_A_SetPullup()      do { WPUCbits.WPUC3 = 1; } while(0)
#define SWITCH_A_ResetPullup()    do { WPUCbits.WPUC3 = 0; } while(0)
#define SWITCH_A_SetPushPull()    do { ODCONCbits.ODCC3 = 1; } while(0)
#define SWITCH_A_SetOpenDrain()   do { ODCONCbits.ODCC3 = 0; } while(0)
#define SWITCH_A_SetAnalogMode()  do { ANSELCbits.ANSC3 = 1; } while(0)
#define SWITCH_A_SetDigitalMode() do { ANSELCbits.ANSC3 = 0; } while(0)

// get/set SWITCH_B aliases
#define SWITCH_B_TRIS               TRISCbits.TRISC6
#define SWITCH_B_LAT                LATCbits.LATC6
#define SWITCH_B_PORT               PORTCbits.RC6
#define SWITCH_B_WPU                WPUCbits.WPUC6
#define SWITCH_B_OD                ODCONCbits.ODCC6
#define SWITCH_B_ANS                ANSELCbits.ANSC6
#define SWITCH_B_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define SWITCH_B_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define SWITCH_B_Toggle()             do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define SWITCH_B_GetValue()           PORTCbits.RC6
#define SWITCH_B_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define SWITCH_B_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)
#define SWITCH_B_SetPullup()      do { WPUCbits.WPUC6 = 1; } while(0)
#define SWITCH_B_ResetPullup()    do { WPUCbits.WPUC6 = 0; } while(0)
#define SWITCH_B_SetPushPull()    do { ODCONCbits.ODCC6 = 1; } while(0)
#define SWITCH_B_SetOpenDrain()   do { ODCONCbits.ODCC6 = 0; } while(0)
#define SWITCH_B_SetAnalogMode()  do { ANSELCbits.ANSC6 = 1; } while(0)
#define SWITCH_B_SetDigitalMode() do { ANSELCbits.ANSC6 = 0; } while(0)

// get/set SS aliases
#define SS_TRIS               TRISCbits.TRISC7
#define SS_LAT                LATCbits.LATC7
#define SS_PORT               PORTCbits.RC7
#define SS_WPU                WPUCbits.WPUC7
#define SS_OD                ODCONCbits.ODCC7
#define SS_ANS                ANSELCbits.ANSC7
#define SS_SetHigh()            do { LATCbits.LATC7 = 1; } while(0)
#define SS_SetLow()             do { LATCbits.LATC7 = 0; } while(0)
#define SS_Toggle()             do { LATCbits.LATC7 = ~LATCbits.LATC7; } while(0)
#define SS_GetValue()           PORTCbits.RC7
#define SS_SetDigitalInput()    do { TRISCbits.TRISC7 = 1; } while(0)
#define SS_SetDigitalOutput()   do { TRISCbits.TRISC7 = 0; } while(0)
#define SS_SetPullup()      do { WPUCbits.WPUC7 = 1; } while(0)
#define SS_ResetPullup()    do { WPUCbits.WPUC7 = 0; } while(0)
#define SS_SetPushPull()    do { ODCONCbits.ODCC7 = 1; } while(0)
#define SS_SetOpenDrain()   do { ODCONCbits.ODCC7 = 0; } while(0)
#define SS_SetAnalogMode()  do { ANSELCbits.ANSC7 = 1; } while(0)
#define SS_SetDigitalMode() do { ANSELCbits.ANSC7 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/