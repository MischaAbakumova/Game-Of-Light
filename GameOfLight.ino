

#include <Wire.h>
#include "Adafruit_Trellis.h"

#define MOMENTARY 0
#define LATCHING 1
// set the mode here

#define MODE LATCHING

Adafruit_Trellis matrix0 = Adafruit_Trellis();

Adafruit_TrellisSet trellis = Adafruit_TrellisSet(&matrix0);

#define NUMTRELLIS 1

#define INTPIN A2

 int numKeys = 16;
 int answerArray[7];
 int game_stage=0;
//0 stage is light show
//1 stage waiting for input
//2 game over
 int press_count=0;
 boolean gameOver;

void setup() {
Serial.begin(9600);
Serial.println("Trellis Demo");

// INT pin requires a pullup
pinMode(INTPIN, INPUT);
digitalWrite(INTPIN, HIGH);

// begin() with the addresses of each panel in order
// I find it easiest if the addresses are in order
trellis.begin(0x70); // only one
// trellis.begin(0x70, 0x71, 0x72, 0x73); // or four!

// light up all the LEDs in order “SUCCSED”
for (int i=0; i<numKeys; i++) {
trellis.setLED(i);
Serial.print("V");
Serial.print(i);
Serial.print(" ");
trellis.writeDisplay();
delay(50);
//Serial.print(“Button: “); Serial.print(i); 
//delay();
}
// then turn them off
for (int i=0; i<numKeys; i++) {
trellis.clrLED(i);
trellis.writeDisplay(); 
delay(50);
}
gameOver=false;
}

void gameisOver() {

trellis.setLED(0); 
trellis.setLED(1);
trellis.setLED(2);
trellis.setLED(3);
trellis.setLED(4);
trellis.setLED(5);
trellis.setLED(6);
trellis.setLED(7);
trellis.setLED(8);
trellis.setLED(9);
trellis.setLED(10);
trellis.setLED(11);
trellis.setLED(12);
trellis.setLED(13);
trellis.setLED(14);
trellis.setLED(15);
delay (500);
trellis.writeDisplay();

trellis.clrLED(0); 
trellis.clrLED(1);
trellis.clrLED(2);
trellis.clrLED(3);
trellis.clrLED(4);
trellis.clrLED(5);
trellis.clrLED(6);
trellis.clrLED(7);
trellis.clrLED(8);
trellis.clrLED(9);
trellis.clrLED(10);
trellis.clrLED(11);
trellis.clrLED(12);
trellis.clrLED(13);
trellis.clrLED(14);
trellis.clrLED(15);
delay(500); 
trellis.writeDisplay(); 
}

void gamePlay() {

//generate 7 unique numbers in random order
//then display them on the Adafruit

Serial.print("Stage= ");
Serial.println(game_stage);

int x;
int orig_array[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};

if(game_stage==0){
for(int i=0; i<7; i++){ 
int a1 = random(0, numKeys);
Serial.println("");
Serial.print("rand ");
Serial.print(i);
Serial.print(":");
Serial.println(a1);
answerArray[i]=a1;
trellis.setLED(a1);
trellis.writeDisplay();
delay(500);
trellis.clrLED(a1);
trellis.writeDisplay();
delay(500);
}
//set up for stage 1 to start count from 0;
press_count = 0;
gameOver = false;
game_stage=1;

//turn off all leds
for (int i=0; i<numKeys; i++){
trellis.clrLED(i); 
}
trellis.writeDisplay(); 
}

if(game_stage==1){
Serial.println(press_count);
// user needs to match the 7 numbers just generated
// 30ms delay is required, dont remove me!
if(press_count < 7){
if (trellis.readSwitches()) {
// go through every button
for (int i=0; i<numKeys; i++){
// if it was pressed…
if (trellis.justPressed(i)) {
//Serial.print(“BUTTON: “); 
//Serial.println(i);
if (trellis.isLED(i)){
trellis.clrLED(i);
}
else{
trellis.setLED(i);
}
// Alternate the LED
// game check 
if(i==answerArray[press_count]){
//YOU GOT IT!!
//nothing happen here
}
else{
//LOST
gameOver = true;
}
//next touch
press_count+=1;
} 
}
// tell the trellis to set the LEDs we requested
trellis.writeDisplay();
} 
}
else{
game_stage =2; // when press_count reach 7 go to the game over stage = 2
}
// then turn them off, remembering which ones were turned on only
}

if(game_stage == 2){
if(gameOver){
gameisOver();
gameisOver();
gameisOver(); 
}
else{
//celerbration
for (int i=0; i<numKeys; i++) {
trellis.setLED(i);
Serial.print("V");
Serial.print(i);
Serial.print(" ");
trellis.writeDisplay();
delay(50);
//Serial.print(“Button: “); Serial.print(i); 
//delay();
}
// then turn them off
for (int i=0; i<numKeys; i++) {
trellis.clrLED(i);
trellis.writeDisplay(); 
delay(50);
}
}
//reset the game
delay(1000);
gameOver=false;
game_stage = 0;
}
}

void loop() {
delay(30);
gamePlay();
trellis.writeDisplay();
}
