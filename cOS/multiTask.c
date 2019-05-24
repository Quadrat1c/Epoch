/*
 *  ArduinOS
 *  Operating System for Arduino's
 *      - Multitasking (Interrupt Service Routine)
 *      - Multithreading (With multiple Atmega Chips)
 *      
 *  Coded ßy: Quadrat1c
 */

// message testing
char
MessageArray[] = "               Multi-tasking DEMO:     The arduino is controlling the LED, the text, and the custom bar graph.                ";
int
MessageLength = strlen(MessageArray);
String
Message = MessageArray,
Display;

// public variables
bool IsDebug = false;
int ClockSpeed = 70;
int incomingByte = 0;   // each byte is recieved one at a time through serial
int command[20];        // commad array
int cmdIndex = 0;       // keep track of command array index
String cmdStr = "";

// LED Pins
int 
clockLED = 2,
redPin = 7,
greenPin = 6,
bluePin = 5;

// task scheduler (Interrupt Service Routine)
int
TaskTimer1 = 0,
TaskTimer2 = 0,
TaskTimer3 = 0;

// task check delay
int
TaskDelay1 = 300,   // 300mS
TaskDelay2 = 250,   // 250mS
TaskDelay3 = 100;   // 100mS

bool
TaskFlag1 = false,
TaskFlag2 = false,
TaskFlag3 = false;

void setup() {
    Serial.begin(9600); // serial port baud rate
    
    pinMode(clockLED, OUTPUT);
    digitalWrite(clockLED, LOW);
    
    // ----- configure Timer 2 to generate a compare-match interrupt every 1mS
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

void loop() {
    // toggle clock LED
    if (TaskFlag1) {
        TaskFlag1 = false;
        digitalWrite(clockLED, !digitalRead(clockLED));
    }
    
    if (TaskFlag2) {
        TaskFlag2 = false;
        //scrollMessage();
    }
    
    if (TaskFlag3) {
        TaskFlag3 = false;
        // check if serial is available
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

void setColor(int redValue, int greenValue, int blueValue)
{
    analogWrite(redPin, redValue);
    analogWrite(greenPin, greenValue);
    analogWrite(bluePin, blueValue);
}

void CmdReceived() // Semicolon
{
    setColor(150,150,0);
    if (IsDebug)
    {
        Serial.println("");
        Serial.println("Command Received");
    }
    
    // print full command array
    for (int i = 0; i < 20; i++)
    {
        if (IsDebug) {
            Serial.print(command[i]);
        }
        cmdStr += decToString(command[i]);
    }
    
    Serial.println("");
    Serial.println(cmdStr);
    
    setColor(0,0,0);
    RunCommand(cmdStr);
}

void CmdComplete() // Enter
{
    // reset command array & cmdIndex to 0's
    for (int i = 0; i < 20; i++)
    {
        command[i] = 0;
        cmdIndex = 0;
        setColor(0,0,0);
        cmdStr = "";
    }
    //Serial.println("");
    //Serial.println("Command & Index Reset");
}

void RunCommand(String cmd)
{
    if (cmd == "help")
    {
        setColor(0,255,0);
        Serial.println("");
        Serial.println("Help - List of commands");
        Serial.println("debug - Turn Debug Mode ON or OFF");
        Serial.println("clock - Change Clock Speed 70-9999");
        setColor(0,0,0);
    }
    else if (cmd == "debug")
    {
        setColor(0,255,0);
        if (IsDebug) 
        {
            IsDebug = false;
            Serial.println("");
            Serial.println("Debug mode OFF");
        }
        else if (!IsDebug)
        {
            IsDebug = true;
            Serial.println("");
            Serial.println("Debug mode ON");
        }
        setColor(0,0,0);
    }
    else if (cmd == "clock")
    {
        setColor(0,255,0);
        Serial.println("Type in a clock speed 70-9999, lower = faster");
        bool clockComplete = false;
        int clockCmdIndex = 0;
        int clockCommand[4];
        String clockCmdStr = "";

        while (!clockComplete)
        {
            if (Serial.available() > 0)
            {
                // start command routine
                incomingByte = Serial.read();
                setColor(100,100,100);
                clockCommand[clockCmdIndex] = incomingByte;
                clockCmdIndex++;
            }

            if (clockCmdIndex >= 4)
            {
                // print full command array
                for (int i = 0; i < 4; i++)
                {
                    clockCmdStr += decToString(clockCommand[i]);
                }
                
                ClockSpeed = clockCmdStr.toInt();
                Serial.println("");
                Serial.println(ClockSpeed);

                if (ClockSpeed < 70) { ClockSpeed = 70; }
                if (ClockSpeed > 9999) { ClockSpeed = 9999; }
                clockComplete = true;
            }
        }
        
        setColor(0,0,0);
    }
    else
    {
        setColor(255,0,0);
        Serial.println("Unknown Command: " + cmd);
        setColor(0,0,0);
    }
}

// ----------------------------
// displayMessage()
// ----------------------------
void scrollMessage() {
  // ----- locals
  /*
     static variables remember the last value
     when the subroutine is re-entered.
  */
  static int index = 0;
  
  Display = Message.substring(index, index + 16);
  Serial.print(Display);
  index++;
  if (index > MessageLength - 15) index = 0;
}

String decToString(int decimal)
{
    switch (decimal)
    {
        // operators
        case 42: return "*"; break;
        case 43: return "+"; break;
        case 45: return "-"; break;
        case 46: return "."; break;
        case 47: return "/"; break;
        // numbers
        case 48: return "0"; break;
        case 49: return "1"; break;
        case 50: return "2"; break;
        case 51: return "3"; break;
        case 52: return "4"; break;
        case 53: return "5"; break;
        case 54: return "6"; break;
        case 55: return "7"; break;
        case 56: return "8"; break;
        case 57: return "9"; break;
        // letters
        case 97: return "a"; break;
        case 98: return "b"; break;
        case 99: return "c"; break;
        case 100: return "d"; break;
        case 101: return "e"; break;
        case 102: return "f"; break;
        case 103: return "g"; break;
        case 104: return "h"; break;
        case 105: return "i"; break;
        case 106: return "j"; break;
        case 107: return "k"; break;
        case 108: return "l"; break;
        case 109: return "m"; break;
        case 110: return "n"; break;
        case 111: return "o"; break;
        case 112: return "p"; break;
        case 113: return "q"; break;
        case 114: return "r"; break;
        case 115: return "s"; break;
        case 116: return "t"; break;
        case 117: return "u"; break;
        case 118: return "v"; break;
        case 119: return "w"; break;
        case 120: return "x"; break;
        case 121: return "y"; break;
        case 122: return "z"; break;
        // default
        default: return ""; break;
    }
}
