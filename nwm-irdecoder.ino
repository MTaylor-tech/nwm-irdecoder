#include <IRremote.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
 
// You will have to set these values depending on the protocol
// and remote codes that you are using. These are For the Adafruit
// Mini Remote
#define MY_PROTOCOL NEC
#define BUTTON_11 0xFFA25D
#define BUTTON_12 0xFF629D 
#define BUTTON_13 0xFFE21D
#define BUTTON_21 0xFF22DD
#define BUTTON_22 0xFF02FD 
#define BUTTON_23 0xFFC23D
#define BUTTON_31 0xFFE01F
#define BUTTON_32 0xFFA857
#define BUTTON_33 0xFF906F
#define BUTTON_41 0xFF6897
#define BUTTON_42 0xFF9867
#define BUTTON_43 0xFFB04F
#define BUTTON_51 0xFF30CF
#define BUTTON_52 0xFF18E7
#define BUTTON_53 0xFF7A85
#define BUTTON_61 0xFF10EF
#define BUTTON_62 0xFF38C7
#define BUTTON_63 0xFF5AA5
#define BUTTON_71 0xFF42BD
#define BUTTON_72 0xFF4AB5
#define BUTTON_73 0xFF52AD
#define SERVOMIN  150 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // this is the 'maximum' pulse length count (out of 4096)
#define LED1 0
#define LED2 1
#define LED3 2
#define LED4 3
#define LED5 4
#define LED6 5
#define LED7 6
#define LED8 7
#define LED9 8
#define LED10 9
#define LED11 10
#define LED12 11
#define SERVO1 12
#define SERVO2 13
#define SERVO3 14
#define PINWHEEL 15
 
IRrecv My_Receiver(11);//Receive on pin 11
decode_results results; 
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
long Previous;   // Stores previous code to handle NEC repeat codes

void snap(int servonum) {
  pwm.setPWM(servonum,0,SERVOMAX);
  delay(200);
  pwm.setPWM(servonum,0,SERVOMIN);
}

void snap2(int servonum1, int servonum2) {
  pwm.setPWM(servonum1,0,SERVOMAX);
  pwm.setPWM(servonum2,0,SERVOMAX);
  delay(200);
  pwm.setPWM(servonum1,0,SERVOMIN);
  pwm.setPWM(servonum2,0,SERVOMIN);
}

void snap3(int servonum1, int servonum2, int servonum3) {
  pwm.setPWM(servonum1,0,SERVOMAX);
  pwm.setPWM(servonum2,0,SERVOMAX);
  pwm.setPWM(servonum3,0,SERVOMAX);
  delay(200);
  pwm.setPWM(servonum1,0,SERVOMIN);
  pwm.setPWM(servonum2,0,SERVOMIN);
  pwm.setPWM(servonum3,0,SERVOMIN);
}

void glow(int led1, int led2, int led3) {
  Serial.print("Glow on ");
  Serial.print(led1);
  Serial.print(", ");
  Serial.print(led2);
  Serial.print(", ");
  Serial.println(led3);
  for (int x=595; x > 0; x--) {
    long rnum = random(1000,3500);
    uint16_t pulselen = rnum + x;
    pwm.setPWM(led1, 0, pulselen);
    rnum = random(1000,3000);
    pulselen = rnum + x;
    pwm.setPWM(led2, 0, pulselen);
    rnum = random(1000,3000);
    pulselen = rnum + x;
    pwm.setPWM(led3, 0, pulselen);
    delay(5);
  }
  pwm.setPWM(led1,0,4096);
  pwm.setPWM(led2,0,4096);
  pwm.setPWM(led3,0,4096);
}

void randGlows() {
  int rnum = random(1,12);
  glows(rnum);
}

void randGlow3() {
  int rnum1 = random(1,12);
  int rnum2 = random(1,12);
  int rnum3 = random(1,12);
  while (rnum2 == rnum1) {
    rnum2 = random(1,12);
  }
  while ((rnum3 == rnum1) || (rnum3 == rnum2)) {
    rnum3 = random(1,12);
  }
  glow(rnum1,rnum2,rnum3);
}

void randSnap() {
  int rnum = random(1,3);
  switch (rnum) {
    case 1:
      snap(SERVO1);
      break;
    case 2:
      snap2(SERVO1, SERVO2);
      //snap(SERVO2);
      break;
    case 3:
      snap3(SERVO1, SERVO2, SERVO3);
      //snap(SERVO2);
      //snap(SERVO3);
      break;
  }
}

void glows(int numleds) {
  Serial.print("Glow with ");
  Serial.print(numleds);
  Serial.println(" leds");
  for (int x=595; x > 0; x--) {
    long rnum = random(1000,3500);
    uint16_t pulselen = rnum + x;
    pwm.setPWM(LED1, 0, pulselen);
    if (1 < numleds) {
      rnum = random(1000,3000);
      pulselen = rnum + x;
      pwm.setPWM(LED2, 0, pulselen);
      if (2 < numleds) {
        rnum = random(1000,3000);
        pulselen = rnum + x;
        pwm.setPWM(LED3, 0, pulselen);
        if (3 < numleds) {
          rnum = random(1000,3000);
          pulselen = rnum + x;
          pwm.setPWM(LED4, 0, pulselen);
          if (4 < numleds) {
            rnum = random(1000,3000);
            pulselen = rnum + x;
            pwm.setPWM(LED5, 0, pulselen);
            if (5 < numleds) {
            rnum = random(1000,3000);
            pulselen = rnum + x;
            pwm.setPWM(LED6, 0, pulselen);
              if (6 < numleds) {
                rnum = random(1000,3000);
                pulselen = rnum + x;
                pwm.setPWM(LED7, 0, pulselen);
                if (7 < numleds) {
                  rnum = random(1000,3000);
                  pulselen = rnum + x;
                  pwm.setPWM(LED8, 0, pulselen);
                  if (8 < numleds) {
                    rnum = random(1000,3000);
                    pulselen = rnum + x;
                    pwm.setPWM(LED9, 0, pulselen);
                    if (9 < numleds) {
                      rnum = random(1000,3000);
                      pulselen = rnum + x;
                      pwm.setPWM(LED10, 0, pulselen);
                      if (10 < numleds) {
                        rnum = random(1000,3000);
                        pulselen = rnum + x;
                        pwm.setPWM(LED11, 0, pulselen);
                        if (11 < numleds) {
                          rnum = random(1000,3000);
                          pulselen = rnum + x;
                          pwm.setPWM(LED12, 0, pulselen);
                        } //12
                      } //11
                    } //10
                  } //9
                } //8
              } //7
            } //6
          } //5
        } //4
      } //3
    } //2
    delay(5);
  } //for
  pwm.setPWM(LED1,0,4096);
  pwm.setPWM(LED2,0,4096);
  pwm.setPWM(LED3,0,4096);
  pwm.setPWM(LED4,0,4096);
  pwm.setPWM(LED5,0,4096);
  pwm.setPWM(LED6,0,4096);
  pwm.setPWM(LED7,0,4096);
  pwm.setPWM(LED8,0,4096);
  pwm.setPWM(LED9,0,4096);
  pwm.setPWM(LED10,0,4096);
  pwm.setPWM(LED11,0,4096);
  pwm.setPWM(LED12,0,4096);
}

void powerup() {
  Serial.println("Tapping into Ley Lines!");
  pwm.setPWM(SERVO1,0,SERVOMIN);
  pwm.setPWM(SERVO2,0,SERVOMIN);
  pwm.setPWM(SERVO3,0,SERVOMIN);
  glow(LED1,LED2,LED3);
  glow(LED4,LED5,LED6);
  glow(LED7,LED8,LED9);
  glow(LED10,LED11,LED12);
  glows(12);
  Serial.println("Ready");
}

void gotime(long action) {
  Serial.print("Received code: ");
  Serial.println(action);
  switch(action) {
            case BUTTON_11: // CH-
              Serial.println("11 CH-");
              powerup();
              break;
            case BUTTON_12: // CH
              randSnap();
              break;
            case BUTTON_13: // CH+
              randGlow3();
              break;
            case BUTTON_21: // |<<
              snap(SERVO1);
              break;
            case BUTTON_22: // >>|
              snap2(SERVO1, SERVO2);
              //snap(SERVO2);
              break;
            case BUTTON_23: // >||
              snap3(SERVO1,SERVO2,SERVO3);
              //snap(SERVO2);
              //snap(SERVO3);
              break;
            case BUTTON_31: // -
              Serial.println("31 -");
              glow(LED1,LED2,LED3); // 0,1,2
              break;
            case BUTTON_32: // +
              Serial.println("32 +");
              randGlows();
              break;
            case BUTTON_33: // EQ
              break;
            case BUTTON_41: // 0
              glows(10);
              break;
            case BUTTON_42: // 100+
              glows(11);
              break;
            case BUTTON_43: // 200+
              glows(12);
              break;
            case BUTTON_51: // 1
              glows(1);
              break;
            case BUTTON_52: // 2
              glows(2);
              break;
            case BUTTON_53: // 3
              glows(3);
              break;
            case BUTTON_61: // 4
              glows(4);
              break;
            case BUTTON_62: // 5
              glows(5);
              break;
            case BUTTON_63: // 6
              glows(6);
              break;
            case BUTTON_71: // 7
              glows(7);
              break;
            case BUTTON_72: // 8
              glows(8);
              break;
            case BUTTON_73: // 9
              glows(9);
              break;
  }
}

void setServoPulse(uint8_t n, double pulse) {
  double pulselength;
  
  pulselength = 1000000;   // 1,000,000 us per second
  pulselength /= 60;   // 60 Hz
  Serial.print(pulselength); Serial.println(" us per period"); 
  pulselength /= 4096;  // 12 bits of resolution
  Serial.print(pulselength); Serial.println(" us per bit"); 
  pulse *= 1000;
  pulse /= pulselength;
  Serial.println(pulse);
  pwm.setPWM(n, 0, pulse);
}

void setup() 
{ 
  My_Receiver.enableIRIn(); // Start the receiver
  Serial.begin(9600);
  Serial.println("It's magic!");

  pwm.begin();
  
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

  powerup();
} 
 
void loop() 
{ 
  pwm.setPWM(LED2,0,4096);
    if (My_Receiver.decode(&results)) {
       if(results.value!=0xFFFFFFFF)
           gotime(results.value);
       Previous=results.value;
       My_Receiver.resume();
    }
    delay(100);
    pwm.setPWM(LED2,4000,1);
    delay(100);
}
