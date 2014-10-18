// ******************************************************************************************* //
// Include file for PIC24FJ64GA002 microcontroller. This include file defines
// MACROS for special function registers (SFR) and control bits within those
// registers.

#include "p24fj64ga002.h"
#include <stdio.h>
#include "lcd.h"
#include "keypad.h"

// ******************************************************************************************* //
// Configuration bits for CONFIG1 settings. 
//
// Make sure "Configuration Bits set in code." option is checked in MPLAB.
//
// These settings are appropriate for debugging the PIC microcontroller. If you need to 
// program the PIC for standalone operation, change the COE_ON option to COE_OFF.

_CONFIG1( JTAGEN_OFF & GCP_OFF & GWRP_OFF & 
		 BKBUG_ON & COE_ON & ICS_PGx1 & 
		 FWDTEN_OFF & WINDIS_OFF & FWPSA_PR128 & WDTPS_PS32768 )

// ******************************************************************************************* //
// Configuration bits for CONFIG2 settings.
// Make sure "Configuration Bits set in code." option is checked in MPLAB.

_CONFIG2( IESO_OFF & SOSCSEL_SOSC & WUTSEL_LEG & FNOSC_PRIPLL & FCKSM_CSDCMD & OSCIOFNC_OFF &
		 IOL1WAY_OFF & I2C1SEL_PRI & POSCMOD_XT )

// ******************************************************************************************* //

// Varible used to indicate that the current configuration of the keypad has been changed,
// and the KeypadScan() function needs to be called.

volatile int scanKeypad;



// ******************************************************************************************* //

int main(void)
{
	char key;
        int printVar = 0;
        int result = 0;


	// TODO: Initialize and configure IOs, LCD (using your code from Lab 1), 
	// UART (if desired for debugging), and any other configurations that are needed.
	
	LCDInitialize();
	KeypadInitialize();
          LCDPrintString("Enter");

   //     LATBbits.LATB15 = 0;
   //     LATBbits.LATB14 = 0;
   //     LATBbits.LATB13 = 0;
   //     LATBbits.LATB12 = 0;
	
	// TODO: Initialize scanKeypad variable.
	
	while(1)
	{
		// TODO: Once you create the correct keypad driver (Part 1 of the lab assignment), write
		// the C program that use both the keypad and LCD drivers to implement the 4-digit password system.
		
		if( scanKeypad == 1 ) {
                      
			key = KeypadScan();
			if( key != -1 ) {
				LCDMoveCursor(1,0);
				LCDPrintChar(key);
			}
			scanKeypad = 0;
		}
/*

            case 0:                                                             // User Mode State
	if (printVar ==  0){
            printVar = 1;                                                       // Displayed header already
            LCDPrintString("Enter:");                                           // Display enter on LCD 1st line
		//go to line 2 columb 1
	}

        if (keypadScan == 1){
            if (not at spot 5) {
		LCDPrintString(key);                                            // Display key
		if ( key == '*'){
                    if ( key ==  '*'){
			state = 1;                                              // Go to program state
                    }
                    else {
			result = 0;                                             // Bad
			state = 3;                                              // go to result state
                    }
                    if (key == '#'){
                        result = 0;                                             // Bad
			state = 3;                                              // Go to result state
                    }
                    else{
                                                                                //DO SOMETHING HERE TO COMPARE OR CALL COMPARE FUNCTION OR COMPARE STATE
                                                                                //POSSIBLY STORE IN TEMP ARRAY TO COMPARE LATER
			}
		}

		if (spot 5){
			LCDPrintString( key); 		// Display key
			if (key == '#'){
				result = 2;		// Good
				//SEE ABOVE CAPS
			}
			else{
				result = 0; 		// Bad
				state = 3; 		// Go to result state
			}
		}
	}
break;

case 1: 							// Program Mode State
	if (printVar == 0){
		printVar = 1; 				// Displayed header already
		LCDClear();				// Clear screen and return home
		LCDPrintString("Set Mode");		// Display Set Mode
		//go to new line
	}

	if (keypadscan = 1){
		LCDPrintString(key); 			// Display key
		if (not spot 5){
			if (key == '*'){
				result = 3;		// Invalid
				state = 3; 		// Go to result state
			}
			if (key == '#'){
				result = 3;		// Invalid
				state = 3; 		// Go to result state
			}
			else {
				// Store in temp array
			}
		}

		if( spot 5 ){
			if (key == '#'){
				result = 4;		// Valid
				state = 3; 		// Go to result state
			}
			else{
				result = 3;		// Invalid
				state = 3; 		// Go to result state
			}
		}
	}
break;

case 2: 							// Compare
	// compare temp array to programed arrays
break;

case 3: 							// Result State
	printVar = 0;					// Reset printVar for case 1 and 2
	LCDClear();					// Clear screen and return home
	if (result == 1){
		LCDPrintString("Bad");			// Display Bad
	}
	if (result == 2){
		LCDPrintString("Good");			// Display Good
	}
	if (result == 3){
		LCDPrintString("Invalid");		// Display Invalid
	}
	if (result == 4){
		LCDPrintStrig("Valid");			// Display Valid
	DelayUS( 2000000);				// Wait 2 seconds (if doesnt work
								// Use DelayUS(); multiple times

	state = 0;					// Go to user mode
break;

*/
                 }
	return 0;
}

// ******************************************************************************************* //
// Defines an interrupt service routine that will execute whenever any enable
// input change notifcation is detected.
// 
//     In place of _ISR and _ISRFAST, we can directy use __attribute__((interrupt))
//     to inform the compiler that this function is an interrupt. 
//
//     _CNInterrupt is a macro for specifying the interrupt for input change 
//     notification.
//
// The functionality defined in an interrupt should be a minimal as possible
// to ensure additional interrupts can be processed. 
void __attribute__((interrupt,auto_psv)) _CNInterrupt(void)
{
	// TODO: Clear interrupt flag
	IFS1bits.CNIF = 0;

	// TODO: Detect if *any* key of the keypad is *pressed*, and update scanKeypad
   //     if((PORTAbits.RA0 == 1 || PORTAbits.RA1 == 1 || PORTBbits.RB2 == 1) && scanKeypad != 1){
            scanKeypad = 1;
   //     }

	// variable to indicate keypad scanning process must be executed.
}

// ******************************************************************************************* //
