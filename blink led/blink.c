#include <reg51.h>

// Define LED connected to Port 1, Pin 0
sbit LED = P1^0; 

// Function to generate a 1ms delay (using Timer 0)
// Calculation for 12MHz crystal: (65536 - 1000) = 64536 = 0xFC18
void delay_1ms() {
    TMOD &= 0xF0; // Clear Timer 0 config
    TMOD |= 0x01; // Set Timer 0 to Mode 1 (16-bit)
    
    TH0 = 0xFC;   // Load High byte
    TL0 = 0x18;   // Load Low byte
    
    TR0 = 1;      // Start Timer 0
    while (!TF0); // Wait for overflow
    
    TR0 = 0;      // Stop Timer 0
    TF0 = 0;      // Clear overflow flag
}

// Function to generate a delay in milliseconds
void delay_ms(unsigned int ms) {
    unsigned int i;
    for(i = 0; i < ms; i++) {
        delay_1ms();
    }
}

void main() {
    LED = 0; // Ensure initial state is off (or on, depending on your circuit)
    
    while (1) {
        LED = ~LED;     // Toggle the LED
        delay_ms(2000);  // Delay for 500ms (Half a second)
    }
}