int incomingByte = 0;
int command[20];
int cmdIndex = 0;

void setup() { 
  Serial.begin(9600);
}
 
void loop() {
  if (Serial.available() > 0) {
    // read the incoming byte
    incomingByte = Serial.read();
    if (incomingByte == 59) {
      // run command
      Serial.println("Command Received:");
      for (int i = 0; i < 20; i ++) {
        Serial.print(command[i]);
      }
    } else if (incomingByte == 10) {
      for (int i = 0; i < 20; i ++) {
        command[i] = 0;
        cmdIndex = 0;
      }
      Serial.println("Command & Index Reset");
    } else {
      
      // echo what was received
      Serial.print("Received: ");
      Serial.println(incomingByte, DEC);
      command[cmdIndex] = incomingByte;
      cmdIndex++;
    }
  }
} 

void byteDecToChar () {
  
}
