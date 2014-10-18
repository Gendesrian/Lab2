// ******************************************************************************************* //
// Include file for PIC24FJ64GA002 microcontroller. This include file defines
// MACROS for special function registers (SFR) and control bits within those
// registers.

#include "p24fj64ga002.h"
#include <stdio.h>
#include "lcd.h"
#include "keypad.h"
#include "string.h"

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
volatile int state = 0;



// ******************************************************************************************* //

int main(void)
{

	unsigned char key;
       // const unsigned int max_NUM_PW = 10;
       // const unsigned int max_PW_length = 6;
       // unsigned char acceptablePW[max_NUM_PW][max_PW_length];
       //char testPW[6];
        //testPW = ""
       //testPW = "";
       //strcpy(testPW, "");
       // int next_empty_row = 0;
       // int index_acceptablePW = 0;
        unsigned int printVar0 = 0;
        unsigned int printVar1 = 0;
        unsigned int result = 0;
        unsigned int inputCount=0;
        unsigned int starCount = 0;
        unsigned int tempCount = 0;
        unsigned int i = 0;
        unsigned pwCount = 1;
        char defaultPW[5] = {'1', '2', '3' , '4'};
        //acceptablePW[next_empty_row]="1234";
       // strcpy(acceptablePW[next_empty_row], "1234");
       // next_empty_row += 1;

        char tempArry[5] = {};
        unsigned char passW1[5] = {};
        unsigned char passW2[5] = {};
        unsigned char passW3[5] = {};
        unsigned char passW4[5] = {};

        T4CONbits.T32 = 1;
        T4CONbits.TCKPS0 = 0;                                                   // 1:1 prescale
        T4CONbits.TCKPS1 = 0;
        PR4 = 0;                                                                // creates a 2second timer
        PR5 = 0b111000010;
        TMR4 = 0;
        TMR5 = 0;
        IFS1bits.T5IF = 0;                                                      //drop the flag
        IEC1bits.T5IE = 1;                                                      //enale interrupt enable
                                                             //enable 32 bit timer
        T4CONbits.TON = 0;                                                      // turn timer off
                                                  //  ^^


        //unsigned int state = 0;


	// TODO: Initialize and configure IOs, LCD (using your code from Lab 1), 
	// UART (if desired for debugging), and any other configurations that are needed.
	
	LCDInitialize();
	KeypadInitialize();
	
	// TODO: Initialize scanKeypad variable.
	
	while(1){
		// TODO: Once you create the correct keypad driver (Part 1 of the lab assignment), write
		// the C program that use both the keypad and LCD drivers to implement the 4-digit password system.
                /*if( scanKeypad == 1 ) {
                      
			key = KeypadScan();
			if( key != -1 ) {
				LCDMoveCursor(1,0);
				LCDPrintChar(key);
			}
			scanKeypad = 0;
		}*/

            switch(state){

                case 0:                                         		// User Mode State
/*******************************PRINT PORTION**********************************/
                    if (printVar0 ==  0){            				//[D:I renamed printVar to 0 and 1 for 								//each case, respectively, because it only 							//sets to 0 during clear state and this
                                                                                    //program can go from case 0 -> case1
                                                                                    //so printVar as before would stay 1 and
                                                                                //skip screen initialization for program 								//state]

                    printVar0 = 1;                                       	// Displayed header already
                    LCDPrintString("Enter");                                	// Display enter on LCD 1st line 									//[D:removed colon, not in example]
                    LCDMoveCursor(1,0);                                         // Go to line 2 columb 1
                                                                                    //[D:LCD command code "C0" forces cursor to beginning of 2nd line]
                    inputCount = 0;                                             //only in this state once
                                                                                    //initialized and cleared
                    starCount=0;                                                //only in this state once
                                                                                    //initialized and cleared
                    }
/******************************END PRINT PORTION*******************************/

/********************************SCAN PORTION**********************************/
                    if (scanKeypad == 1){
                        key = KeypadScan();
                        scanKeypad = 0;
                        if(key != -1){
                            LCDPrintChar(key);                  		// Display key
                            inputCount += 1;                                    // Increment inputCount for = 5 case
                           tempArry[tempCount] = key;                          // Store key into tempArry
                            tempCount += 1;                                     // Count for tempArry storage.  May be able to just use inputCount.
                           // strcat(testPW,key);                                 //adds key to testPW
                            if ( key == '*'){
				starCount = starCount + 1;
				//if the 1st two entries are stars
				if ( starCount == 2 && inputCount == 2){
					state = 1;                              // Go to program state
				}
                                else if (starCount != 2 && inputCount >= 2){
					result = 1;                             // Bad
					state = 3;                              // Go to result state
				}
                            }

                            if (key == '#'){
				result = 1;                             	// Bad
				state = 3;                              	// Go to result state
                            //[D:if pound is entered WHILE NOT IN PROGRAM MODE it is
                                //automatically a bad entry]
                            }

                            /*else{
                             *
				//[D: ONLY NEED TO COMPARE ONCE ALL 4 DIGITS ARE 						//ENTERED, ELSE STATEMENT NOT NEEDED UNTIL AT END]
				//DO SOMETHING HERE TO COMPARE OR CALL COMPARE
                          	//FUNCTION OR COMPARE STATE
				//POSSIBLY STORE IN TEMP ARRAY TO COMPARE LATER
                            }*/

                            if (inputCount == 4){
                                T4CONbits.TON = 1;                              // turn timer on
                                while (IFS1bits.T5IF == 0);
                                T4CONbits.TON = 0;
                            
                            state = 2;                                          //I think this is when to untilize state 2

                            }                                                   // End of IF(inputCount==4)
                        }
                    }                                                           // End scanKeypad == 1

/****************************END SCAN PORTION**********************************/

                break;








                case 1:                                                        	// Program Mode State
/******************************PRINT PORTION***********************************/
                    if (printVar1 == 0){
                    printVar1 = 1;                                      	// Displayed header already
                    LCDClear();                                         	// Clear screen and return home
                    LCDPrintString("Set Mode");                         	// Display Set Mode
                    LCDMoveCursor(1,0);                                         // Go to new line
                   // strcpy(testPW,"");                                                 //reset doublestar to empty string
                    inputCount =0;                                              // Reset to count for programming state
                    starCount = 0;                                              // Not needed for this state but why not?
                    tempCount = 0;
                    }
/***************************END PRINT PORTION**********************************/

                    if (scanKeypad == 1){
                        key = KeypadScan();
                        scanKeypad = 0;
                       // if (key != -1){
                            LCDPrintChar(key);                              	// Display key
                            inputCount += 1;                                        // Update inputCount
                            if(tempCount != 4){
                            tempArry[tempCount] = key;
                            tempCount += 1;                                         // Update tempCount for tempArry
                            }
                          //  strcat(testPW,key);                                 //adds key to testPW

                            if (inputCount <5 && key != -1){
                                if (key == '*'){
                                    result = 3;                                     // Invalid
                                    state = 3;                              	// Go to result state
                                }

                                if (key == '#'){
                                    result = 3;                             	// Invalid
                                    state = 3;                                      // Go to result state
                                }

                            }                                                       // End of IF count less than 4

                            if( inputCount == 5 ){
                                if (key == '#'){
                                    T4CONbits.TON = 1;                              // turn timer on
                                    while (IFS1bits.T5IF == 0);
                                    T4CONbits.TON = 0;
                                   // strcpy(acceptablePW[next_empty_row], testPW);
                                    //acceptablePW[next_empty_row] = testPW;
                                   // next_empty_row +=1;
                                    if(pwCount == 1){
                                        strcpy(passW1,tempArry);
                                        pwCount += 1;
                                        result = 4;
                                        state = 3;
                                    }
                                    else if(pwCount == 2){
                                        strcpy(passW2,tempArry);
                                        pwCount += 1;
                                    }
                                    else if(pwCount == 3){
                                        strcpy(passW3,tempArry);
                                        pwCount += 1;
                                    }
                                    else if(pwCount == 4){
                                        strcpy(passW4,tempArry);
                                        pwCount += 1;
                                    }
                                    result = 4;                                     // Valid
                                    state = 3;                              	// Go to result state
                                }

                                else if(key != '#'){
                                    result = 3;                             	// Invalid
                                    state = 3;                              	// Go to result state
                                }
                            }
                       // }
                    }                                                           // End scanKeypad == 1
/****************************END SCAN PORTION**********************************/
                break;








                case 2: 							// Compare
                    

                    
                // compare temp array to programed arrays
                //[D:Is this where you compare with your list of acceptable PW?!?]
                //DO SOMETHING HERE TO COMPARE OR CALL COMPARE
                //FUNCTION OR COMPARE STATE
                //POSSIBLY STORE IN TEMP ARRAY TO COMPARE LATER
                    if(strcmp(tempArry, defaultPW)==0 ){
                            result = 2;
                        }
                        
                    else if(strcmp(tempArry, passW1)==0 ){
                            result = 2;
                        }
                       
                    else if(strcmp(tempArry, passW2)==0 ){
                            result = 2;
                        }
                       
                    else if(strcmp(tempArry, passW3)==0 ){
                            result = 2;
                        }
                       
                    else if(strcmp(tempArry, passW4)==0 ){
                            result = 2;
                        }
                    else {
                        result = 1;
                    }

                    


                    //for (index_acceptablePW=0; i < max_NUM_PW; index_acceptablePW++)
                   // {
                   //     if (strcmp(acceptablePW[index_acceptablePW],testPW) == 0)
//                        {
//                            result = 2;
//                            state = 3;
//                            //continue;
//
//                        }
//
//                        else if (result != 2 && state != 3)
//                        {
//                            result = 1;
//                        }
//                       // if (state == 3)
//                       // {
//                       //     break;
//                       // }
//                    }
                    state = 3; // Go to result state

                break;








                case 3: 							// Result State

                printVar0 = 0;                                          	// Reset printVar1/2 for case 0 and 1
                printVar1 = 0;
                LCDClear();                                                 	// Clear screen and return home
                if (result == 1){
                    LCDPrintString("Bad");                                	// Display Bad
                //T4CONbits.TON = 1;                                          	// turn timer on
                //while (IFS1bits.T5IF == 0);                                     //
                //T4CONbits.TON = 0;
                }

                if (result == 2){
                    LCDPrintString("Good");                                 	// Display Good
                //T4CONbits.TON = 1;                                          	// turn timer on
                //while (IFS1bits.T5IF == 0);                                     //
                //T4CONbits.TON = 0;
                }

                if (result == 3){
                    LCDPrintString("Invalid");                                  // Display Invalid
                }

                if (result == 4){
                    LCDPrintString("Valid");                                     // Display Valid
                }

               // for (i=0; i< 6 ; i++){
                    //tempArry[i] = '\0';
               // }

                T4CONbits.TON = 1;                                          	// turn timer on
                while (IFS1bits.T5IF == 0);                                     //
                T4CONbits.TON = 0;
                //TMR4 = 0;
                //TMR5 =0;
                //tempArry[5] = {};
                scanKeypad = 0;
                starCount = 0;                                                  // Reset starCount to 0
                inputCount = 0;                                                 // Reset inputCount = 0
                tempCount = 0;
                LCDClear();                                                     // Clear LCD and return home
                state = 0;                                              	// Go to user mode
                break;

		

            }                                                                   // End Switch
        }                                                                       // End While

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


void __attribute__((interrupt, aut_psv)) _T5Interrupt(void){
    IFS1bits.T5IF = 0;
    TMR4 = 0;
    TMR5 =0;

}

void __attribute__((interrupt,auto_psv)) _CNInterrupt(void)
{
	// TODO: Clear interrupt flag
	IFS1bits.CNIF = 0;

	// TODO: Detect if *any* key of the keypad is *pressed*, and update scanKeypad
        // variable to indicate keypad scanning process must be executed.

        scanKeypad = 1;
}

// ******************************************************************************************* //
