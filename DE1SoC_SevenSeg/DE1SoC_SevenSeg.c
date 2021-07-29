/*
 * DE1SoC_SevenSeg.c
 *
 *  Created on: 12 Feb 2021
 *      Author: Harry Clegg
 *      		You!
 */

#include "DE1SoC_SevenSeg.h"

// ToDo: Add the base addresses of the seven segment display peripherals.
volatile unsigned char *sevenseg_base_lo_ptr=(unsigned char *)0xFF200020;
volatile unsigned char *sevenseg_base_hi_ptr=(unsigned char *)0xFF200030;

//volatile unsigned char *sevenseg_base_lo_ptr = 0;
//volatile unsigned char *sevenseg_base_hi_ptr = 0;

// There are four HEX displays attached to the low (first) address.
#define SEVENSEG_N_DISPLAYS_LO 4

// There are two HEX displays attached to the high (second) address.
#define SEVENSEG_N_DISPLAYS_HI 2

void DE1SoC_SevenSeg_Write(unsigned int display, unsigned char value) {
    // Select between the two addresses so that the higher level functions
    // have a seamless interface.
    if (display < SEVENSEG_N_DISPLAYS_LO) {
        // If we are targeting a low address, use byte addressing to access
        // directly.
        sevenseg_base_lo_ptr[display] = value;
    } else {
        // If we are targeting a high address, shift down so byte addressing
        // works.
        display = display - SEVENSEG_N_DISPLAYS_LO;
        sevenseg_base_hi_ptr[display] = value;
    }
}

void DE1SoC_SevenSeg_SetSingle(unsigned int display, unsigned int value) {
    // ToDo: Write the code for driving a single seven segment display here.
    // Your function should turn a real value 0-F into the correctly encoded
    // bits to enable the correct segments on the seven segment display to
    // illuminate. Use the DE1SoC_SevenSeg_Write function you created earlier
    // to set the bits of the display.
		//display=display+2;
		if (value==0){
			DE1SoC_SevenSeg_Write(display,0x3F);// light segment 0,1,2,3,4,5
		}
		if (value==1){
			DE1SoC_SevenSeg_Write(display,0x06);//  light segment 1,2
		}
		if (value==2){
			DE1SoC_SevenSeg_Write(display,0x5B);// light segment 0,1,3,4,6
		}
		if (value==3){
			DE1SoC_SevenSeg_Write(display,0x4F);// light segment 0,1,2,3,6
		}
		if (value==4){
			DE1SoC_SevenSeg_Write(display,0x66);// light segment 1,2,5,6
		}
		if (value==5){
			DE1SoC_SevenSeg_Write(display,0x6D);// light segment 0,2,3,5,6
		}
		if (value==6){
			DE1SoC_SevenSeg_Write(display,0x7D);// light segment 0,2,3,4,5,6
		}
		if (value==7){
			DE1SoC_SevenSeg_Write(display,0x07);//light segment 0,1,2
		}
		if (value==8){
			DE1SoC_SevenSeg_Write(display,0x7F);// light all segment
		}
		if (value==9){
			DE1SoC_SevenSeg_Write(display,0x67);// light segment 0,1,2,5,6
		}
		if (value==0x0A){
			DE1SoC_SevenSeg_Write(display,0x77);// light segment 0,1,2,4,5,6
		}
		if (value==0x0B){
			DE1SoC_SevenSeg_Write(display,0x7C);//light segment 2,3,4,5,6
		}
		if (value==0x0C){
			DE1SoC_SevenSeg_Write(display,0x39);//light segment 0,3,4,5
		}
		if (value==0x0D){
			DE1SoC_SevenSeg_Write(display,0x5E);//light segment 1,2,3,4,6
		}
		if (value==0x0E){
			DE1SoC_SevenSeg_Write(display,0x79);// light segment 0,3,4,5,6
		}
		if (value==0x0F){
			DE1SoC_SevenSeg_Write(display,0x71);// light segment 0,4,5,6
		}
		if (value>0x0F){
			DE1SoC_SevenSeg_Write(display,0x40);// light segment 6 only
		}
	}


void DE1SoC_SevenSeg_SetDoubleHex(unsigned int display, unsigned int value) {
    // ToDo: Write the code for setting a pair of seven segment displays
    // here. Good coding practice suggests your solution should call
    // DE1SoC_SevenSeg_SetSingle() twice.
    // This function should show the first digit of a HEXADECIMAL number on
    // the specified 'display', and the second digit on the display to
    // the left of the specified display.

	unsigned int valuefH=value%16;// take the first bit of the input number
	unsigned int valuesH=value/16;// take the second bit of the input number
	DE1SoC_SevenSeg_SetSingle(display, valuefH);// light the first bit number in the display by setsingle function
	DE1SoC_SevenSeg_SetSingle(display+1, valuesH);// light the second bit number in the display by setsingle functin
    /** Some examples:
     *
     *    input | output | HEX(N+1) | HEX(N)
     *    ----- | ------ | -------- | ------
     *        5 |     05 |        0 |      5
     *       30 |     1E |        1 |      E
     *     0x60 |     60 |        6 |      0
     */
}

void DE1SoC_SevenSeg_SetDoubleDec(unsigned int display, unsigned int value) {
    // ToDo: Write the code for setting a pair of seven segment displays
    // here. Good coding practice suggests your solution should call
    // DE1SoC_SevenSeg_SetSingle() twice.
    // This function should show the first digit of a DECIMAL number on
    // the specified 'display', and the second digit on the display to
    // the left of the specified display.
	unsigned int valuefD=value%10;//take the first bit of the input number
	unsigned int valuesD=value/10;//take the second bit of the input number
	DE1SoC_SevenSeg_SetSingle(display, valuefD);//light the first bit number in the display by setsingle function
	DE1SoC_SevenSeg_SetSingle(display+1, valuesD);//light the second bit number in the display by setsingle function
    /** Some examples:
     *
     *	  input | output | HEX(N+1) | HEX(N)
     *    ----- | ------ | -------- | ------
     *        5 |     05 |        0 |      5
     *       30 |     30 |        3 |      0
     *     0x90 |     5A |        5 |      A
     */
}
