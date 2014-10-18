// ******************************************************************************************* //

//YELLOW COLUMN
//GREEN ROWS


#include "p24fj64ga002.h"
#include "keypad.h"
#include "lcd.h"

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

    TRISAbits.TRISA0 = 1;                                                       //col 1 pin2
    TRISAbits.TRISA1 = 1;                                                       //col 2 pin3
    TRISBbits.TRISB2 = 1;                                                       //col 3 pin6

    AD1PCFGbits.PCFG0 = 1;
    AD1PCFGbits.PCFG1 = 1;
    AD1PCFGbits.PCFG4 = 1;

    //CHANGE NOTIFICATION
    CNEN1bits.CN2IE = 1;                                                        //col 1 pin2
    CNEN1bits.CN3IE = 1;                                                        //col 2 pin3
    CNEN1bits.CN6IE = 1;                                                        //col 3 pin6
 
    //INTERNAL PULL-UP (
    CNPU1bits.CN2PUE = 1;                                                       //col 1 pin2
    CNPU1bits.CN3PUE = 1;                                                       //col 2 pin3
    CNPU1bits.CN6PUE = 1;                                                       //col 3 pin6
    /////////////////////////////////////////////////////////////



    /////////////////////////////////////////////////////////////
    //                       OUTPUTS                           //
    /////////////////////////////////////////////////////////////

    //INITIALIZE OUTPUTS
    TRISBbits.TRISB15 = 0;                                                      //row1 pin 26
    TRISBbits.TRISB14 = 0;                                                      //row2 pin 25
    TRISBbits.TRISB13 = 0;                                                      //row3 pin 24
    TRISBbits.TRISB12 = 0;                                                      //row4 pin 23

    //OPEN-DRAIN CONFIGURATION
    ODCBbits.ODB15 = 1;                                                         //row1 pin 26
    ODCBbits.ODB14 = 1;                                                         //row2 pin 25
    ODCBbits.ODB13 = 1;                                                         //row3 pin 24
    ODCBbits.ODB12 = 1;                                                         //row4 pin 24
    ////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////

    //CN INTERRUPT FLAG AND ENABLE
    IFS1bits.CNIF = 0;                                                          //CLEARS THE CHANGE NOTIFICATION INTERRUPT FLAG
    IEC1bits.CNIE = 1;                                                          //ENABLES THE CHANGE NOTIFICATION INTERRUPT


}

// ******************************************************************************************* //
volatile int state2 = 0;

char KeypadScan() { 

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

    char key = -1;                                                              // Initialize key to -1
    int word = 0x0000;                                                       // Initialize word and make all 0
        

    while (1){
        switch (state2){


                case 0:                                                         // Row 1 Scan of Columbs
                    LATB = (LATB | 0xF000);                                     // Make RB15 through 12 -> 1 and dont change rest
                    word = 0x7FFF;                                              // Make word be 0111 for first 4 bits
                    LATB = (word & LATB);                                       // Change RB15 -> 12 to 0111

                    DelayUs(150000);                                            // Wait for pins to settle

                    /*Scan for Columb 1*/
                    if(PORTAbits.RA0 == 0 && PORTAbits.RA1 == 1 && PORTBbits.RB2 == 1){
                        key = '1';                                              // Update key
                        state2 = 5;                                             // Go to columb 1 wait state
                       
                    }

                    /*Scan for Columb 2*/
                    if(PORTAbits.RA0 == 1 && PORTAbits.RA1 == 0 && PORTBbits.RB2 == 1){
                        key = '2';                                              // Update key
                        state2 = 6;                                             // Go to columb 2 wait state
                        
                    }

                    /*Scan for Columb 3*/
                    if(PORTAbits.RA0 == 1 && PORTAbits.RA1 == 1 && PORTBbits.RB2 == 0){
                        key = '3';                                              // Update key
                        state2 = 7;                                             // Go to columb 3 wait state
                   
                    }

                    /*If NO Columbs found*/
                    if(PORTAbits.RA0 == 1 && PORTAbits.RA1 == 1 && PORTBbits.RB2 == 1) {
                        state2 = 1;                                             // Go to next row (row 2)
                    }
                break;
                  
                  
                  
                  
                case 1:                                                         // Row 2 Scan of Columbs
                    word = ((word>>1) | (0x8000));                              // Shift word right 1 and or with 1000 to make RB15 -> 12 equal 1011
                    LATB = (LATB | 0xF000);                                     // Make RB15 through 12 -> 1 and dont change rest
                    LATB = (word & LATB);                                       // Change RB15 -> 12 to 1011

                    DelayUs(150000);                                            // Wait for pins to settle

                    /*Scan for Columb 1*/
                    if(PORTAbits.RA0 == 0 && PORTAbits.RA1 == 1 && PORTBbits.RB2 == 1){
                        key = '4';                                              // Update key
                        state2 = 5;                                             // Go to columb 1 wait state
                    
                    }

                    /*Scan for Columb 2*/
                    if(PORTAbits.RA0 == 1 && PORTAbits.RA1 == 0 && PORTBbits.RB2 == 1){
                        key = '5';                                              // Update key
                        state2 = 6;                                             // Go to columb 2 wait state
                    
                    }

                    /*Scan for Columb 3*/
                    if(PORTAbits.RA0 == 1 && PORTAbits.RA1 == 1 && PORTBbits.RB2 == 0){
                        key = '6';                                              // Update key
                        state2 = 7;                                             // Go to columb 3 wait state
                      
                    }

                    /*If NO Columbs found*/
                    if(PORTAbits.RA0 == 1 && PORTAbits.RA1 == 1 && PORTBbits.RB2 == 1) {
                        state2 = 2;                                             // Go to next row (row 3)
                    }
                break;
                  
                  
                  
                  
                case 2:                                                         // Row 3 Scan of Columbs
                    word = ((word>>1) | (0x8000));                              // Shift word right 1 and or with 1000 to make RB15 -> 12 equal 1101
                    LATB = (LATB | 0xF000);                                     // Make RB15 through 12 -> 1 and dont change rest
                    LATB = (word & LATB);                                       // Change RB15 -> 12 to 1101

                    DelayUs(150000);                                            // Wait for pins to settle

                    /*Scan for Columb 1*/
                    if(PORTAbits.RA0 == 0 && PORTAbits.RA1 == 1 && PORTBbits.RB2 == 1){
                        key = '7';                                              // Update key
                        state2 = 5;                                             // Go to columb 1 wait state
                        
                    }

                    /*Scan for Columb 2*/
                    if(PORTAbits.RA0 == 1 && PORTAbits.RA1 == 0 && PORTBbits.RB2 == 1){
                        key = '8';                                              // Update key
                        state2 = 6;                                             // Go to columb 2 wait state
                       
                    }

                    /*Scan for Columb 3*/
                    if(PORTAbits.RA0 == 1 && PORTAbits.RA1 == 1 && PORTBbits.RB2 == 0){
                        key = '9';                                              // Update key
                        state2 = 7;                                             // Go to columb 3 wait state
                       
                    }

                    /*If NO Columbs found*/
                    if(PORTAbits.RA0 == 1 && PORTAbits.RA1 == 1 && PORTBbits.RB2 == 1) {
                        state2 = 3;                                             // Go to next row (row 4)
                    }
                break;
                  
                  
                  
                  
                case 3:                                                         // Row 4 Scan of Columbs
                    word = ((word >> 1) | (0x8000));                            // Shift word right 1 and or with 1000 to make RB15 -> 12 equal 1110
                    LATB = (LATB | 0xF000);                                     // Make RB15 through 12 -> 1 and dont change rest
                    LATB = (word & LATB);                                       // Change RB15 -> 12 to 1110

                    DelayUs(150000);                                            // Wait for pins to settle

                    /*Scan for Columb 1*/
                    if(PORTAbits.RA0 == 0 && PORTAbits.RA1 == 1 && PORTBbits.RB2 == 1){
                        key = '*';                                              // Update key
                        state2 = 5;                                             // Go to columb 1 wait state
                       
                    }

                    /*Scan for Columb 2*/
                    if(PORTAbits.RA0 == 1 && PORTAbits.RA1 == 0 && PORTBbits.RB2 == 1){
                        key = '0';                                              // Update key
                        state2 = 6;                                             // Go to columb 2 wait state
                       
                    }

                    /*Scan for Columb 3*/
                    if(PORTAbits.RA0 == 1 && PORTAbits.RA1 == 1 && PORTBbits.RB2 == 0){
                        key = '#';                                              // Update key
                        state2 = 7;                                             // Go to columb 3 wait state
                       
                    }

                    /*If NO Columbs found*/
                    if(PORTAbits.RA0 == 1 && PORTAbits.RA1 == 1 && PORTBbits.RB2 == 1) {
                        state2 = 4;                                             // Go to Return state
                    }
                break;



                case 4:                                                         // Return State
                    LATB = (LATB | 0xF000);                                     // Make RB15 - > 12 1111
                    LATB = (LATB ^ 0xF000);                                     // XOR RB15 -> 12 with 1111 to get 0000

                    DelayUs(150000);                                            // Wait for pins to settle
                    state2 = 0;                                                 // Go to Row 1 scan for next call
                    
                    return key;                                                 // Return key
                break;



                case 5:                                                         // Columb 1 wait state
                    if (PORTAbits.RA0 == 1){                                    // If columb 1 released
                        state2 = 4;                                             // Go to Return state
                    }
                break;



                case 6:                                                         // Columb 2 wait state
                    if (PORTAbits.RA1 == 1){                                    // If columb 2 released
                        state2 = 4;                                             // Go to Return state
                    }
                break;



                case 7:                                                         // Columb 3 wait state
                    if (PORTBbits.RB2 == 1){                                    // If columb 1 released
                        state2 = 4;                                             // Go to Return state
                    }
                break;
        }
    }
}
// ******************************************************************************************* //
