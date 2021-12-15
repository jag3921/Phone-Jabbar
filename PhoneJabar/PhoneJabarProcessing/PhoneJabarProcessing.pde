


import processing.serial.*;
import processing.sound.*;

Serial myPort; // Serial object

// Data received from the serial port
int val;
String inBuffer;
SoundFile alarm;

void setup() {
  size(1000, 1000); // window size
  
  String portName = Serial.list()[1];
  myPort = new Serial(this, portName, 9600);
  myPort.clear();
  myPort.bufferUntil('\n');
  
  alarm = new SoundFile(this, "beep.mp3");
}

void draw() {
}

void serialEvent(Serial s) {
  // get the string
  // Note: Every time you read a char, byte or string, it’s removed from
  // the serial buffer. So it’s good practice to read the string into a 
  // variable as shown below and immediately do something with that data 
  // (like graph it, which we do in the draw() method). Then read another string.
  String inBuffer = s.readStringUntil('\n');
  
  if (inBuffer != null) {
    inBuffer = trim(inBuffer); // remove any possible white space characters
    val = int(inBuffer); // get the latest string char & convert it to an int
    if(val == 1){
      println("loop");
      alarm.loop();
    }
    else if(val == 0){
      println("Pause");
      alarm.stop();
    }
  }
}
