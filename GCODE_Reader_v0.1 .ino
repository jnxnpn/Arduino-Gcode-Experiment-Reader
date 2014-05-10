/* 
 Experimental G-code reader (actually A-code...) versionn: 0.1
 Type A___(degrees) in serial monitor to run the servo on pin 9
 baudrate 9600 or custom
 
 
 see: http://youtu.be/dCb3nYzt8eg for demostration. 
 
 Coded by JX Pan
 
 under CC Attribution-NonCommercial-ShareAlike 4.0 International license
 
 Have fun
 */

#include <Servo.h> 
byte byteRead; // setup, 坑爹!!!!
boolean done;  
int num;
int dig;
boolean cmd;
Servo serv;


void setup() {     

  Serial.begin(9600); // the higher the better if possible
  serv.attach(9);
}

void loop() {

  cmd = false;  // set for this new loop
  done = true;  // so that the big "while" wouldn't be triggered unless byteRead is 65
  dig = -1;     // set for this loop, -1 for easier calculation later
  num = 0;      // set for this new loop
  byteRead = Serial.read();
  while(byteRead == 65 || done == false)
  { 

    done = false; // so that "while" wouldn't stop inspite of changes of byteRead
    delay(10);    // for better communication
    byteRead = Serial.read();

    while(byteRead >= 48 && byteRead <= 57 && done == false)
    { 

      dig = dig+1;
      num = (byteRead -48) + num * 10;
      delay(10); 
      byteRead = Serial.read();  // read before "if" and another aound of "while"

      if (byteRead ==10)
      { 
        done = true; // to end both big and small "while", I know there's a command for
                     // this situation, but I forgot how to use it... called "break" maybe
        cmd = true;  // to help distinguish if there IS a command. 
                     // so that the servo wouldn't keep going to 0
        Serial.print ("Received: ");
        Serial.print ("A");
        Serial.println (num);


      }
    }
  }


  if (cmd == true) // if there's actually a command
  { 
    if (num <= 180 && num >= 0 )
    {
      //servo action

      serv.write(num); 
      delay(15); 

      //Serial action



    }
    else
    {
      Serial.println("error: excessive angle");
      // if there is a command and Arduino receives a excessive angle number
      // this code automatically ignores "-", so no worries about negative degrees
    }

  }

  delay (10); // for better communication


}









