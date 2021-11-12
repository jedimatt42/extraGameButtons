/* Buttons to USB Joystick Example

   You must select Joystick from the "Tools > USB Type" menu

   This example code is in the public domain.
*/

#include <Bounce.h>

// Create Bounce objects for each button.  The Bounce object
// automatically deals with contact chatter or "bounce", and
// it makes detecting changes very simple.
// 10 ms debounce time
Bounce button0 = Bounce(7, 10);
Bounce button1 = Bounce(8, 10);

int b0_pressed;
int b1_pressed;

void setup() {
  // Configure the pins for input mode with pullup resistors.
  // The pushbuttons connect from each pin to ground.  When
  // the button is pressed, the pin reads LOW because the button
  // shorts it to ground.  When released, the pin reads HIGH
  // because the pullup resistor connects to +5 volts inside
  // the chip.  LOW for "on", and HIGH for "off" may seem
  // backwards, but using the on-chip pullup resistors is very
  // convenient.  The scheme is called "active low", and it's
  // very commonly used in electronics... so much that the chip
  // has built-in pullup resistors!
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(13, OUTPUT);
  b0_pressed = LOW;
  b1_pressed = LOW;
  digitalWrite(13, LOW);

  // set analog part of joystick to a stable state
  Joystick.X(512);
  Joystick.Y(512);
  Joystick.Z(512);
  Joystick.Zrotate(512);
  Joystick.sliderLeft(512);
  Joystick.sliderRight(512);
  Joystick.hat(-1);
}

void loop() {
  // Update all the buttons.  There should not be any long
  // delays in loop(), so this runs repetitively at a rate
  // faster than the buttons could be pressed and released.
  button0.update();
  button1.update();

  // Check each button for "falling" edge.
  // Update the Joystick buttons only upon changes.
  // falling = high (not pressed - voltage from pullup resistor)
  //           to low (pressed - button connects pin to ground)
  if (button0.fallingEdge()) {
    Joystick.button(1, 1);
    b0_pressed = HIGH;
  }
  if (button1.fallingEdge()) {
    Joystick.button(2, 1);
    b1_pressed = HIGH;
  }

  // Check each button for "rising" edge
  // Update the Joystick buttons only upon changes.
  // rising = low (pressed - button connects pin to ground)
  //          to high (not pressed - voltage from pullup resistor)
  if (button0.risingEdge()) {
    Joystick.button(1, 0);
    b0_pressed = LOW;
  }
  if (button1.risingEdge()) {
    Joystick.button(2, 0);
    b1_pressed = LOW;
  }

  digitalWrite(13, b0_pressed || b1_pressed);
}
