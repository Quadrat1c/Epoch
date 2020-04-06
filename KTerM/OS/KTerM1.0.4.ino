/*
 * KTerM v1.0.4
 * Atmega328 Operating System
 * Designed to run the KTerM IC Computer
 * This is designed to demo the KTerMR1 PCB Board and test functionality of Multitasking.
 * 
 * Features:
 *      - Multitasking (ISR) Interrupt Service Routine
 *      [Under Development] Multithreading (With multiple Atmega Chips)
 * 
 * Revisions:
 *  v1.0.1
 *      - Clock Speed fix. Can now go from 0-9999 without errors or command length issues.
 *  v1.0.2
 *      - Cleaned up lots of things
 *  v1.0.3
 *      - Added multiple files to organize code
 */

// Global Variables
bool IsDebug = false;   // Debug mode shows command bytes
int incomingByte = 0;   // Each byte is recieved one at a time through serial
int command[20];        // Command Array
int cmdIndex = 0;       // Keeps track of command array index
String cmdStr = "";
String ver = "1.0.4";
int clockTicks = 0;
bool IsClockLED = false;

// Pins
int clockLED = 13,      // COUT clock output
    redPin = 6,         // RGB LED Red
    grnPin = 7,         // RGB LED Green
    bluPin = 8;         // RGB LED Blue

// Task Scheduler (Interrupt Service Routine)
int TaskTimer1 = 0,
    TaskTimer2 = 0,
    TaskTimer3 = 0;
// Task Check Delay
int TaskDelay1 = 300,   // Lower number is faster. Higher is slower tick rate.
    TaskDelay2 = 5,     // 5mS
    TaskDelay3 = 5;     // 5mS
// Task Flags
bool TaskFlag1 = false,
     TaskFlag2 = false,
     TaskFlag3 = false;

// Initialization
void setup () {
    Serial.begin(9600);     // Serial port baud rate
    
    pinMode(clockLED, OUTPUT);      // Define clockLED pin for OUTPUT
    digitalWrite(clockLED, LOW);    // make sure clockLED is off

    // Configure Timer 2 to generate a compare-match interrupt every 1mS
    noInterrupts();            // disable interrupts
    TCCR2A = 0;                // clear control registers
    TCCR2B = 0;
    TCCR2B |= (1 << CS22) |    // 16MHz/128=8uS
            (1 << CS20) ;
    TCNT2 = 0;                 // clear counter
    OCR2A = 125 - 1;           // 8uS*125=1mS (allow for clock propagation)
    TIMSK2 |= (1 << OCIE2A);   // enable output compare interrupt
    interrupts();              // enable interrupts
}

// Main Loop
void loop() {
    // Run Clock LED
    if (TaskFlag1) {
        TaskFlag1 = false;
        if (IsClockLED) {
            digitalWrite(clockLED, LOW);
            IsClockLED = false;
        } else {
            digitalWrite(clockLED, HIGH);
            IsClockLED = true;
            clockTicks++;
        }
        //digitalWrite(clockLED, !digitalRead(clockLED));
    }

    if (TaskFlag2) {
        TaskFlag2 = false;
        // Do Something
        //Serial.println("Tick");
    }

    if (TaskFlag3) {
        TaskFlag3 = false;
        // Check if serial is available
        if (Serial.available() > 0)
        {
            // start command routine
            incomingByte = Serial.read();
        
            if (incomingByte == 59) // detect if byte is a Semicolon (the end of the command ;)
            {
                CmdReceived();
            }
            else if (incomingByte == 10)    // detect if byte is Enter clean everything up cmd routine has finished
            {
                CmdComplete();
            }
            else    // follow cmdIndex and add the full command to array
            {
                //Serial.println(incomingByte);
                setColor(0,0,255);
                command[cmdIndex] = incomingByte;
                cmdIndex++;
            }
        }
    }
}

// -------------------------------
// task scheduler (1mS interrupt)
// -------------------------------
ISR(TIMER2_COMPA_vect)
{
    // each timer counts the number of milliseconds since 
    // its associated task was last performed.
    // each additional task requires another timer and flag
    TaskTimer1++;
    TaskTimer2++;
    TaskTimer3++;

    if (TaskTimer1 > TaskDelay1 - 1) {
        TaskTimer1 = 0;
        TaskFlag1 = true;
    }

    if (TaskTimer2 > TaskDelay2 - 1) {
        TaskTimer2 = 0;
        TaskFlag2 = true;
    }

    if (TaskTimer3 > TaskDelay3 - 1) {
        TaskTimer3 = 0;
        TaskFlag3 = true;
    }
}
