const int led = 5; // GPIO5
const int button = 4; // GPIO4
char buttonIsPressed[4]; // char to keep "yes" or "no"
int counter = 0;

int ledState = HIGH;
int buttonState; // the current reading from the input pin
int lastButtonState = LOW; // the previous reading from the input pin

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0; // the last time the output pin was toggled
unsigned long debounceDelay = 50; // the debounce time; increase if the output flickers

void setup()
{
  pinMode(led,OUTPUT);
  pinMode(button,INPUT_PULLUP); // pull up GPIO4 = HIGH when button not pressed
 
  Serial.begin(115200); // initialize USB Serial communication at 115.2 Kbps
 
  digitalWrite(led,ledState);
}

void loop(){
  int val = digitalRead(button); // perform digital reading on GPIO4
 
  // Serial.print("Val // Serial.print(val);
  if (val == 0) // GPIO4 becomes LOW when button is pressed
  {
    strcpy(buttonIsPressed,"yes");// copy the word "yes" into buttonIsPressed variable
  }
  else
  {
    strcpy(buttonIsPressed,"no"); // copy the word "no" into buttonIsPressed variable
  }
 
  // If the switch changed, due to noise or pressing:
  if (val != lastButtonState)
  {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }
  
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (val != buttonState) 
    {
      buttonState = val;

      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH)
      {
        ledState = !ledState;
        counter++;
      }
    }
  }

  if (counter >= 10) 
  {
    counter = 0;
  }

  // set the LED:
  digitalWrite(led, ledState);

  Serial.print("\tbutton pressed: ");
  Serial.println(buttonIsPressed);          // print out the button is pressed
  Serial.print("\tcounter: ");            // print out counter
  Serial.println(counter);
  Serial.print("\tbutton: ");
  Serial.println(buttonState);              // print out buttonState
  Serial.print("\tlastButtonState: ");
  Serial.println(lastButtonState);          // print out last button state
 
  delay(500);
  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = val;
}