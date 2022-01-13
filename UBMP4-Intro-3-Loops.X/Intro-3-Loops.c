/*==============================================================================
 Project: UBMP4-Simon-Starter
 Date:    January 12, 2022
 
  A Simon-style pattern matching game starter framework.
 ==============================================================================*/
 
#include    "xc.h"              // Microchip XC8 compiler include file
#include    "stdint.h"          // Include integer definitions
#include    "stdbool.h"         // Include Boolean (true/false) definitions
 
#include    "UBMP4.h"           // Include UBMP4 constants and functions
 
// TODO Set linker ROM ranges to 'default,-0-7FF' under "Memory model" pull-down.
// TODO Set linker code offset to '800' under "Additional options" pull-down.
 
// Program constants
#define pressed 0               // Switch pressed logic state
#define timeOut 2400            // Idle shutdown time-out duration * 50ms (1200/min)
#define patternLength 42        // Total number of pattern steps to match
 
// Set up program variables
__persistent unsigned char randomSeed;  // Random seed updated from TMR0
unsigned char button;           // Button ID (0 = none, 1 = S1, etc.)
unsigned char pattern[patternLength];	// Pattern sequence storage
unsigned char step = 0;         // Current step (pattern sequence index) counter
unsigned char maxStep = 0;      // Highest step achieved by player
unsigned int idle = 0;          // In-game idle timer for shutdown
 
// Define program functions
extern int rand();              // Declarations for random number generation
extern void srand(unsigned int);
unsigned int newSeed;           // New random number generator seed values
 
/*==============================================================================
 Interrupt function. Processes IOC interrupts and wakes game from nap/sleep.
 =============================================================================*/
 
void __interrupt() wake(void)
{
    di();                       // Disable interrupts
	if(IOCIF == 1 && IOCIE == 1)	// Check for IOC interrupt
	{
        IOCAF = 0;              // Clear IOC port A interrupt flag
        IOCBF = 0;              // Clear IOC port B interrupt flag
        IOCIF = 0;				// Clear IOC interrupt flag
	}
	else
    {
        IOCAN = 0b00001000;     // Other interrupt? Only allow IOC on pushbuttons
        IOCBN = 0b11110000;
		INTCON = 0b00001000;
    }
	return;
}
 
void nap(void)
{
    LED1 = 1;                   // Turn all LEDs off
    LATC = 0;
    IOCAF = 0;                  // Clear S1 IOC interrupt flag
    IOCBF = 0;                  // Clear S2-S5 IOC interrupt flags
    IOCIF = 0;                  // Clear global IOC interrupt flag
    ei();                       // Enable interrupts
    SLEEP();
 
    RESET();                    // Restart processor after wake-up
}
    
/*==============================================================================
 getButton function. Return the code of a pressed button. 0 = no button.
 =============================================================================*/
 
unsigned char getButton(void)       // Return code of pressed button or 0 if
{                                   // no buttons are pressed
 
}
 
/*==============================================================================
 LED function. Light one of the 4 LEDs. 0 = all LEDs off.
==============================================================================*/
 
void LED(unsigned char num)
{
 
}
 
/*==============================================================================
 Music note functions. Plays note for requested cycles of time period.
 =============================================================================*/
 
void noteE5(unsigned int per)   // Plays note E5 for requested number of cycles
{
    for(per; per != 0; per--)
    {
        BEEPER = !BEEPER;
        __delay_us(758);
    }
}
 
void noteCS6(unsigned int per)   // Plays note C#6 for requested number of cycles
{
    for(per; per != 0; per--)
    {
        BEEPER = !BEEPER;
        __delay_us(451);
    }
}
 
void noteA5(unsigned int per)   // Plays note A5 for requested number of cycles
{
    for(per; per != 0; per--)
    {
        BEEPER = !BEEPER;
        __delay_us(568);
    }
}
 
void noteE6(unsigned int per)   // Plays note E6 for requested number of cycles
{
    for(per; per != 0; per--)
    {
        BEEPER = !BEEPER;
        __delay_us(379);
    }
}
 
/*==============================================================================
 Sound functions. 
 =============================================================================*/
 
void sound(unsigned char num)   // Play selected note sound
{
	if(num == 1)
        noteE5(379);
	else if(num == 2)
		noteCS6(568);
	else if(num == 3)
		noteE6(758);
	else if(num == 4)
		noteA5(451);	
}
 
void startSound(void)           // Game start-up sound
{
 
}
 
void win(void)                  // Game win function
{
 
	nap();                      // Shutdown
}
 
void lose(void)                 // Pattern fail. Game lose function
{
                                // Sounds, lights?
                                // Show score?
	nap();                      // Power down
}
 
/*==============================================================================
	Main program loop. The main() function is executed on power-up and reset.
==============================================================================*/
 
int main(void)
{
    OSC_config();               // Configure internal oscillator for 48 MHz
    UBMP4_config();             // Configure on-board UBMP4 I/O devices
    
//    LED1 = 1;                   // Wait for a button press
//    while(SW2 == !pressed && SW3 == !pressed && SW4 == !pressed && SW5 == !pressed);
//    LED1 = 0;                   // LED on, play start sound
//    startSound();
//    while(SW2 == pressed || SW3 == pressed || SW4 == pressed || SW5 == pressed);
 
    // Initialize the random number generator
    randomSeed = TMR0;   		// Generate random number from timer
	newSeed = (newSeed << 8 ) | randomSeed; // Mix previous seed with random sample
	srand(newSeed);             // Seed random number generator
    
	maxStep = 0;                // Reset user's max step
    
	while(1)					// Loop continuously until win, lose or shutdown
	{
        // Button and light test code
        
		button = getButton();   // Button test code
		LED(button);
        sound(button);
		LED(0);
 
        // Activate bootloader if SW1 is pressed.
        if(SW1 == 0)
        {
            RESET();
        }
 
        // Add a new step and play the pattern for the user
        
//		__delay_ms(1000);       // Delay before playing next pattern
//		pattern[maxStep] = (rand() & 0b00000011) + 1;   // Pick next pattern step
//		maxStep++;              // Increase step count and check if user won
//		if(maxStep == (patternLength + 1))       
//			win();
//		for(step = 0; step != maxStep; step++)  // Play each pattern step
//		{
//			LED(pattern[step]);
//			sound(pattern[step]);
//			LED(0);
//			__delay_ms(500);
//		}
		
        // Let user repeat the pattern, comparing each step to the saved pattern
        
 
	}
}
 
