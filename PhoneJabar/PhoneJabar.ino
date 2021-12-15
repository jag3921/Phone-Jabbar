int touchSensorVal, baseTouchSensorVal, buttonPushes, prevButtonState, buttonState, prevTouchSensorVal;
unsigned long timer, oldTime;
bool buttonReset, started, playingAudio;
const int Button_Pin = 2;
const int MaxButtonPresses = 50;
const long MaxTimer = 6000;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(Button_Pin, INPUT);

  timer = 0;
  started = false;
  calibrateSensors();
}

void loop() {
  // put your main code here, to run repeatedly:
  touchSensorVal = analogRead(A0);
  buttonState = digitalRead(Button_Pin);
  if(touchSensorVal - prevTouchSensorVal > 100 && timer == 0){
    Reset();
    started = true;
  }
  if(touchSensorVal > 400 && started) 
  {
    timer += (millis() - oldTime);
    if(playingAudio){
      playingAudio = false;
      Serial.println(0);
    }
    if(timer >= MaxTimer)
    {
      Reset();
      started = false;
    }
  }
  if(timer < MaxTimer && timer > 0){
    if( (touchSensorVal < 400) && !buttonReset){
      if(!playingAudio){
        Serial.println(1);
        playingAudio = true;
      }
    }
      if(buttonState == HIGH && prevButtonState == LOW){
        buttonPushes++;
      }
      if(buttonPushes >= MaxButtonPresses){
        Reset();
        started = true;
      }
  }
  
  oldTime = millis();
  prevButtonState = buttonState;
  prevTouchSensorVal = touchSensorVal;
  delay(1);
}

void Reset(){
  timer = 0;
  buttonPushes = 0;
  buttonReset = false;
  if(playingAudio){
    playingAudio = false;
    Serial.println(0);
  }
}

void calibrateSensors(){
  baseTouchSensorVal = analogRead(A0);
}
