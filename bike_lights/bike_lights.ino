// assign names to pins
#define LEFT_LED_PIN 11
#define MIDDLE_LED_PIN 10
#define RIGHT_LED_PIN 9
#define POT_PIN A0
#define LEFT_BUTTON_PIN 6
#define MIDDLE_BUTTON_PIN 7
#define RIGHT_BUTTON_PIN 8

#define DEBOUNCE_WINDOW_MS 100 // button presses less than this far apart are thrown out

#define NUM_PATTERNS 6
// enum to let us refer to patterns by names instead of numbers
typedef enum {
  AllOff = 0,
  AllOn = 1,
  AllBlinking = 2,
  LeftBlinker = 3,
  RightBlinker = 4,
  Bouncing = 5
} Pattern;

uint32_t patternStartTime = 0; // when the last pattern change was, used for blink logic etc.
Pattern currentPattern = AllOff;

uint32_t lastButtonPressTime = 0; // for debounce - when was the last rising edge

uint8_t cycleButtonLastState = LOW; // for catching the rising edge of the button press

void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
    pinMode(LEFT_LED_PIN, OUTPUT);
    pinMode(MIDDLE_LED_PIN, OUTPUT);
    pinMode(RIGHT_LED_PIN, OUTPUT);
    //inputs
    pinMode(RIGHT_BUTTON_PIN, INPUT);
    pinMode(MIDDLE_BUTTON_PIN, INPUT);
    pinMode(LEFT_BUTTON_PIN, INPUT);
    pinMode(POT_PIN, INPUT);
}

void loop() {
  // this loop has no delays in it. It runs as fast as possible, so as not to miss any inputs.

  // input section: update brightness, read button, do debounce logic
  uint16_t brightness = analogRead(POT_PIN)*255/1024; // multiply before division
  uint8_t cycleButtonState = digitalRead(MIDDLE_BUTTON_PIN);
  if (cycleButtonState == HIGH && cycleButtonLastState == LOW) {
    // rising edge - button was just pressed
    // only act if we're not in the debounce window
    if (millis() > lastButtonPressTime + DEBOUNCE_WINDOW_MS) {
      lastButtonPressTime = millis();
      // enums are constants, so this is just a number I can increment
      currentPattern = currentPattern + 1;
      if (currentPattern >= NUM_PATTERNS){
        // wrap around if we go past the end of the list
        currentPattern = 0;
      }
      // reset patternStartTime
      patternStartTime = millis();
    }
  }

  cycleButtonLastState = cycleButtonState; // save this for the next loop

  // left and right buttons override cycle button
  if (digitalRead(LEFT_BUTTON_PIN) == HIGH) {
    currentPattern = LeftBlinker;
  }
  if (digitalRead(RIGHT_BUTTON_PIN) == HIGH) {
    currentPattern = RightBlinker;
  }

  // status update!
  Serial.print("Current pattern: #");
  Serial.print(currentPattern);
  Serial.print(", brightness: ");
  Serial.println(brightness);

  // output/pattern section: logic for each pattern
  // no delays allowed here. Instead of delays, figure out how long your entire pattern is,
  // and do something like `uint16_t patternElapsedMs = (millis()-patternStartTime) % PATTERN_LENGTH_MS;`
  if (currentPattern == AllOff) {

  } else if (currentPattern == AllOn) {

  } else if (currentPattern == AllBlinking) {
        
  } else if (currentPattern == LeftBlinker) {
    // this is a 1000-ms-long cycle
    int16_t patternElapsedMs = (millis()-patternStartTime) % 1000;
    if (patternElapsedMs < 500){
      analogWrite(LEFT_LED_PIN, brightness);
    } else {
      analogWrite(LEFT_LED_PIN, 0);
    }
    // turn off all other LEDs - they may have been left on by a different pattern
    digitalWrite(MIDDLE_LED_PIN, LOW);
    digitalWrite(RIGHT_LED_PIN, LOW);
  } else if (currentPattern == RightBlinker) {
    // this is a 1000-ms-long cycle
    int16_t patternElapsedMs = (millis()-patternStartTime) % 1000;
    if (patternElapsedMs < 500){
      analogWrite(RIGHT_LED_PIN, brightness);
    } else {
      analogWrite(RIGHT_LED_PIN, 0);
    }
    // turn off all other LEDs - they may have been left on by a different pattern
    digitalWrite(MIDDLE_LED_PIN, LOW);
    digitalWrite(LEFT_LED_PIN, LOW);
  } else if (currentPattern == Bouncing) {
    
  } else {
    Serial.println("ERROR - we haven't handled a pattern - this should be unreachable");
  }
}
