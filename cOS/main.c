/*
 * ArduinOS
 * Operating System for Arduino's
 * Coded by: Quadrat1c
 */

// public variables
bool IsDebug = false;
int ClockSpeed = 70;
int incomingByte = 0;   // each byte is recieved one at a time through serial
int command[20];        // commad array
int cmdIndex = 0;       // keep track of command array index
String cmdStr = "";
// pins
int clockLED = 2;
int redPin = 7;
int greenPin = 6;
int bluePin = 5;

// initialize
void setup()
{
    Serial.begin(9600); // set serial baudrate at 9600bps
    pinMode(clockLED, OUTPUT);
}

// main loop
void loop()
{
    // turn clock led on/off
    digitalWrite(clockLED, HIGH);
    delay(ClockSpeed);
    digitalWrite(clockLED, LOW);
    delay(ClockSpeed);
    
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
    
    delay(70);
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
        delay(500);
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
        delay(500);
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
        delay(500);
        setColor(0,0,0);
    }
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
