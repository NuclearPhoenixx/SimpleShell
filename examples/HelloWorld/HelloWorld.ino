#include <SimpleShell_Enhanced.h>

#define BAUDRATE 1200

CShell shell;

// Or specifiy a custom Serial port:
// Shell shell(Serial1);

void helloworld(String *args) {
  // Print "Hello World!"
  Serial.println("Hello World!");
  // Print the arguments we've got
  Serial.println(*args);
}

void setup() {
  // Setup the builtin LED for blinking
  pinMode(LED_BUILTIN, OUTPUT);

  // Register our 'helloworld' command
  shell.registerCommand(new ShellCommand(helloworld, "helloworld", "Optional Description"));
  // Setup the serial communication
  shell.begin(BAUDRATE);
}

void serialEvent() {
  // Handle the serial input
  shell.handleEvent();
}

void loop() {
  // Blink the builtin LED
	digitalWrite(LED_BUILTIN, HIGH);
	delay(250);
	digitalWrite(LED_BUILTIN, LOW);
	delay(250);
}
