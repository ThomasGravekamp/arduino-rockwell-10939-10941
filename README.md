## Arduino Rockwell 10939/10941 chipset emulator

This code will make an Arduino Uno (or Nano) behave like an Rockwell 10939/10941 chipset. The Arduino will output the character data sent from any CPU/MPU to the Serial connection.

This project has been developed to debug the data coming from an Gottlieb System 80B pinball machine as the display was not working properly.

More documentation to be added soon...

## Important

Make sure to change the code reading from the port registers when using any other Arduino (compatible) board other than the Arduino Uno or Nano as this code directly uses the values present in the port registers.
