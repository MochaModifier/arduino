/** Aid4CG Prototype
 * Goals: 
 *  1 Hardcoded hotkeys
 *  2 Press and Release keys in sync with button
 *  3 Perform useful work in a 3d modeling app
 * 
 * Created 3/29/2020 by Glenn Craver (@MochaModifier)
 * 
 * */

#include "Keyboard.h"

/* Button Layout
 * [3] [4] [5]
 * [0] [1] [2]
 */ 

// pins definitions
// All buttons trigger on HIGH
/// [Alias] Keyboard Mode blocks uploading of sketches, board is recognized as a keyboard
const bool MODE_KEYBOARD = true;
/// [Alias] Arduino Mode allows for uploading of sketches
const bool MODE_ARDUINO = false;

/// [Pin 13] Sets the Board Mode based on pin state
const int SWITCH_MODE = 13;
/// Stores which btns are connected to which pins
const int btnPins[] = {4, 3, 2, 8, 7, 6};
/// Number of Buttons the board has. This value is a constant, and shouldn't change later on.
const int NUM_BUTTONS = sizeof(btnPins) / 2;


/// Stores what key a button corresponds to
char btnActions[] = {'E', '1', '2', 'w', 'e', 'r'};

/// Stores last read state off the SWITCH_MODE pin
bool boardPrevMode = MODE_ARDUINO;
/// Stores the current acknowledged state of each button
int btnState[] = {LOW, LOW, LOW, LOW, LOW, LOW};

/// Stores the last read states off each button
int btnLastRead[] = {LOW, LOW, LOW, LOW, LOW, LOW};
/// Stores the last read states off each button
int btnLastTriggerTime[] = {0, 0, 0, 0, 0, 0};

/** Experiment */
/// experimental - How many milliseconds to wait before acknowledging the state of a pin
const int DEBOUNCE_DELAY = 50; //in ms


void setup()
{
  // set the Keyboard Toggle Switch pin
  pinMode(SWITCH_MODE, INPUT);

  boardPrevMode = digitalRead(SWITCH_MODE) == HIGH;

  // set all BTN pins as inputs
  for(int pin = 0; pin < NUM_BUTTONS; pin++) {
    pinMode(pin, INPUT);
  }

}
void loop()
{
  // the Leonardo is in Keyboard Mode if the Toggle Pin reads HIGH
  bool boardMode = digitalRead(SWITCH_MODE) == HIGH;
  bool modeChanged = boardMode != boardPrevMode;

  if(modeChanged) {
    if(boardMode == MODE_KEYBOARD) {
      Keyboard.begin();
    } else {
      // clean up and end Keyboard mode.
      Keyboard.releaseAll();
      Keyboard.end();  
    }
  } else { // no change in board mode
    if(boardMode == MODE_KEYBOARD) {  
      int btnReading; // stores btnReading as HIGH or LOW
      bool stateHasChanged; // if btn state has changed, stores as true
      
      for(int btn = 0; btn < NUM_BUTTONS; btn++) {
        btnReading = digitalRead(btnPins[btn]);
        
        if(btnLastRead[btn] != btnReading) {
          // record the time after any state change, be it from noise or pressing
          btnLastTriggerTime[btn] = millis();
          // record this reading for next time
          btnLastRead[btn] = btnReading;
        }

        int deltaTime = millis() - btnLastTriggerTime[btn];

        if(deltaTime > DEBOUNCE_DELAY) {
          if(btnState[btn] != btnReading){
            if(btn == 0 && btnReading == HIGH) {
              Keyboard.press(KEY_LEFT_SHIFT);
              Keyboard.press(KEY_LEFT_ALT);
              delay(30);
              Keyboard.write('e');
              delay(30);
              Keyboard.release(KEY_LEFT_SHIFT);
              Keyboard.release(KEY_LEFT_ALT);
            }
            else if(btn == 1  && btnReading == HIGH) {
              Keyboard.press(KEY_LEFT_CTRL);
              Keyboard.press(KEY_LEFT_ALT);
              delay(30);
              Keyboard.write('w');
              delay(30);
              Keyboard.release(KEY_LEFT_CTRL);
              Keyboard.release(KEY_LEFT_ALT);
            }
            else if(btn == 2 && btnReading == HIGH) {
              Keyboard.press(KEY_LEFT_ALT);
              delay(30);
              Keyboard.write('1');
              delay(30);
              Keyboard.release(KEY_LEFT_ALT);
            }
            else if(btnReading == HIGH) {
              Keyboard.press(btnActions[btn]);
            } else {
              Keyboard.release(btnActions[btn]);
            }
            // record current btnReading for later
          }
          btnState[btn] = btnReading;
        }
      }
    } else {
      delay(500);
    }
  }

  boardPrevMode = boardMode;


}
