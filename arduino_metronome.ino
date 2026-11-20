//www.elegoo.com
/*

 http://www.arduino.cc/en/Tutorial/LiquidCrystal
 */
#include <LiquidCrystal.h>
#include "pitches.h";

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
int onOff = 6;
int right = 4;
int left = 5;
int menu = 3;

float tempo = 60;
int metro = NOTE_C6;
float lastbeat = 0;

float time = 0;

int changePressed = 0;
int changeElapsed = 0;

boolean added = false; 
boolean rightPress = false; 
boolean previousRight = false; 

boolean subtracted = false; 
boolean leftPress = false;
boolean previousLeft = false; 

boolean menuPress = false;
boolean previousMenu = false;
int cursor = 0;

String BPM = "BPM:";
boolean buttonPress = false;
boolean previousPress = false; 
boolean start = false; 

long nowTime = 0;
long stopTime = 0;
long elapsedTime = 0;
long totalElapsed = 0;
long runningTime = 0;

String setTime = "Time:";
String colon = ":";
String zero = "0";
String count = "";

String timeSig[] = {"2/4", "3/4", "4/4", "6/8"};
int beats[] = {2, 3, 4, 6};
int chooseSig = 2;
int accent = NOTE_G6;
int beat = 0;

int button = 0;//1:Left 2:Right 3:Menu 4:Start/Stop
int mode = 0;
static int BPM_MODE = 0;
static int MENU_MODE = 3;
static int TIMESIG_MODE = 1;

byte cursorChar[] = {B01000, B01100, B01110, B01111, B01111, B01110, B01100, B01000};


void setup() {
  lcd.begin(16, 2);
  lcd.clear();
  pinMode(onOff, INPUT_PULLUP);
  pinMode(right, INPUT_PULLUP);
  pinMode(left, INPUT_PULLUP);
  pinMode(menu, INPUT_PULLUP);
  lcd.createChar(0,cursorChar);
  
  Serial.begin(9600);
}

void loop() {
button = checkButtons();

if(button == 3) mode = 3;
  
  if(mode == BPM_MODE){
    checkStart();
    lcd.setCursor(0,0);
    lcd.print(BPM);
    lcd.setCursor(0,1);
    lcd.print(setTime);
    if(start){
      nowTime = millis();
      openSerial();
    
      adjustMetronome(button);

      printMetronome();

      startMetronome();
    
      printTime();
    
    }else{
      elapsedTime = (millis() - stopTime);
    }
  }else if(mode == TIMESIG_MODE){
      lcd.setCursor(0,0);
      lcd.print("Time Signature:");
      lcd.setCursor(0,1);
      lcd.print(timeSig[chooseSig]);
      changeTimeSig();
  }else if (mode == MENU_MODE){
    displayMenu();

    changeMode();

  }

  if(button == 1) previousLeft = true;
  if(button == 2) previousRight = true;
  
}

int checkButtons(){
  if(digitalRead(left)== LOW){
    leftPress = true; 
    if(leftPress != previousLeft) changePressed = millis();
    changeElapsed = millis() - changePressed;
    return 1;
  }else{
    previousLeft = false;
    previousLeft = false;
  }

  if(digitalRead(right) == LOW){
    rightPress = true; 
    if(rightPress != previousRight) changePressed = millis();
    changeElapsed = millis() - changePressed;
    return 2;
  }else{
    rightPress = false;
    previousRight = false;
  }

  if(digitalRead(onOff) == LOW){
    buttonPress = true;
    return 4;
  }else{
    buttonPress = false;
    previousPress = false; 
  }

  if(digitalRead(menu) == LOW){
    menuPress = true;
    if(menuPress != previousMenu) changePressed = millis();
    lcd.clear();
    previousMenu = true; 
    changeElapsed = millis() - changePressed;
    return 3;
  }
  return 0;
}



float setMetronome(int x){
  if(x>0){
    return 60000.00/x;
  }
return 0.00;
}

void checkStart(){
  if(button == 4){
    if(buttonPress != previousPress){
      start = !start;
      if(start) runningTime = millis();
      if(!start) stopTime +=millis()-runningTime;
    }
    previousPress = true;
  }
  
}

void openSerial(){
  if (Serial.available() > 0){
      tempo = Serial.parseFloat();
      while(Serial.available()>0){
        Serial.read();
    }
  }
}

void adjustMetronome(int button){
  if(button == 2){
    if(changeElapsed >= 75 && !added){
      tempo +=1; 
      added = true; 
    }if(changeElapsed >=400){
      if(changeElapsed % 75 <=3){
        tempo+=1;
      }
    }
  }else{
    added = false; 
  }

  if(button == 1){
    if(changeElapsed >= 75 && !subtracted && tempo > 0){
      tempo -=1; 
      subtracted = true; 
    }if(changeElapsed >=400 && tempo > 0){
      if(changeElapsed % 75 <=3){
        tempo-=1;
      }
    }
  }else{
    subtracted = false; 
  }
}

void printMetronome(){
  lcd.setCursor(4,0);
      if(tempo>=100)lcd.print(tempo);
      else lcd.print(zero + tempo);
}
void startMetronome(){
  time = setMetronome(tempo);
  int currBeat = beat;
  int numBeats = beats[chooseSig];
  if(beat>=numBeats){
    currBeat = beat % numBeats;
    
  }

  if(nowTime - lastbeat >= time && time > 0){
    if(currBeat!=0){
        tone(2,metro, 20);
        lastbeat = millis();
        beat++;
      }else if(currBeat == 0){
        tone(2,accent,20);
        lastbeat = millis();
        beat++;
      }
  }  
}

void printTime(){
  lcd.setCursor(5,1);
  String count = findTime(stopTime + (millis() - runningTime));
  lcd.print(count);
}

String findTime(long x){
  int min = 0; 
  int seconds = 0;
  if(x!=0){
    min = x/60000;
    seconds = x/1000;
  } 
  if(seconds>= 60){
    for(int i = seconds; i >=60; i-=60){
      seconds-=60;
    }
  }
  if(seconds<10 && min<10){
    return(zero + min + colon + "0" + seconds);
  }else if(min < 10){
    return(zero +min + colon + seconds);
  }else if(seconds < 10){
    return(min+ colon + zero + seconds);
  }
  return(min + colon + seconds);
}

void changeTimeSig(){
  if(button == 1 && chooseSig > 0 && previousLeft != leftPress){
    chooseSig -=1; 
  }
  if(button == 2 && chooseSig < 3 && previousRight != rightPress){
    chooseSig+=1;
  }
}

void displayMenu(){
  lcd.setCursor(1,0);
  lcd.print("BPM");
  lcd.setCursor(1, 1);
  lcd.print("Time Signature");
  lcd.setCursor(0, cursor);
  lcd.write(byte(0));
}

void changeMode(){
  if(button == 1 && cursor > 0){
    lcd.clear();
    cursor -=1; 
  }if(button == 2 && cursor <1){
    lcd.clear();
    cursor +=1;
  }if(button == 4){
    mode = cursor; 
    lcd.clear();
    previousPress = true;
  }
}
