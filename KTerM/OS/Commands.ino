void cmdHelp() {
    setColor(0,255,0);
    Serial.println("help; - List of commands");
    Serial.println("about; - About KTerM and Version");
    Serial.println("var; - show list of variables and values");
    Serial.print("debug; - Turn Debug Mode ON or OFF");
    Serial.print(" [Debug Mode]: ");
    Serial.println(IsDebug);
    Serial.print("clock; - Change Clock Speed 0-9999");
    Serial.print(" [Current Clock Speed]: ");
    Serial.println(TaskDelay1);
    Serial.print("[Clock Ticks]: ");
    Serial.println(clockTicks);
    Serial.println("eepr; - Read EEPROM memory location");
    Serial.println("eepw; - Write EEPROM memory location");
    Serial.println("eepu; - Update EEPROM memory location");
    setColor(0,0,0);
}

void cmdAbout() {
    setColor(0,255,0);
    Serial.println("KTerM is an IC Based Terminal Computer and Operating System for the Atmega328 Chip.");
    Serial.print("Version: ");
    Serial.println(ver);
    Serial.println("Developed by: Kyle Muranyi");
    setColor(0,0,0);
}

void cmdVar() {
    setColor(0,255,0);
    Serial.println("Variable Command");
    setColor(0,0,0);
}

void cmdDebug() {
    setColor(0,255,0);
    if (IsDebug) {
        IsDebug = false;
        Serial.println("Debug mode OFF");
    } else if (!IsDebug) {
        IsDebug = true;
        Serial.println("Debug mode ON");
    }
    setColor(0,0,0);
}

void cmdEEPR() {
    setColor(0,255,0);
    eRomRead(0);
    setColor(0,0,0);
}

void cmdEEPW() {
    setColor(0,255,0);
    eRomWrite(0, 0);
    setColor(0,0,0);
}

void cmdEEPU() {
    setColor(0,255,0);
    eRomUpdate(0, 0);
    setColor(0,0,0);
}

void cmdClock() {
    setColor(0,255,0);
    Serial.print("Current Clock Speed: ");
    Serial.println(TaskDelay1);
    Serial.println("Type in a clock speed 0-9999, lower = faster");
    Serial.println("All commands must end with ;");
    Serial.println("Example Clock Speed: 155;");

    bool clockComplete = false;
    int clockCmdIndex = 0;
    int clockCommand[4];
    String clockCmdStr = "";

    while (!clockComplete) {
        if (Serial.available() > 0) {
            incomingByte = Serial.read();   // Read incoming bytes
            
            if (incomingByte == 59) {       // Detect if byte is a Semicolon (the end of the command ;)
                for (int i = 0; i < 4; i++) {
                    if (IsDebug) {
                        Serial.print(clockCommand[i]);
                    }
                    clockCmdStr += decToString(clockCommand[i]);
                }

                Serial.println("");
                Serial.print("Clock Updated: ");
                Serial.println(clockCmdStr.toInt());
                TaskDelay1 = clockCmdStr.toInt();
                clockComplete = true;
            }
            
            else if (incomingByte == 10) {  // Detect if byte is Enter then clean everything up cmd routine has finished
                for (int i = 0; i < 4; i++) {
                    clockCommand[i] = 0;
                    clockCmdIndex = 0;
                    setColor(0,0,0);
                    clockCmdStr = "";
                }
            } else {  // follow clockCmdIndex and add the full command to array
                //Serial.println(incomingByte);
                setColor(100,100,100);
                clockCommand[clockCmdIndex] = incomingByte;
                clockCmdIndex++;
            }
        }
    }
    setColor(0,0,0);
}

void CmdReceived() {    // put a Semicolon at the end of commands
    setColor(150,150,0);
    if (IsDebug) {
        Serial.println("");
        Serial.println("Command Received");
    }

    // Print full command array
    for (int i = 0; i < 20; i++) {
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

void CmdComplete() { // Enter 
    // reset command array & cmdIndex to 0's
    for (int i = 0; i < 20; i++) {
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
    if (cmd == "help") { cmdHelp(); } 
    else if (cmd == "about") { cmdAbout(); } 
    else if (cmd == "debug") { cmdDebug(); } 
    else if (cmd == "clock") { cmdClock(); }
    else if (cmd == "var")   { cmdVar(); }
    else if (cmd == "eepr")   { cmdEEPR(); }
    else if (cmd == "eepw")   { cmdEEPW(); }
    else if (cmd == "eepu")   { cmdEEPU(); }
    //else if (cmd == "math") { cmdMath(); }  
    else {
        setColor(255,0,0);
        Serial.println("Unknown Command: " + cmd);
        setColor(0,0,0);
    }
}
