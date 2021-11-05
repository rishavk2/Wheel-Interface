int pread1; // var for prev reading switch1
int pread2; // var for prev reading switch2
int floop=0; // has first loop completed

// check which input low, does task associated to input
void rotary1() { // 4 input rotary: D5, D6, D11, D12
    
    if (digitalRead(5) == LOW) {
      Serial.println("input 1"); // test code
    } else if (digitalRead(6)==LOW) {
      Serial.println("input 2"); // test code
    } else if (digitalRead(11)==LOW) {
      // do this
    } else if (digitalRead(12)==LOW) {
      // do this
    }
}

// check which input low, does task associated to input
void rotary2() { // 4 input rotary: D13-D16
    if (digitalRead(13) == LOW) {
      // do this
    } else if (digitalRead(14)==LOW) {
      // do this
    } else if (digitalRead(15)==LOW) {
      // do this
    } else if (digitalRead(16)==LOW) {
      // do this
    }
}
// check which input low, does task associated to input
void rotary3() { // 5 input rotary: D17-D21
    if (digitalRead(17) == LOW) {
      // do this
    } else if (digitalRead(18)==LOW) {
      // do this
    } else if (digitalRead(19)==LOW) {
      // do this
    } else if (digitalRead(20)==LOW) {
      // do this
    } else if (digitalRead(21)==LOW) {
      // do this
    }
}
// checks if on first loop, if so will run no matter what.
// afterwards only runs if new read is different from previous read
void switch1() { // D2
  if (floop==0) { // run no matter what on first execution
    if (digitalRead(2)==LOW) {
      // do this
    } else if (digitalRead(2)==HIGH) {
      // do this
    }
    pread1 = digitalRead(2); // set previous read
  
  } else if (digitalRead(2)!= pread1) { // if the input is not the same as previous execution
    //execution code
    if (digitalRead(2)==LOW) {
      // do this
    } else if (digitalRead(2)==HIGH) {
      // do this
    }
    pread1 = digitalRead(2); // set previous read
  }
}
// checks if on first loop, if so will run no matter what.
// afterwards only runs if new read is different from previous read
void switch2() { // D4
  if (floop==0) { // run no matter what on first execution
    if (digitalRead(4)==LOW) {
      // do this
    } else if (digitalRead(4)==HIGH) {
      // do this
    }
    pread2 = digitalRead(4); // set previous read
  
  } else if (digitalRead(4)!= pread2) { // if the input is not the same as previous execution
    //execution code
    if (digitalRead(4)==LOW) {
      // do this
    } else if (digitalRead(4)==HIGH) {
      // do this
    }
    pread2 = digitalRead(4); // set previous read
  }
}
// if read is low complete task
void button1() {
  if (digitalRead(0)==LOW) {
    // do this
  } 
}
// if read is low complete task
void button2() {
    if (digitalRead(1)==LOW) {
    // do this
  } 
}

// function pointer initialization. Array of button/switch functions
// functions correspond to input array. Ex (D0 = button1)  
  typedef void(*fnPointer)();
  fnPointer fn[] = {button1, button2, switch1, switch2, rotary1, rotary1, rotary1, rotary1, 
  rotary2, rotary2, rotary2, rotary2, rotary3, rotary3, rotary3, rotary3, rotary3};

void setup() {

  Serial.begin(9600);
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
  // array of inputs
  int inputArray[] = {digitalRead(0), digitalRead(1), digitalRead(2), digitalRead(4), digitalRead(5), 
  digitalRead(6), digitalRead(11), digitalRead(12), digitalRead(13), digitalRead(14), digitalRead(15), 
  digitalRead(16), digitalRead(17), digitalRead(18), digitalRead(19), digitalRead(20), digitalRead(21)};

  // calls corresponding function for input if low
  for (int i=0; i<=16; i++) { // runs through all 17 inputs
    
    if (inputArray[i] == LOW || i==2 || i==4) { // read is low, call function, always call the switches
      fn[i]();
    }
  }
  floop=1; // first loop has finished
  delay(100); // delay for stability

}
