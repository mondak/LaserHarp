//Modified by Matthew Ondak
#include <Tone.h> //Make sure to install the Tone library in the Arduino

const boolean DEBUG = false; //Turn to true if we need to debug

const int CALIBRATION_PIN = A5; //Where our tuner is potentiometer is
const int SPEAKER_PIN = 8; // Where the speaker pin is
const int SENSOR_COUNT = 5; //How many laser strings we will have

typedef struct 
{
  int pin; //To assign each pin
  int note; //To assign the note to be played
} 
sensor_type;

sensor_type sensor[SENSOR_COUNT]; //Setup an array of the sensors

Tone notePlayer; //Bring up the library of tones

void setup(void)
{
  if (DEBUG) {
    Serial.begin(9600);
  }
  sensor[0].pin = A0; // analog input 0
  sensor[0].note = NOTE_C4; //These notes can be changed. Reference Tone library
  sensor[1].pin = A1; //analog input 1,
  sensor[1].note = NOTE_D4;
  sensor[2].pin = A2; //Analog input 2,
  sensor[2].note = NOTE_E4;
  sensor[3].pin = A3; //Analog input 3,
  sensor[3].note = NOTE_F4;
  sensor[4].pin = A4; //Analog input 4 
  sensor[4].note = NOTE_G4;

  notePlayer.begin(SPEAKER_PIN); //Begin playing the sound
}

void loop(void)
{//Loop that senses when the photoresisters drop a certain calibration
  //It then sends a signal true to play a sound. Checks all the sensors
  int calibration = analogRead(CALIBRATION_PIN);
  if (DEBUG) {
    Serial.print("cal: ");
    Serial.print(calibration);
  }
  int activeSensor = -1;//To make sure the sound isn't always playing set it to -1
  for (int p = 0 ; p < SENSOR_COUNT ; p++) {
    int sensor_value = analogRead(sensor[p].pin);
    if (DEBUG) {
      Serial.print("\tsensor ");
      Serial.print(p);
      Serial.print(": ");
      Serial.print(sensor_value);
    }
    if ( sensor_value < calibration ) {
      activeSensor = p; //Set active sensor to whichever sensor since the calibration is higher than the sensor
      if (DEBUG) Serial.print("!"); // "!" indicates note being played
    }
  }
  if (DEBUG) Serial.println();
  if (activeSensor == -1) {
    notePlayer.stop(); //Stop if a finger is moved
  } 
  else {
    notePlayer.play(sensor[activeSensor].note); //Otherwise play a note
  }
  if (DEBUG) delay(1000);
}



