// ******************************************************************************************* //

#include "p24fj64ga002.h"
#include "keypad.h"

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
    //INITALIZE INPUTS. INPUTS = 1
    TRISBBITS.TRISB6 = 1;   //RB6
    TRISBBITS.TRISB7 = 1;   //RB7
    TRISBBITS.TRISB8 = 1;   //RB8
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    //CHANGE NOTIFICATION

    //CNEN1BITS.CN6IE = 1;
    //CNEN1BITS.CN7IE = 1;
    //CNEN1BITS.CN8IE = 1;

    CNEN2BITS.CN24IE = 1;
    CNEN2BITS.CN23IE = 1;
    CNEN2BITS.CN22IE = 1;
    /////////////////////////////////////////////////////////////

    /////////////////////////////////////////////////////////////
    //INTERNAL PULL-UP (may not b 1, double check)
    //CNPU1BITS.CN4PUE = 1;
    //CNPU1BITS.CN5PUE = 1;
    //CNPU1BITS.CN6PUE = 1;

    CNPU2BITS.CN24PUE = 1;
    CNPU2BITS.CN23PUE = 1;
    CNPU2BITS.CN22PUE = 1;
    /////////////////////////////////////////////////////////////

    /////////////////////////////////////////////////////////////
    //INITALIZE OUTPUTS. OUTPUT  = 0;
    TRISBBITS.TRISB12 = 0;
    TRISBBITS.TRISB13 = 0;
    TRISBBITS.TRISB14 = 0;
    TRISBBITS.TRISB15 = 0;
    ///////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////
    //OPEN-DRAIN CONFIG.
    ODCBBITS.ODB12 = 1;
    ODCBBITS.ODB13 = 1;
    ODCBBITS.ODB14 = 1;
    ODCBBITS.ODB15 = 1;
    /////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    //RANDOM GUESS ON CN INTERRUPT FLAG AND ENABLE
    IFS1BITS.CNIF = 0; //CLEARS THE CHANGE NOTIFICATION INTERRUPT FLAG
    IEC1BITS.CNIE = 1; //ENABLES THE CHANGE NOTIFICATION INTERRUPT


}

// ******************************************************************************************* //

char KeypadScan() {
	char key = -1;
	
	
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
