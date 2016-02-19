/*
 * File:   lcd.c
 * Authors:
 *
 * Created on December 31, 2014, 1:39 PM
 */

/* TODO: Make define statements for each pin used in the LCD
 */
#include <xc.h>
#include "lcd.h"
#include "timer.h"

#define OUTPUT 0
#define ON 1
#define OFF 0
#define LOWER 1
#define UPPER 0
#define LCD_WRITE_MODE 1
#define LCD_READ_MODE 0


/* The pins that you will use for the lcd control will be
 * TRISCbits.TRISC4      RC4
 * LCD_E       RC2
 * LCD_D4      RE7
 * LCD_D5      RE5
 * LCD_D6      RE3
 * LCD_D7      RE1
 * Use these so that we will be able to test your code for grading and to
 * help you debug your implementation!
 */

/*#define LCD_DATA TRISE
#define LCD_RS TRISCbits.TRISC4
#define LCD_E TRISCbits.TRISC2

#define TRIS_D4 LATEbits.LATE4
#define TRIS_D5 LATEbits.LATE5
#define TRIS_D6 LATEbits.LATE6
#define TRIS_D7 LATEbits.LATE7
#define TRIS_RS LATCbits.LATC4
#define TRIS_E LATCbits.LATC2*/

/* This function should take in a two-byte word and writes either the lower or upper
 * byte to the last four bits of LATE. Additionally, according to the LCD data sheet
 * It should set TRISCbits.TRISC4 and LCD_E with the appropriate values and delays.
 * After these commands are issued, there should be a delay.
 * The command type is a simplification. From the data sheet, the RS is '1'
 * when you are simply writing a character. Otherwise, RS is '0'.
 */


void writeFourBits(unsigned char word, unsigned int commandType, unsigned int delayAfter, unsigned int lower){
    //TODO:
    // set the commandType (RS value)
    // WTF is this here for we are supposed to use 4 bit mode and you have LATE 0, 2, 4, and 6 when you tell us to use the ODD registers
    //LATEbits.LATE0 = word&0x01; 
    //LATEbits.LATE2 = word&0x02;
    //LATEbits.LATE4 = word&0x04;
    //LATEbits.LATE6 = word&0x08;
    if(lower){ // set least sig bits
        LATEbits.LATE4 = word & 0x01;
        LATEbits.LATE5 = (word >> 1) & 0x01;
        LATEbits.LATE6 = (word >> 2) & 0x01;
        LATEbits.LATE7 = (word >> 3) & 0x01;
    }
    else{ // set most sig figs
        LATEbits.LATE4 = (word >> 4) & 0x01;
        LATEbits.LATE5 = (word >> 5) & 0x01;
        LATEbits.LATE6 = (word >> 6) & 0x01;
        LATEbits.LATE7 = (word >> 7) & 0x01;
    }
    LATCbits.LATC4 = commandType; // 1 for write 0 for read,  LCD_RW
    //enable
    LATCbits.LATC2 = 1; // This allows reading of data into LCD mem,  LCD_E
    //delay
    delayUs(10);
    //disable
    LATCbits.LATC2 = 0; // Finishes writing data, LCD_E
    delayUs(10);
    delayUs(delayAfter);
}

/* Using writeFourBits, this function should write the two bytes of a character
 * to the LCD.
 */
void writeLCD(unsigned char word, unsigned int commandType, unsigned int delayAfter){
    //TODO:
    writeFourBits(word, commandType, delayAfter, UPPER); // Writes upper 4 bits of work into LCD mem
    writeFourBits(word, commandType, delayAfter, LOWER); // Writes lower 4 bits of work into LCD mem
}

/* Given a character, write it to the LCD. RS should be set to the appropriate value.
 */
void printCharLCD(char c) {
    //TODO:
    writeLCD(c, LCD_WRITE_MODE, 46); // WRITES a character to LCD
}

/*Initialize the LCD
 */
void initLCD(void) {
    // Setup D, RS, and E to be outputs (0).
    
    //TRISE = OUTPUT;
    TRISCbits.TRISC4 = OUTPUT; // LCD_RS output
    TRISCbits.TRISC2 = OUTPUT; // LCD_E
    //LATC = OUTPUT;
    TRISEbits.TRISE4 = OUTPUT;
    TRISEbits.TRISE5 = OUTPUT;
    TRISEbits.TRISE6 = OUTPUT;
    TRISEbits.TRISE7 = OUTPUT;
    
    
    /*while(1){
    LATEbits.LATE4 = 1;
    LATEbits.LATE5 = 1;
    LATEbits.LATE6 = 1;
    LATEbits.LATE7 = 1;
    LATCbits.LATC4 = 1;
    LATCbits.LATC2 = 1;
    }//*/
    
    LATEbits.LATE4 = 1;
    LATEbits.LATE5 = 1;
    LATEbits.LATE6 = 0;
    LATEbits.LATE7 = 0;
    LATCbits.LATC4 = 0;
    LATCbits.LATC2 = 1;
    delayUs(40);
    LATCbits.LATC2 = 0;//*/
    delayUs(210);
    delayUs(210);
    delayUs(210);
    delayUs(210);
    delayUs(210);
    delayUs(210);
    delayUs(210);
    delayUs(210);
    delayUs(210);
    delayUs(210);
    delayUs(210);
    delayUs(210);
    delayUs(210);
    delayUs(210);
    delayUs(210);
    delayUs(210);
    delayUs(210);
    delayUs(210);
    delayUs(210);
    delayUs(210);
    delayUs(210);//*/
    //LATCbits.LATC2 = 0;//*/
    delayUs(210);
    delayUs(210);
    delayUs(210);
    LATCbits.LATC2 = 1;
    delayUs(210);
    LATCbits.LATC2 = 0;//*/
    delayUs(210);
    delayUs(210);
    delayUs(210);
    LATCbits.LATC2 = 1;
    delayUs(210);
    LATCbits.LATC2 = 0;//*/
    
    // Initialization sequence utilizes specific LCD commands before the general configuration
    // commands can be utilized. The first few initialization commands cannot be done using the
    // WriteLCD function. Additionally, the specific sequence and timing is very important.
    
    // Enable 4-bit interface
    // Initialization line/code for setting as 4Bit interface
    LATEbits.LATE4 = 0;
    LATEbits.LATE5 = 1;
    LATEbits.LATE6 = 0;
    LATEbits.LATE7 = 0;
    LATCbits.LATC4 = 0;
    LATCbits.LATC2 = 1;
    delayUs(40);
    LATCbits.LATC2 = 0;//*/
    // Delay for
    delayUs(40);
        
    // Function Set (specifies data width, lines, and font.
    LATEbits.LATE4 = 0;
    LATEbits.LATE5 = 1;
    LATEbits.LATE6 = 0;
    LATEbits.LATE7 = 0;
    LATCbits.LATC4 = 0;
    LATCbits.LATC2 = 1;
    delayUs(40);
    //LATCbits.LATC2 = 0;//*/
    // Delay for
    delayUs(40);
    
    LATEbits.LATE4 = 0;
    LATEbits.LATE5 = 0;
    LATEbits.LATE6 = 0;
    LATEbits.LATE7 = 0;
    LATCbits.LATC4 = 0;
    LATCbits.LATC2 = 1;
    delayUs(40);
    LATCbits.LATC2 = 0;//*/
    // Delay for
    delayUs(210);
    delayUs(210);
    delayUs(210);
    delayUs(210);
    delayUs(210);

    // 4-bit mode initialization is complete. We can now configure the various LCD
    // options to control how the LCD will function.
    // TODO: Display On/Off Control
    LATEbits.LATE4 = 0;
    LATEbits.LATE5 = 0;
    LATEbits.LATE6 = 0;
    LATEbits.LATE7 = 0;
    LATCbits.LATC4 = 0;
    LATCbits.LATC2 = 1;
    delayUs(40);
    //LATCbits.LATC2 = 0;//*/
    // Delay for
    delayUs(40);
    LATEbits.LATE4 = 0;
    LATEbits.LATE5 = 0;
    LATEbits.LATE6 = 0;
    LATEbits.LATE7 = 1;
    LATCbits.LATC4 = 0;
    LATCbits.LATC2 = 1;
    delayUs(40);
    LATCbits.LATC2 = 0;//*/
    // Delay for
    delayUs(210);
    delayUs(210);
    delayUs(210);
    delayUs(210);
    delayUs(210);
    // Turn Display (D) Off
    
    // clear
    LATEbits.LATE4 = 0;
    LATEbits.LATE5 = 0;
    LATEbits.LATE6 = 0;
    LATEbits.LATE7 = 0;
    LATCbits.LATC4 = 0;
    LATCbits.LATC2 = 1;
    delayUs(40);
    //LATCbits.LATC2 = 0;//*/
    // Delay for
    delayUs(40);
    LATEbits.LATE4 = 1;
    LATEbits.LATE5 = 0;
    LATEbits.LATE6 = 0;
    LATEbits.LATE7 = 0;
    LATCbits.LATC4 = 0;
    LATCbits.LATC2 = 1;
    delayUs(40);
    LATCbits.LATC2 = 0;//*/
    // Delay for
    delayUs(210);
    delayUs(210);
    delayUs(210);
    delayUs(210);
    delayUs(210);
    // done clearing
    // TODO: Clear Display (The delay is not specified in the data sheet at this point. You really need to have the clear display delay here.
    
    // TODO: Entry Mode Set
        // Set Increment Display, No Shift (i.e. cursor move)
    LATEbits.LATE4 = 0;
    LATEbits.LATE5 = 0;
    LATEbits.LATE6 = 0;
    LATEbits.LATE7 = 0;
    LATCbits.LATC4 = 0;
    LATCbits.LATC2 = 1;
    delayUs(40);
    //LATCbits.LATC2 = 0;//*/
    // Delay for
    delayUs(40);
    LATEbits.LATE4 = 0;
    LATEbits.LATE5 = 1;
    LATEbits.LATE6 = 1;
    LATEbits.LATE7 = 0;
    LATCbits.LATC4 = 0;
    LATCbits.LATC2 = 1;
    delayUs(40);
    LATCbits.LATC2 = 0;//*/
    // Delay for
    delayUs(210);
    delayUs(210);
    delayUs(210);
    /*while(1){
    delayUs(210);
    delayUs(210);
    LATEbits.LATE4 = 0;
    LATEbits.LATE5 = 0;
    LATEbits.LATE6 = 0;
    LATEbits.LATE7 = 0;
    LATCbits.LATC4 = 0;
    LATCbits.LATC2 = 1;
    delayUs(210);
    delayUs(210);
    //LATCbits.LATC2 = 0;
    delayUs(210);
    delayUs(210);
    LATEbits.LATE4 = 1;
    LATEbits.LATE5 = 0;
    LATEbits.LATE6 = 0;
    LATEbits.LATE7 = 0;
    LATCbits.LATC4 = 0;
    LATCbits.LATC2 = 1;
    delayUs(210);
    delayUs(210);
    LATCbits.LATC2 = 0;}//*/
    // input mode set
    // TODO: Display On/Off Control
        // Turn Display (D) On, Cursor (C) Off, and Blink(B) Off
}

/*
 * You can use printCharLCD here. Note that every time you write a character
 * the cursor increments its position automatically.
 * Since a string is just a character array, try to be clever with your use of pointers.
 */
void printStringLCD(const char* s) {
    //TODO:
}

/*
 * Clear the display.
 */
void clearLCD(){
}

/*
 Use the command for changing the DD RAM address to put the cursor somewhere.
 */
void moveCursorLCD(unsigned char x, unsigned char y){
}

/*
 * This function is called in lab1p2.c for testing purposes.
 * If everything is working properly, you should get this to look like the video on D2L
 * However, it is suggested that you test more than just this one function.
 */
void testLCD(){
    initLCD();
    //while(1){
        /*delayUs(210);
        delayUs(210);
        delayUs(210);
        delayUs(210);
        delayUs(210);
        delayUs(210);
        delayUs(210);*/
        delayUs(200);
        LATEbits.LATE4 = 0;
        LATEbits.LATE5 = 1;
        LATEbits.LATE6 = 0;
        LATEbits.LATE7 = 0;

        LATCbits.LATC4 = 1; // 1 for write 0 for read,  LCD_RW
        //enable
        delayUs(1);
        LATCbits.LATC2 = 1; // This allows reading of data into LCD mem,  LCD_E
        //delay
        delayUs(40);
        //disable
        //LATCbits.LATC2 = 0; // Finishes writing data, LCD_E
        delayUs(1000);
        LATEbits.LATE4 = 0;
        LATEbits.LATE5 = 0;
        LATEbits.LATE6 = 1;
        LATEbits.LATE7 = 1;
        //enable
        //LATCbits.LATC2 = 1; // This allows reading of data into LCD mem,  LCD_E
        //delay
        delayUs(100);
        //disable
        LATCbits.LATC2 = 0; // Finishes writing data, LCD_E
    //}
    //delayUs(100000000);//*/
    //int i = 0;
    printCharLCD('c');
    /*for(i = 0; i < 1000; i++) delayUs(1000);
    clearLCD();
    printStringLCD("Hello!");
    moveCursorLCD(1, 2);
    for(i = 0; i < 1000; i++) delayUs(1000);
    printStringLCD("Hello!");
    for(i = 0; i < 1000; i++) delayUs(1000);*/
}