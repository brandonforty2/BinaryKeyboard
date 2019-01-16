#include <Keyboard.h>
#include "info.h"
//

String mode = "";

int zeroPin = 3;
int onePin = 6;
int enterPin = 9;

//State of each key, either 0 or 1
int zero = 0;
int one = 0;
int enter = 0;

void setup(){
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(zeroPin, INPUT);
  pinMode(onePin, INPUT);
  pinMode(enterPin, INPUT);

  delay(1000);
  readKeypresses();
  if (zero == 1 && one == 1 && enter == 1){
    information();
    mode = "ascii";
  }  
  
  else if(zero == 1 && one == 1){
    mode = "binary";
  }

  else{
    mode = "ascii";
  }
  
  Keyboard.begin();
  digitalWrite(LED_BUILTIN, HIGH);
  //SerialUSB.begin(9600);
  //SerialUSB.print("Connected");

  while(zero == 1 || one == 1 || enter == 1){
    readKeypresses();
  }
  
}

void loop(){

/*
  SerialUSB.print(zero);
  SerialUSB.print(one);
  SerialUSB.print(enter);
  SerialUSB.println("");
  delay(1000);
  */
  while (mode == "binary"){
    readKeypresses();
  
    if (zero == 1){
      //Keyboard.write('0');
      keypress2('0', zero, zeroPin);
      //Keyboard.print(out);
    }
    
  
    else if (one == 1){
      //Keyboard.write('1');
      keypress2('1', one, onePin);
    }

    else if (enter == 1){
      keypress2(178, enter, enterPin);
    }
    
  }

  while (mode == "ascii"){
    //Store 8 inputs into an array, then feed that array into the function below
    //Put that functions output into keypress2
    //If the third key is pressed reset the array
    resetArray:
    int charCount = 0;   //Count amount of inputs/length of array
    int letterArray[7];
    int out;

    while (charCount < 8){
      readKeypresses();
      if (zero == 1){
        letterArray[charCount] = 0;
        charCount = charCount + 1;
        while(zero == 1){
          readKeypresses();
        }
      }
      else if(one == 1){
        letterArray[charCount] = 1;
        charCount = charCount + 1;
        while (one == 1){
          readKeypresses();
        }
      }
      else if (enter == 1){
        while (enter == 1){
          readKeypresses();
        }
        goto resetArray;
      }
    }

    out = arrayToInt(letterArray);
    Keyboard.write(out);
    SerialUSB.println(out);
    for (int i = 0; i < 8; i++){
      SerialUSB.print(letterArray[i]);
    }
  }
  
}

void keypress2(char key, int state, int keyPin){
  Keyboard.press(key);
  while(state == 1){
    state = digitalRead(keyPin);
  }
  Keyboard.release(key);
}

int arrayToInt(int letter[]){
  int n = 7;
  //int letterArray[7];
  int letterNumber;
  int i;
  for (i = 0; i < 8; i++){
    letterNumber += (int) letter[i] * pow(2,n);
    SerialUSB.println((int) letter[i] * pow(2,n));
    n = n - 1;
  }
  //SerialUSB.println(letterNumber[]);
  return letterNumber;
}

void readKeypresses(){
  delay(8);
  zero = digitalRead(zeroPin);
  one = digitalRead(onePin);
  enter = digitalRead(enterPin);
}
