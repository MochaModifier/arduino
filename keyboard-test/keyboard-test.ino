#include <Keyboard.h>

char *comments[] = {"Hello World!", 
  "This is the start of the AID4CG Project!", 
  "This prototype demonstrates a few key things", 
  "----",
  "1. The Hardware component is set up and functional",
  "2. Windows is able to recognize the prototype device as a 'Keyboard'",
  "3. The prototype is able to send keyboard commands to the computer",
  "(this is how I've managed to create this demo)",
  "4. I can control this via button presses",
  "----",
  "Challenges encounted",
  "1. It is possible to 'deadlock' the board, rendering it impossible to re-program the device",
  "2. It is possible to fix this.",
  "3. I am now more familiar with how creating a 'keyboard' type device works, and can avoid this issue now",
  };

int buttonPin = 2;

void setup()
{
  pinMode(buttonPin, INPUT);
  digitalWrite(buttonPin, HIGH);

}

void loop()
{
  bool isRunning = false;
  int arrSize = sizeof(comments);
  if(digitalRead(buttonPin) == LOW && !isRunning) 
  {
    
    isRunning = true;
    
    Keyboard.begin();
    delay(3000);

    for(int i = 0; i < arrSize; i++) {
      delay(2000);
      Keyboard.println(comments[i]);
    }
    delay(1000);
    Keyboard.releaseAll();
    Keyboard.end();

    isRunning = false;
  }


}
