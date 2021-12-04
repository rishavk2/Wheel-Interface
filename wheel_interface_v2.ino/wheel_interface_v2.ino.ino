#include <ASTCanLib.h>  
uint8_t sendData[8];
uint8_t txBuffer[8];

// check which input low, does task associated to input
void rotary1() { // 4 input rotary: 2-5
    
    if (digitalRead(2) == LOW) {
      sendData[0] = 1;
    } else if (digitalRead(3)==LOW) {
      sendData[0] = 2;
    } else if (digitalRead(4)==LOW) {
      sendData[0] = 3;
    } else if (digitalRead(5)==LOW) {
      sendData[0] = 4;
    }
}

// check which input low, does task associated to input
void rotary2() { // 5 input rotary: 6->10
    if (digitalRead(6) == LOW) {
      sendData[1] = 1;
    } else if (digitalRead(7)==LOW) {
      sendData[1] = 2;
    } else if (digitalRead(8)==LOW) {
      sendData[1] = 3;
    } else if (digitalRead(9)==LOW) {
      sendData[1] = 4;
    } else if (digitalRead(10)==LOW) {
      sendData[1] = 5;
    }
}
// check which input low, does task associated to input
void rotary3() { // 5 input rotary: 11->15
    if (digitalRead(11) == LOW) {
      sendData[2]=1;
    } else if (digitalRead(12)==LOW) {
      sendData[2]=2;
    } else if (digitalRead(13)==LOW) {
      sendData[2]=3;
    } else if (digitalRead(14)==LOW) {
      sendData[2]=4;
    } else if (digitalRead(15)==LOW) {
      sendData[2]=5;
    }
}

void switch1() { // 16
    if (digitalRead(16)==LOW) {
      sendData[3]=0; // need to double check this
    } else if (digitalRead(16)==HIGH) {
      sendData[3]=1;
    }
}
// checks if on first loop, if so will run no matter what.
// afterwards only runs if new read is different from previous read
void switch2() { // D4
    if (digitalRead(17)==LOW) {
      sendData[4]=0; // need to double check this
    } else if (digitalRead(17)==HIGH) {
      sendData[4]=1;
    }
}

void button1() { // 1 pressed 0 up
  if (digitalRead(18)==LOW) {
    sendData[5]=0;
  } else if (digitalRead(18)==HIGH) {
    sendData[5]=1;
  }
}

void button2() { // 1 pressed 0 up
  if (digitalRead(19)==LOW) {
    sendData[6]=0;
  } else if (digitalRead(19)==HIGH) {
    sendData[6]=1;
  }
}

// function pointer initialization. Array of button/switch functions
// functions correspond to input array. Ex (D0 = button1)  
  typedef void(*fnPointer)();
  fnPointer fn[] = {rotary1, rotary1, rotary1, rotary1, rotary2, rotary2, rotary2, rotary2, 
  rotary2, rotary3, rotary3, rotary3, rotary3, rotary3, switch1, switch2, button1, button2};

void setup() {

  canInit(1000000); // init CAN port
  Serial.begin(9600);
  txMsg.pt_data = &txBuffer[0]; // reference massage data to transmit buffer
  
  pinMode(0, INPUT_PULLUP);
  pinMode(1, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP); 
  pinMode(5, INPUT_PULLUP); 
  pinMode(6, INPUT_PULLUP); 
  pinMode(11, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);
  pinMode(13, INPUT_PULLUP);
  pinMode(14, INPUT_PULLUP);
  pinMode(15, INPUT_PULLUP);
  pinMode(16, INPUT_PULLUP);
  pinMode(17, INPUT_PULLUP);
  pinMode(18, INPUT_PULLUP);
  pinMode(19, INPUT_PULLUP);
  pinMode(20, INPUT_PULLUP);
  pinMode(21, INPUT_PULLUP);

}


void loop() {

  // calls all functions
  for (int i=0; i<=19; i++) { // runs through all 17 inputs
    fn[i]();
  }
  //  load data into tx buffer
  for (int i=0; i<8; i++){
    txBuffer[i] = sendData[i];
  }
  // Setup CAN packet.
  txMsg.ctrl.ide = MESSAGE_PROTOCOL;  // Set CAN protocol (0: CAN 2.0A, 1: CAN 2.0B)
  txMsg.id.ext   = MESSAGE_ID;        // Set message ID
  txMsg.dlc      = MESSAGE_LENGTH;    // Data length: 8 bytes
  txMsg.ctrl.rtr = MESSAGE_RTR;       // Set rtr bit

  // Send command to the CAN port controller
  txMsg.cmd = CMD_TX_DATA;       // send message
  // Wait for the command to be accepted by the controller
  while(can_cmd(&txMsg) != CAN_CMD_ACCEPTED);
  // Wait for command to finish executing
  while(can_get_status(&txMsg) == CAN_STATUS_NOT_COMPLETED);
  // Transmit is now complete. Wait a bit and loop
  delay(100); // delay for stability

}
