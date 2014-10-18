// ******************************************************************************************* //

//YELLOW COLUMN
//GREEN ROWS


#include "p24fj64ga002.h"
#include "keypad.h"


volatile int keypadNumber = -1;
// ******************************************************************************************* //

void KeypadInitialize() {
	
	// TODO: Configure IOs and Change Notificaiton interrupt for keypad scanning. This

	// configuration should ensure that if any key is pressed, a change notification interrupt 
	// will be generated. NOTE --- DO NOT USE RB9
        //??SO... IF ONE OF THESE NOTIFICATIONS CHANGES, FLAG CHANGES FROM 0 TO 1 AND SOME INTERRUPT HAPPENS??

        // COL = INPUTS
        // ROWS = OUTPUT

        //ODCx = OUTPUT
        //INTERNAL PULL-UP for input pins
        //CHANGE NOTIFICATION INTERRUPT for input pins

    /////////////////////////////////////////////////////////////
    //                          INPUTS                         //
    /////////////////////////////////////////////////////////////

    //INITALIZE INPUTS. INPUTS = 1
    TRISBBITS.TRISB10 = 1;   //RB10 // column 1 pin 21
    TRISBBITS.TRISB11 = 1;   //RB11   // col 2 pin 22
    TRISBBITS.TRISB5 = 1;   //RB5     //col 3 pin 14

    //CHANGE NOTIFICATION
    CNEN2BITS.CN16IE = 1; // pin 21 RB10
    CNEN1BITS.CN15IE = 1; //pin 22 RB11
    CNEN2BITS.CN27IE = 1; // pin 14 RB5
 
    //INTERNAL PULL-UP (may not b 1, double check)
    CNPU2BITS.CN16PUE = 1; //pin 21
    CNPU1BITS.CN15PUE = 1; //pin 22
    CNPU2BITS.CN27PUE = 1; // pin 14
    /////////////////////////////////////////////////////////////


    /////////////////////////////////////////////////////////////
    //                       OUTPUTS                           //
    /////////////////////////////////////////////////////////////

    //INITALIZE OUTPUTS. OUTPUT  = 0;
    TRISABITS.TRISA0 = 0; // row 1 - 4 in order going down  pin 2
    TRISABITS.TRISA1 = 0; // pin 3
    TRISBBITS.TRISB2 = 0; //pin 6
    TRISBBITS.TRISB3 = 0; //pin 7




    //OPEN-DRAIN CONFIG.
    ODCABITS.ODA0 = 1; // pin2
    ODCABITS.ODA1 = 1; //pin 3
    ODCBBITS.ODB2 = 1; //pin6
    ODCBBITS.ODB3 = 1; //pin 7
    ////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    //RANDOM GUESS ON CN INTERRUPT FLAG AND ENABLE
    IFS1BITS.CNIF = 0; //CLEARS THE CHANGE NOTIFICATION INTERRUPT FLAG
    IEC1BITS.CNIE = 1; //ENABLES THE CHANGE NOTIFICATION INTERRUPT


}

// ******************************************************************************************* //

char KeypadScan() {
	char key = -1;
        int count = 0;
        /***************case1**********************/


                LATABITS.LATA0 = 0;
                LATABITS.LATA1 = 1;
                LATBBITS.LATB2 = 1;
                LATBBITS.LATB3 = 1;
                
                if(LATBBITS.LATB10 == 0 && LATBBITS.LATB11 == 1 && LATBBITS.LATB5 == 1){
                    key='1';
                    count = count + 1;
            }
                if(LATBBITS.LATB10 == 1 && LATBBITS.LATB11 == 0 && LATBBITS.LATB5 == 1){
                    key='2';
                    count = count + 1;
                }
                if(LATBBITS.LATB10 == 0 && LATBBITS.LATB11 == 1 && LATBBITS.LATB5 == 0){
                    key='3';
                    count = count + 1;
                }
               // if(LATBBITS.LATB10 == 0 && LATBBITS.LATB11 == 0|| LATBBITS.LATB11 == 0 && LATBBITS.LATB5 == 0 || LATBBITS.LATB10 == 0 && LATBBITS.LATB5 == 0){
               //     return -1;
                //
                
                
                LATABITS.LATA0 = 1;
                LATABITS.LATA1 = 0;
                LATBBITS.LATB2 = 1;
                LATBBITS.LATB3 = 1;
                
                if(LATBBITS.LATB10 == 0 && LATBBITS.LATB11 == 1 && LATBBITS.LATB5 == 1){
                    key='4';
                    count = count + 1;
            }
                if(LATBBITS.LATB10 == 1 && LATBBITS.LATB11 == 0 && LATBBITS.LATB5 == 1){
                    key='5';
                    count = count + 1;
                }
                if(LATBBITS.LATB10 == 0 && LATBBITS.LATB11 == 1 && LATBBITS.LATB5 == 0){
                    key='6';
                    count = count + 1;
                }

                
                LATABITS.LATA0 = 1;
                LATABITS.LATA1 = 1;
                LATBBITS.LATB2 = 0;
                LATBBITS.LATB3 = 1;
                
                if(LATBBITS.LATB10 == 0 && LATBBITS.LATB11 == 1 && LATBBITS.LATB5 == 1){
                    key='7';
                    count = count + 1;
            }
                if(LATBBITS.LATB10 == 1 && LATBBITS.LATB11 == 0 && LATBBITS.LATB5 == 1){
                    key='8';
                    count = count + 1;
                }
                if(LATBBITS.LATB10 == 0 && LATBBITS.LATB11 == 1 && LATBBITS.LATB5 == 0){
                    key='9';
                    count = count + 1;
                }
            
                
                LATABITS.LATA0 = 1;
                LATABITS.LATA1 = 1;
                LATBBITS.LATB2 = 1;
                LATBBITS.LATB3 = 0;
                
                if(LATBBITS.LATB10 == 0 && LATBBITS.LATB11 == 1 && LATBBITS.LATB5 == 1){
                    key='*';
                    count = count + 1;
            }
                if(LATBBITS.LATB10 == 1 && LATBBITS.LATB11 == 0 && LATBBITS.LATB5 == 1){
                    key='0';
                    count = count + 1;
                }
                if(LATBBITS.LATB10 == 0 && LATBBITS.LATB11 == 1 && LATBBITS.LATB5 == 0){
                    key='#';
                    count = count + 1;
                }
            
                
                if (count > 1)
                {
                    key = -1;
                }
            
        }



	// TODO: Implement the keypad scanning procedure to detect if exactly one button of the 
	// keypad is pressed. The function should return:
	//
	//      -1         : Return -1 if no keys are pressed.
	//      '0' - '9'  : Return the ASCII character '0' to '9' if one of the 
	//                   numeric (0 - 9) keys are pressed.
                    //011 0000 <- binary 0, add 1 in binary to increase by 1. // 30 hex, same to increase by 1
	//      '#'        : Return the ASCII character '#' if the # key is pressed. 
                    //010 0011 <- binary // 23 hex
        //      '*'        : Return the ASCII character '*' if the * key is pressed.
                    //010 1010 -< binary // 2A hex
	//       -1        : Return -1 if more than one key is pressed simultaneously.
	// Notes: 
	//        1. Only valid inputs should be allowed by the user such that all invalid inputs 
	//           are ignored until a valid input is detected.
	//        2. The user must release all keys of the keypad before the following key press
	//           is processed. This is to prevent invalid keypress from being processed if the 
	//           users presses multiple keys simultaneously.
	//

	return key;
}

// ******************************************************************************************* //
void setupColumns () {

}

//  CNInterrupt
void __attribute__ ((interrupt, auto_psv)) _CNInterrupt(void)
{
    if(PORTBbits.RB10 == 0 || PORTBbits.RB11 == 0 || PORTBbits.RB5 == 0){
    // update keypress
    // switch states?

    }
//    if (CNPU2BITS.CN16PUE = 0) //pin 21
//    {
//        CNPU2BITS.CN16PUE = 1;
//        if ()
    }
IFS1bits.CNIF = 0;                                                              // Reset Change Notification flag
}